#include "Detection.h"
#include <process.h>
#include <wincon.h>
#include <WinInet.h>
#pragma comment(lib,"wininet.lib")

/*整体线程控制全局变量*/
bool g_threadWait = false;

/*条码全局变量*/
QString g_code = "";

QString Dt::Base::m_lastError = "No error";

QList<QString> Dt::Base::m_logList = {};

bool Dt::Base::m_outputRunLog = false;

IConnMgr* Dt::Base::m_canConnMgr = nullptr;

CanSender Dt::Base::m_canSender = CanSender();

/************************************************************************/
/* Dt::Base realize                                                         */
/************************************************************************/

Dt::Base::Base(QObject* parent)
{
	qRegisterMetaType<BaseTypes::TestResult>("BaseTypes::TestResult");
	qRegisterMetaType<bool*>("bool*");
}

Dt::Base::~Base()
{
	exitConsoleWindow();

	JsonTool::deleteInstance();
	
	threadQuit();

	QApplication::exit(0);
}

const QString& Dt::Base::getLastError()
{
	return m_lastError;
}


void Dt::Base::setTestSequence(const int& testSequence)
{
	m_testSequence = testSequence;
}

void Dt::Base::setDetectionType(const BaseTypes::DetectionType& type)
{
	m_detectionType = type;
}

const BaseTypes::DetectionType& Dt::Base::getDetectionType()
{
	return m_detectionType;
}

bool Dt::Base::initInstance()
{
	bool result = false;
	do
	{
		m_jsonTool = JsonTool::getInstance();

		RUN_BREAK(!m_jsonTool, "m_jsonTool分配内存失败");

		RUN_BREAK(!m_jsonTool->initInstance(), m_jsonTool->getLastError());

		m_defConfig = m_jsonTool->getParsedDefConfig();

		m_hwdConfig = m_jsonTool->getParsedHwdConfig();

		m_udsConfig = m_jsonTool->getParsedUdsConfig();

		m_canConnMgr = m_canConnFactory.GetConnMgrInstance(m_defConfig->device.canName.toLatin1());

		RUN_BREAK(!m_canConnMgr, "CAN通信初始化失败");

#ifdef QT_DEBUG
		m_canConnMgr->EnableDebugInfo(true);
#endif

		RUN_BREAK(!initConsoleWindow(), "初始化调试控制台失败");

		if (m_defConfig->enable.saveCanLog)
		{
			saveCanLog(true);
		}

		m_udsApplyMgr = m_udsFactory.GetConnMgrInstance(m_defConfig->device.udsName.toLatin1());

		RUN_BREAK(!m_udsApplyMgr, "UDS通信协议初始化失败");

		m_udsApplyMgr->SetIConnMgr(m_canConnMgr);

		RUN_BREAK(!m_canSender.Init(m_canConnMgr), "CanSender初始化失败");

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::initConsoleWindow()
{
	bool result = false;
	do 
	{
		m_outputRunLog = m_defConfig->enable.outputRunLog;

		if (!m_outputRunLog)
		{
			result = true;
			break;
		}

		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		result = true;
	} while (false);
	return result;
}

void Dt::Base::exitConsoleWindow()
{
	if (!m_outputRunLog)
	{
		return;
	}
	FreeConsole();
}

bool Dt::Base::openDevice()
{
	bool result = false;
	do
	{
		m_connect = true;
		if (!m_canConnMgr->Connect(500, 0))
		{
			setLastError("连接CAN卡失败", false, true);
		}

		auto& hardware = m_defConfig->hardware;
		if (!m_power.Open(hardware.powerPort, hardware.powerBaud, hardware.powerVoltage))
		{
			setLastError("打开电源失败", false, true);
		}

		if (!m_relay.Open(hardware.relayPort, hardware.relayBaud))
		{
			setLastError("打开继电器失败", false, true);
		}

		if (!m_voltage.Open(hardware.voltagePort, hardware.voltageBaud))
		{
			setLastError("打开电压表失败", false, true);
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Base::closeDevice()
{
	bool result = false;
	do
	{
		setScanCodeDlg(m_connect = false);

		if (!m_canConnMgr->DisConnect())
		{
			setLastError("CAN断开连接失败", false, true);
		}

		if (!m_power.Output(false))
		{
			setLastError("关闭电源失败", false, true);
		}

		Sleep(100);

		if (!m_power.Close())
		{
			setLastError("关闭电源失败", false, true);
		}

		if (!m_relay.Close())
		{
			setLastError("关闭继电器失败", false, true);
		}

		m_voltage.Close();

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::prepareTest(LaunchProc launchProc, void* args)
{
	setCurrentStatus("准备测试");
	setTestResult(BaseTypes::TestResult::TR_TS);
	bool result = false, success = true;
	do
	{
		setCanLogName(m_defConfig->device.detectionName, m_defConfig->device.modelName, g_code);

		clearListItem();

		m_elapsedTime = GetTickCount();

		addListItem(Q_SPRINTF("第%u块产品开始测试", m_total), false);

		initDetectionLog();

		addListItem("等待系统启动,请耐心等待...");

		RUN_BREAK(!m_power.Output(true), "电源通讯失败,请检测连接");

		msleep(300);

		m_canSender.Start();

		if (m_detectionType == BaseTypes::DT_AVM)
		{
			const int portArray[] = {
				m_defConfig->relay.acc
				,m_defConfig->relay.gnd
				,m_defConfig->relay.pinboard
			};

			bool success = true;
			for (int i = 0; i < sizeof(portArray) / sizeof(int); i++)
			{
				if (!m_relay.SetOneIO(portArray[i], true))
				{
					success = false;
					break;
				}
				msleep(300);
			}
			RUN_BREAK(!success, "继电器通讯失败,请检查连接");
		}

		if (m_detectionType != BaseTypes::DT_DVR)
		{
			size_t&& startTime = GetTickCount();
			launchProc&& args ? (success = launchProc(args)) : msleep(m_startDelay);
			setCurrentStatus(success ? "状态正常" : "状态异常", true);
			addListItem(Q_SPRINTF("系统启动%s用时 %.2f秒", success ? "成功" : "失败", static_cast<float>(GetTickCount() - startTime) / 1000));
			addListItem(Q_SPRINTF("系统启动 %s", OK_NG(success)), false);
		}

		RUN_BREAK(!success, "初始化系统异常");

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::prepareTest(LaunchProcEx lauProcEx, void* args, const int& request, MsgProc msgProc)
{
	setCurrentStatus("准备测试");
	setTestResult(BaseTypes::TestResult::TR_TS);
	bool result = false, success = true;
	do
	{
		setCanLogName(m_defConfig->device.detectionName, m_defConfig->device.modelName, g_code);

		clearListItem();

		m_elapsedTime = GetTickCount();

		addListItem(Q_SPRINTF("第%u块产品开始测试", m_total), false);

		initDetectionLog();

		addListItem("等待系统启动,请耐心等待...");

		RUN_BREAK(!m_power.Output(true), "电源通讯失败,请检查连接");

		msleep(300);

		m_canSender.Start();

		if (m_detectionType == BaseTypes::DT_AVM)
		{
			const int portArray[] = {
				m_defConfig->relay.acc
				,m_defConfig->relay.gnd
				,m_defConfig->relay.pinboard
			};

			bool success = true;
			for (int i = 0; i < sizeof(portArray) / sizeof(int); i++)
			{
				if (!m_relay.SetOneIO(portArray[i], true))
				{
					success = false;
					break;
				}
				msleep(300);
			}
			RUN_BREAK(!success, "继电器通讯失败,请检查连接");
		}

		if (m_detectionType != BaseTypes::DT_DVR)
		{
			size_t&& startTime = GetTickCount();
			success = lauProcEx(args, request, msgProc);
			setCurrentStatus(success ? "状态正常" : "状态异常", true);
			addListItem(Q_SPRINTF("系统启动%s用时 %.2f秒", success ? "成功" : "失败", static_cast<float>(GetTickCount() - startTime) / 1000));
			addListItem(Q_SPRINTF("系统启动 %s", OK_NG(success)), false);
		}

		RUN_BREAK(!success, "初始化系统异常");

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::prepareTest(const int& id, const ulong& delay, const int& req, MsgProc msgProc)
{
	setCurrentStatus("准备测试");
	setTestResult(BaseTypes::TestResult::TR_TS);
	bool result = false, success = true;
	do
	{
		setCanLogName(m_defConfig->device.detectionName, m_defConfig->device.modelName, g_code);

		clearListItem();

		m_elapsedTime = GetTickCount();

		addListItem(Q_SPRINTF("第%u块产品开始测试", m_total), false);

		initDetectionLog();

		addListItem("等待系统启动,请耐心等待...");

		RUN_BREAK(!m_power.Output(true), "电源通讯失败,请检查连接");

		msleep(300);

		m_canSender.Start();

		if (m_detectionType == BaseTypes::DT_AVM)
		{
			const int portArray[] = {
				m_defConfig->relay.acc
				,m_defConfig->relay.gnd
				,m_defConfig->relay.pinboard
			};

			bool success = true;
			for (int i = 0; i < sizeof(portArray) / sizeof(int); i++)
			{
				if (!m_relay.SetOneIO(portArray[i], true))
				{
					success = false;
					break;
				}
				msleep(300);
			}
			RUN_BREAK(!success, "继电器通讯失败,请检查连接");
		}

		if (m_detectionType != BaseTypes::DT_DVR)
		{
			size_t&& startTime = GetTickCount();
			success = autoProcessCanMsg(id, req, msgProc, delay);
			setCurrentStatus(success ? "状态正常" : "状态异常", true);
			addListItem(Q_SPRINTF("系统启动%s用时 %.2f秒", success ? "成功" : "失败", static_cast<float>(GetTickCount() - startTime) / 1000));
			addListItem(Q_SPRINTF("系统启动 %s", OK_NG(success)), false);
		}

		RUN_BREAK(!success, "初始化系统异常," + getLastError());

		result = true;
	} while (false);
	return result;
}

void Dt::Base::setStartDelay(const size_t& delay)
{
	m_startDelay = delay;
}

bool Dt::Base::finishTest(bool success)
{
	bool result = false;
	do
	{
		if (success)
		{
			++m_total;
		}

		flushCanLogBuffer();

		addListItem(Q_SPRINTF("测试用时 %.2f秒", (float)(GetTickCount() - m_elapsedTime) / 1000), false);

		setTestResult(success ? BaseTypes::TestResult::TR_OK : BaseTypes::TestResult::TR_NG);

		m_canSender.Stop();

		RUN_BREAK(!m_power.Output(false), "电源通讯失败,请检查连接");

		msleep(300);

		if (m_detectionType == BaseTypes::DT_AVM)
		{
			const int portArray[] = {
			m_defConfig->relay.acc
			,m_defConfig->relay.gnd
			,m_defConfig->relay.pinboard
			};

			bool success = true;
			for (int i = 0; i < sizeof(portArray) / sizeof(int); i++)
			{
				if (!m_relay.SetOneIO(portArray[i], false))
				{
					success = false;
					break;
				}
				msleep(300);
			}
			RUN_BREAK(!success, "继电器通讯失败,请检查连接");
		}
		else if (m_detectionType == BaseTypes::DT_AVM)
		{
			RUN_BREAK(!m_relay.SetAllIO(false), "继电器通讯失败,请检查连接");
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Base::saveLog(bool success)
{
	bool result = false;
	do
	{
		if (!finishTest(success))
		{
			break;
		}

		if (success ? true : setQuestionBox("提示", getLastError() + "\n检测NG是否要保存日志"))
		{
			if (!writeLog(success))
			{
				break;
			}
		}

		if (!success && m_defConfig->enable.unlockDlg)
		{
			setUnlockDlg();
		}

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::checkCurrent()
{
	setCurrentStatus("检测电流");
	bool result = false, success = true,deviceFail = false;
	do
	{
		CurrentConfig* info = m_hwdConfig->current;
		for (int i = 0; i < m_jsonTool->getCurrentConfigCount(); i++)
		{
			float voltage = 0.0f;
			RUN_BREAK(deviceFail = !m_power.GetVoltage(&voltage), "获取电压失败");

			if (fabs(voltage - info[i].voltage) > 0.1)
			{
				RUN_BREAK(deviceFail = !m_power.SetVol(info[i].voltage), "设置电压失败");
				msleep(3000);
			}

			RUN_BREAK(deviceFail = !m_power.GetCurrent(&info[i].read), "获取电流失败");

			(info[i].read >= info[i].low) && (info[i].read <= info[i].high) ? info[i].result = true : info[i].result = success = false;

			addListItem(Q_SPRINTF("%s  %.3f  %s", info[i].name, info[i].read, OK_NG(info[i].result)));

			WRITE_LOG("%s,%s,%.3f,%.3f,%.3f", OK_NG(info[i].result), info[i].name, info[i].read, info[i].high, info[i].low);
		}
		
		RUN_BREAK(deviceFail, getLastError());

		RUN_BREAK(!success, "检测电流失败");

		result = true;
	} while (false);
	m_power.SetVol(m_defConfig->hardware.powerVoltage);
	addListItem(Q_SPRINTF("检测电流 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Base::checkStaticCurrent(const ulong& delay)
{
	setCurrentStatus("检测静态电流");
	bool result = false;
	do
	{
		addListItem("检测静态电流需要一定时间大约30秒,请耐心等待...");
		float current = 0.0f;
		RUN_BREAK(!m_power.GetCurrent(&current), "获取工作电流失败");

		RUN_BREAK(current < 0.1, "系统未上电");

		auto& relay = m_defConfig->relay;
		RUN_BREAK(!m_relay.SetOneIO(relay.acc, false), "继电器关闭ACC IO失败");
		msleep(300);

		size_t&& startTime = GetTickCount();
		bool success = false;
		while (true)
		{
			if (m_power.GetCurrent(&current))
			{
				if (current < 0.01)
				{
					success = true;
					break;
				}
			}

			if (GetTickCount() - startTime >= 15000)
			{
				break;
			}
			msleep(300);
		}

		RUN_BREAK(!success, "系统休眠超时");
		msleep(500);

		RUN_BREAK(!m_relay.SetOneIO(relay.staticCur, true), "继电器静态电流表端口打开失败");
		msleep(300);

		RUN_BREAK(!m_relay.SetOneIO(relay.gnd, false), "继电器GND端口关闭失败");
		msleep(delay);

		StaticConfig& info = m_hwdConfig->staticCurrent;

		HardwareConfig& hardware = m_defConfig->hardware;

		StaticCurrentMgr staticCurrent;

		RUN_BREAK(!staticCurrent.Open(hardware.staticPort, hardware.staticBaud), S_TO_Q_STR(staticCurrent.GetLastError()));

		RUN_BREAK(!staticCurrent.GetStaticCurrent(info.read), S_TO_Q_STR(staticCurrent.GetLastError()));

		staticCurrent.Close();

		info.result = ((info.read >= info.low) && (info.read < info.high));

		addListItem(Q_SPRINTF("静态电流  %.3f  %s", info.read, OK_NG(info.result)));

		WRITE_LOG("%s,静态电流,%.3f,%.3f,%.3f", OK_NG(info.result), info.read, info.high, info.low);

		RUN_BREAK(!info.result, "检测静态电流失败");

		RUN_BREAK(!m_relay.SetOneIO(relay.gnd, true), "继电器GND端口打开失败");
		msleep(500);

		RUN_BREAK(!m_relay.SetOneIO(relay.staticCur, false), "继电器静态电流表端口关闭失败");
		msleep(300);

		//RUN_BREAK(!m_relay.SetOneIO(relay.acc, true), "继电器ACC IO打开失败");
		//msleep(300);
		result = true;
	} while (false);
	addListItem(Q_SPRINTF("检测静态电流 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Base::checkVoltage()
{
	setCurrentStatus("检测电压");
	bool result = false, success = true, deviceFail = false;
	do
	{
		VoltageConfig* info = m_hwdConfig->voltage;
		for (int i = 0; i < m_jsonTool->getVoltageConfigCount(); i++)
		{
			RUN_BREAK(deviceFail = !m_relay.SetOneIO(info[i].relay, true), "打开继电器失败");
			msleep(1200);

			RUN_BREAK(deviceFail = !m_voltage.ReadVol(&info[i].read), "电压表读取失败");

			(info[i].read >= info[i].low) && (info[i].read <= info[i].high) ? info[i].result = true : info[i].result = success = false;

			addListItem(Q_SPRINTF("%s  %.3f  %s", info[i].name, info[i].read, OK_NG(info[i].result)));

			WRITE_LOG("%s,%s,%.3f,%.3f,%.3f", OK_NG(info[i].result), info[i].name, info[i].read, info[i].high, info[i].low);

			RUN_BREAK(deviceFail = !m_relay.SetOneIO(info[i].relay, false), "关闭继电器失败");
			msleep(300);
		}
		
		RUN_BREAK(deviceFail, getLastError());

		RUN_BREAK(!success, "检测电压失败");

		result = true;
	} while (false);
	addListItem(Q_SPRINTF("检测电压 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Base::clearDtc()
{
	setCurrentStatus("清除DTC");
	bool result = false;
	do
	{
		RUN_BREAK(!m_udsApplyMgr->ClearDiagnosticInformation(), "清除DTC失败");
		result = true;
	} while (false);
	addListItemEx(Q_SPRINTF("清除DTC %s", OK_NG(result)));
	WRITE_LOG("%s 清除DTC", OK_NG(result));
	return result;
}

bool Dt::Base::checkVersion()
{
	setCurrentStatus("检测版本号");
tryAngin:
	bool result = false, success = true;
	do
	{
		QList<int> modify;
		auto info = m_udsConfig->ver;
		for (int i = 0; i < m_jsonTool->getVerConfigCount(); i++)
		{
			if (!m_udsApplyMgr->ReadDataByIdentifier(info[i].did[0], info[i].did[1], &info[i].size, (UCHAR*)info[i].read))
			{
				strcpy(info[i].read, "读取失败");
				success = info[i].result = false;
				addListItem(Q_SPRINTF("%s  %s  %s", info[i].name, info[i].read, OK_NG(info[i].result)));
				continue;
			}

			udsEncodeConvert(&info[i]);

			if (strncmp(info[i].setup, info[i].read, strlen(info[i].setup)))
			{
				info[i].result = false;
				success = false;
				modify.push_back(i);
			}
			else
			{
				info[i].result = true;
			}
			addListItem(Q_SPRINTF("%s  %s  %s", info[i].name, info[i].read, OK_NG(info[i].result)));
			msleep(50);
		}

		/*如果出错,则进行自动修正*/
		if (!success && setQuestionBox("友情提示", "检测版本数据不匹配,\n是否自动修改为正确数据?", true))
		{
			/*修正需要验证,避免作业员私自乱改动*/
			if (!setAuthDlg())
			{
				setMessageBox("提示", "认证失败,无法自动修改为正确数据");
				break;
			}

			bool complete = false;
			for (int i = 0; i < modify.size(); i++)
			{
				complete = m_jsonTool->setVerConfigValue(info[modify[i]].name, "值", info[modify[i]].read);
			}

			if (complete && m_jsonTool->initInstance(true))
			{
				setDetectionLog(BaseTypes::DL_VER);

				addListItem("已自动修正,重新检测版本号");
				goto tryAngin;
			}
			else
			{
				setMessageBox("错误", QString("自动修改为正确数据失败,\n%1,请手动修改").arg(m_jsonTool->getLastError()));
			}
		}

		/*写入最终日志*/
		setDetectionLog(BaseTypes::DL_VER, [&](const int& i)->void {WRITE_LOG("%s %s %s", OK_NG(info[i].result), info[i].name, info[i].read); });

		RUN_BREAK(!success, "检测版本号失败");
		result = true;
	} while (false);
	addListItem(Q_SPRINTF("检测版本号 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Base::checkDtc()
{
	setCurrentStatus("检测DTC");
	bool again = false;
tryAgain:
	bool result = false, success = true;
	QList<int> modify;
	do
	{
		int count = 0;
		uchar dtcInfo[512] = { 0 };
		RUN_BREAK(!m_udsApplyMgr->SafeReadDTCInformation(02, 0xff, &count, dtcInfo), "读取DTC失败");

		auto config = m_udsConfig->dtc;
		for (int i = 0; i < count / 4; i++)
		{
			for (int j = 0; j < m_jsonTool->getDtcConfigCount(); j++)
			{
				if (config[j].ignore)
				{
					continue;
				}

				if ((dtcInfo[i * 4 + 0] == config[j].dtc[0])
					&& (dtcInfo[i * 4 + 1] == config[j].dtc[1])
					&& (dtcInfo[i * 4 + 2] == config[j].dtc[2]))
				{
					modify.push_back(j);
					config[j].dtc[3] = dtcInfo[i * 4 + 3];
					config[j].exist = true;
					success = false;
					addListItem(Q_SPRINTF("%s  存在  %d", config[j].name, config[j].dtc[3]));
				}
			}
		}

		/*如果存在DTC*/
		if (!success && !again)
		{
			RUN_BREAK(!m_udsApplyMgr->ClearDiagnosticInformation(), "清除DTC失败");
			setDetectionLog(BaseTypes::DL_DTC);
			addListItem("清除DTC成功,重新检测DTC");
			again = true;
			goto tryAgain;
		}

		/*如果清除了DTC,第二次重新测试还没有通过,则进行自动修正*/
		if (!success && again)
		{
			/*进行提示该产品存在故障*/
			addListItem("请注意,该产品进行清除DTC,重新测试NG,可能存在故障");

			/*进行自动修正,需要认证*/
			if (setQuestionBox("友情提示", "检测DTC存在异常,\n是否自动忽略存在项目?", true) && setAuthDlg())
			{
				bool complete = true;
				for (int i = 0; i < modify.size(); i++)
				{
					complete = m_jsonTool->setDtcConfigValue(config[modify[i]].name, "忽略", "1");
				}

				if (complete && m_jsonTool->initInstance(true))
				{
					setDetectionLog(BaseTypes::DL_DTC);
					addListItem("已自动修正,重新检测DTC");
					goto tryAgain;
				}
				else
				{
					setMessageBox("错误", QString("自动修改为正确数据失败,\n%1,请手动修改").arg(m_jsonTool->getLastError()));
				}
			}
		}
		RUN_BREAK(!success, "检测DTC失败,该产品可能存在故障,\n请联系管理员.");
		result = true;
	} while (false);

	/*写入最终DTC日志*/
	setDetectionLog(BaseTypes::DL_DTC, [&](const int& j)->void {WRITE_LOG("%s 存在 %d", m_udsConfig->dtc[j].name, m_udsConfig->dtc[j].dtc[3]); });
	addListItem(Q_SPRINTF("检测DTC %s", OK_NG(result)), false);
	return result;
}

void Dt::Base::outputCanLog(bool enable)
{
	m_canConnMgr->EnableDebugInfo(enable);
}

void Dt::Base::saveCanLog(bool enable)
{
	m_canConnMgr->EnableSaveLog(enable);
}

void Dt::Base::setCanLogName(const QString& detectionName, const QString& modelName, const QString& code)
{
	m_canConnMgr->SetDetectionData(GET_DETECTION_DIR(detectionName), Q_TO_C_STR(modelName), Q_TO_C_STR(code));
}

void Dt::Base::flushCanLogBuffer()
{
	m_canConnMgr->NewLogFile();
}

void Dt::Base::clearCanRecvBuffer()
{
	m_canConnMgr->ClearRecBuffer();
}

const int Dt::Base::quickRecvCanMsg(MsgNode* msgNode, const int& maxSize, const int& ms)
{
	return m_canConnMgr->QuickReceive(msgNode, maxSize, ms);
}

bool Dt::Base::autoProcessCanMsg(const int& id, const int& request, MsgProc msgProc, const ulong& delay)
{
	bool result = false, success = false, deviceFail = false;
	do
	{
		MsgNode msgNode[512] = { 0 };
		clearCanRecvBuffer();
		size_t&& startTime = GetTickCount();
		while (true)
		{
			const int&& size = quickRecvCanMsg(msgNode, 512, 100);
			for (int i = 0; i < size; i++)
			{
				if (msgNode[i].id == id)
				{
					if (msgProc == nullptr)
					{
						msleep(1000);
						float current = 0.0f;
						m_power.GetCurrent(&current);

						if (current < 0.1f)
						{
							deviceFail = true;
							break;
						}

						if (current >= m_defConfig->threshold.canRouse)
						{
							success = true;
							break;
						}
					}
					else
					{
						if (msgProc(request, msgNode[i]))
						{
							success = true;
							break;
						}
					}
				}
			}

			RUN_BREAK(deviceFail, "电源未上电");

			RUN_BREAK(success, "CAN报文处理成功");

			RUN_BREAK(GetTickCount() - startTime > delay, "CAN报文处理失败");
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Base::autoTemplateCanFnc(const char* name, const int& id, const int& req, MsgProc proc, MsgList msg, const ulong& delay)
{
	setCurrentStatus(name);
	bool result = false;
	do 
	{
		if (msg.size() != 0)
		{
			m_canSender.AddMsg(msg.begin()[0], delay);
			m_canSender.Start();
		}

		RUN_BREAK(!autoProcessCanMsg(id, req, proc), Q_SPRINTF("%s失败", name));
		result = true;
	} while (false);
	if (msg.size() != 0)
	{
		m_canSender.DeleteOneMsg(msg.begin()[0].id);
	}
	WRITE_LOG("%s %s", OK_NG(result), name);
	addListItemEx(Q_SPRINTF("%s %s", name, OK_NG(result)));
	return result;
}

IConnMgr* Dt::Base::getCanConnect()
{
	return m_canConnMgr;
}

CanSender* Dt::Base::getCanSender()
{
	return &m_canSender;
}

const float& Dt::Base::getCanRouseCur() const
{
	return m_defConfig->threshold.canRouse;
}

CItechSCPIMgr& Dt::Base::getPower()
{
	return m_power;
}

void Dt::Base::setAccessLevel(const int& udsLevel)
{
	m_udsLevel = udsLevel;
}

void Dt::Base::setDiagnosticSession(const int& udsSession)
{
	m_udsSession = udsSession;
}

void Dt::Base::restoreAccessLevel()
{
	m_udsLevel = SAL_LEVEL1;
}

void Dt::Base::restoreDiagnosticSession()
{
	m_udsSession = 0x03;
}

bool Dt::Base::enterSecurityAccess(const uchar& session, const uchar& access)
{
	bool result = false;
	do
	{
		m_canConnMgr->ClearRecBuffer();

		RUN_BREAK(!m_udsApplyMgr->SafeDiagnosticSessionControl(session), "进入扩展模式失败," + getUdsLastError());

		RUN_BREAK(!m_udsApplyMgr->SafeSecurityAccess(access), "安全解锁失败," + getUdsLastError());

		result = true;
	} while (false);
	return result;
}

bool Dt::Base::readDataByDid(const uchar& did0, const uchar& did1, int* size, uchar* data)
{
	return m_udsApplyMgr->ReadDataByIdentifier(did0, did1, size, data);
}

bool Dt::Base::writeDataByDid(const uchar& did0, const uchar& did1, const int& size, const uchar* data)
{
	bool result = false;
	do
	{
		if (!m_udsApplyMgr->DiagnosticSessionControl(m_udsSession))
		{
			break;
		}

		if (!m_udsApplyMgr->SecurityAccess(m_udsLevel))
		{
			break;
		}

		if (!m_udsApplyMgr->WriteDataByIdentifier(did0, did1, size, data))
		{
			break;
		}

		if (!confirmDataByDid(did0, did1, size, data))
		{
			break;
		}
		result = true;
	} while (false);

	if (!result)
	{
		setLastError(getUdsLastError());
	}
	return result;
}

bool Dt::Base::writeDataByDidEx(const uchar* routine, const uchar& did0, const uchar& did1, const int& size, const uchar* data)
{
	bool result = false;
	do
	{
		if (!m_udsApplyMgr->DiagnosticSessionControl(m_udsSession))
		{
			break;
		}

		if (!m_udsApplyMgr->SecurityAccess(m_udsLevel))
		{
			break;
		}

		uchar routineData = 0x01;
		if (!m_udsApplyMgr->RoutineControl(routine[0], routine[1], routine[2], 1, &routineData, 0, 0))
		{
			break;
		}

		if (!m_udsApplyMgr->WriteDataByIdentifier(did0, did1, size, data))
		{
			break;
		}

		if (!confirmDataByDid(did0, did1, size, data))
		{
			break;
		}
		result = true;
	} while (false);

	if (!result)
	{
		setLastError(getUdsLastError());
	}
	return result;
}

bool Dt::Base::confirmDataByDid(const uchar& did0, const uchar& did1, const int& size, const uchar* data)
{
	bool result = false;
	do
	{
		int recvSize = 0;
		uchar buffer[256] = { 0 };

		RUN_BREAK(!readDataByDid(did0, did1, &recvSize, buffer), getUdsLastError());

		RUN_BREAK(size != recvSize, "读取长度对比失败");

		RUN_BREAK(memcmp(data, buffer, size), "对比数据失败");
		result = true;
	} while (false);
	return result;
}

const QString Dt::Base::getUdsLastError()
{
	return G_TO_Q_STR(m_udsApplyMgr->GetLastError());
}

void Dt::Base::initDetectionLog()
{
	m_logList.clear();

	for (size_t i = 0; i < m_jsonTool->getCurrentConfigCount(); i++)
	{
		m_hwdConfig->current[i].read = 0.0f;
		m_hwdConfig->current[i].result = false;
	}

	for (size_t i = 0; i < m_jsonTool->getResConfigCount(); i++)
	{
		m_hwdConfig->res[i].read = 0.0f;
		m_hwdConfig->res[i].result = false;
	}

	for (size_t i = 0; i < m_jsonTool->getVoltageConfigCount(); i++)
	{
		m_hwdConfig->voltage[i].read = 0.0f;
		m_hwdConfig->voltage[i].result = false;
	}

	for (size_t i = 0; i < m_jsonTool->getVerConfigCount(); i++)
	{
		m_udsConfig->ver[i].result = false;
		memset(m_udsConfig->ver[i].read, 0x00, sizeof(m_udsConfig->ver[i].read));
	}

	for (size_t i = 0; i < m_jsonTool->getDtcConfigCount(); i++)
	{
		m_udsConfig->dtc[i].exist = false;
	}
}

void Dt::Base::setDetectionLog(const BaseTypes::DetectionLog& log, const std::function<void(const int&)>& fnc)
{
	if (log == BaseTypes::DL_ALL)
	{
		m_logList.clear();
	}

	if (log == BaseTypes::DL_CUR || log == BaseTypes::DL_ALL)
	{
		for (size_t i = 0; i < m_jsonTool->getCurrentConfigCount(); i++)
		{
			if (!fnc)
			{
				m_hwdConfig->current[i].read = 0.0f;
				m_hwdConfig->current[i].result = false;
			}
			else
			{
				fnc(i);
			}
		}
	}

	if (log == BaseTypes::DL_RES || log == BaseTypes::DL_ALL)
	{
		for (size_t i = 0; i < m_jsonTool->getResConfigCount(); i++)
		{
			if (!fnc)
			{
				m_hwdConfig->res[i].read = 0.0f;
				m_hwdConfig->res[i].result = false;
			}
			else
			{
				fnc(i);
			}
		}
	}
	
	if (log == BaseTypes::DL_VOL || log == BaseTypes::DL_ALL)
	{
		for (size_t i = 0; i < m_jsonTool->getVoltageConfigCount(); i++)
		{
			if (!fnc)
			{
				m_hwdConfig->voltage[i].read = 0.0f;
				m_hwdConfig->voltage[i].result = false;
			}
			else
			{
				fnc(i);
			}
		}
	}
	
	if (log == BaseTypes::DL_VER || log == BaseTypes::DL_ALL)
	{
		for (size_t i = 0; i < m_jsonTool->getVerConfigCount(); i++)
		{
			if (!fnc)
			{
				m_udsConfig->ver[i].result = false;
				memset(m_udsConfig->ver[i].read, 0x00, HWD_BUF);
			}
			else
			{
				fnc(i);
			}
		}
	}
	
	if (log == BaseTypes::DL_DTC || log == BaseTypes::DL_ALL)
	{
		for (size_t i = 0; i < m_jsonTool->getDtcConfigCount(); i++)
		{
			if (!fnc)
			{
				m_udsConfig->dtc[i].exist = false;
			}
			else
			{
				fnc(i);
			}
		}
	}
}

const QString Dt::Base::createLogFile(bool success)
{
	QString result = "";
	do
	{
		QDir dir;
		auto& device = m_defConfig->device;
		QString logDirName(GET_DETECTION_DIR(m_defConfig->device.detectionName));
		/*log/error/20200228/机种_条码_时分秒.csv*/
		QString filePath = QString("./%1/%2/%3/").arg(logDirName, success ? "NOR" : "ERR", Misc::getCurrentDate(true));
		if (!dir.exists(filePath))
		{
			RUN_BREAK(!dir.mkpath(filePath), "创建日志路径失败");
		}
		result = filePath.append(QString("%1_%2_%3.csv").arg(device.modelName, g_code.isEmpty() ? "未知条码" : g_code, Misc::getCurrentTime(true)));
	} while (false);
	return result;
}

bool Dt::Base::writeLog(bool success)
{
	bool result = false;
	do
	{
		QFile file(createLogFile(success));
		RUN_BREAK(!file.open(QFile::WriteOnly), "打开文件失败," + file.errorString());

		QTextStream stream(&file);
		stream << Q_SPRINTF(" ,条形码,%s,\n,检测结果,%s,\n", Q_TO_C_STR(g_code), OK_NG(success));

		for (int i = 0; i < m_logList.size(); i++)
		{
			stream << m_logList[i] << endl;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

void Dt::Base::threadPause()
{
	g_threadWait = true;
	while (g_threadWait) { msleep(100); }
}

bool Dt::Base::threadIsPause()
{
	return g_threadWait;
}

void Dt::Base::threadContinue()
{
	g_threadWait = false;
}

void Dt::Base::threadQuit()
{
	m_connect = false;
	m_quit = true;

	if (threadIsPause())
	{
		closeDevice();
		threadContinue();
	}

	if (isRunning())
	{
		wait(5000);
	}

	quit();
}

void Dt::Base::setScanCodeDlg(bool show)
{
	emit setScanCodeDlgSignal(show);
	show ? threadPause() : threadContinue();
}

void Dt::Base::setUnlockDlg(bool show)
{
	emit setUnlockDlgSignal(show);
	threadPause();
}

void Dt::Base::setMessageBox(const QString& title, const QString& text)
{
	emit setMessageBoxSignal(title, text);
	threadPause();
}

void Dt::Base::setMessageBoxEx(const QString& title, const QString& text, const QPoint& point)
{
	emit setMessageBoxExSignal(title, text, point);
	threadPause();
}

bool Dt::Base::setQuestionBox(const QString& title, const QString& text, bool auth)
{
	bool result = false;
	emit setQuestionBoxSignal(title, text, &result, auth);
	threadPause();
	return result;
}

bool Dt::Base::setQuestionBoxEx(const QString& title, const QString& text, const QPoint& point)
{
	bool result = false;
	emit setQuestionBoxExSignal(title, text, &result, point);
	threadPause();
	return result;
}

void Dt::Base::setTestResult(const BaseTypes::TestResult& testResult)
{
	emit setTestResultSignal(testResult);
}

void Dt::Base::setCurrentStatus(const QString& status, bool systemStatus)
{
	emit setCurrentStatusSignal(status, systemStatus);
}

void Dt::Base::addListItem(const QString& item, bool logItem)
{
	emit addListItemSignal(QString("%1 %2").arg(Misc::getCurrentTime(), item), logItem);
}

void Dt::Base::addListItemEx(const QString& item)
{
	addListItem(item, false); addListItem(item, true);
}

void Dt::Base::clearListItem()
{
	emit clearListItemSignal();
}

bool Dt::Base::setAuthDlg(const int& flag)
{
	bool result = false;
	emit setAuthDlgSignal(&result, flag);
	threadPause();
	return result;
}

void Dt::Base::setLastError(const QString& error)
{
#ifdef QT_DEBUG
	qDebug() << error << endl;
#endif
	m_lastError = error;
}

void Dt::Base::setLastError(const QString& error, bool addItem, bool msgBox)
{
#ifdef QT_DEBUG
	qDebug() << error << endl;
#endif
	m_lastError = error;

	if (addItem)
	{
		addListItem(m_lastError);
	}

	if (msgBox)
	{
		QMessageBox::warning(static_cast<QWidget*>(nullptr), "错误", error);
	}
}

bool Dt::Base::udsEncodeConvert(VersonConfig* config)
{
	bool bRet = false;
	do
	{
		std::string strDataType = config->encode;
		if (strDataType.find("ASCII") != std::string::npos)
		{

		}
		else if (strDataType.find("U08") != std::string::npos)
		{
			for (int i = 8; i < 4 + 8; i++)
			{
				config->read[i] += ('1' - 1);
			}
		}
		else if (strDataType.find("ASCR4") != std::string::npos)
		{
			for (int i = config->size - 4; i < config->size; i++)
			{
				config->read[i] += ('1' - 1);
			}
		}
		else if (strDataType.find("USN") != std::string::npos
			|| strDataType.find("BIN") != std::string::npos
			|| strDataType.find("BCD") != std::string::npos)
		{
			for (int i = 0; i < config->size; i++)
			{
				config->read[i] += ('1' - 1);
			}
		}
		else if (strDataType.find("INT") != std::string::npos)
		{
			UCHAR ucTemp = config->read[0];
			config->read[0] = config->read[3];
			config->read[3] = ucTemp;

			ucTemp = config->read[1];
			config->read[1] = config->read[2];
			config->read[2] = ucTemp;

			int iTemp = *(int*)&config->read[0];
			sprintf(config->read, "%d", iTemp);
		}
		else if (strDataType.find("ASCBCD44") != std::string::npos)
		{
			char szEnd[64] = { 0 };
			strncpy(szEnd, &config->read[7], config->size - 7);
			char szMid[64] = { 0 };
			for (int i = 3; i < 4 + 3; i++)
			{
				char temp[8] = { 0 };
				sprintf(temp, "%02x", config->read[i]);
				sprintf(&szMid[strlen(szMid)], "%s", temp);
			}
			sprintf(&config->read[3], "%s%s", szMid, szEnd);
		}
		else
		{
			break;
		}

		//祛除头、尾的空格
		std::string strVer = config->read;
		strVer.erase(0, strVer.find_first_not_of(" "));
		strVer.erase(strVer.find_last_not_of(" ") + 1);
		strcpy(config->read, strVer.c_str());
		bRet = true;
	} while (false);
	return bRet;
}

/************************************************************************/
/* Dt::Hardware realize                                                     */
/************************************************************************/
Dt::Hardware::Hardware(QObject* parent)
{

}

Dt::Hardware::~Hardware()
{

}

/************************************************************************/
/* Dt::Function realize                                                 */
/************************************************************************/
Dt::Function::Function(QObject* parent)
{

}

Dt::Function::~Function()
{
	if (m_cvAnalyze)
	{
		cvReleaseImage(&m_cvAnalyze);
	}

	if (m_cvPainting)
	{
		cvReleaseImageHeader(&m_cvPainting);
	}

	if (m_cardConfig.name == "MV800")
	{
		m_mv800.DeinitCard();
	}
	else
	{
		SAFE_DELETE(m_mil);
	}
}

bool Dt::Function::initInstance()
{
	bool result = false;
	do
	{
		if (!Dt::Base::initInstance())
		{
			break;
		}

		setCaptureCardAttribute();

		m_cvAnalyze = cvCreateImage(cvSize(m_cardConfig.width, m_cardConfig.height), 8, 3);
		RUN_BREAK(!m_cvAnalyze, "m_cvAnalyze分配内存失败");

		m_cvPainting = cvCreateImageHeader(cvSize(m_cardConfig.width, m_cardConfig.height), 8, 3);
		RUN_BREAK(!m_cvPainting, "m_cvPainting分配内存失败");

		if (m_cardConfig.name == "MV800")
		{
			RUN_BREAK(!m_mv800.InitCard(1), "初始化MV800采集卡失败");
		}
		else
		{
			m_mil = NO_THROW_NEW Cc::Mil(this);
			RUN_BREAK(!m_mil, "Cc::Mil分配内存失败");
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::openDevice()
{
	bool result = false;
	do 
	{
		if (!Dt::Base::openDevice())
		{
			break;
		}

		if (m_cardConfig.name == "MV800")
		{
			if (!m_mv800.Connect(NULL, NULL, m_cardConfig.width, m_cardConfig.height, Cc::Mv800Proc, m_cardConfig.channel, this))
			{
				setLastError("打开MV800采集卡失败," + G_TO_Q_STR(m_mv800.GetLastError()), false, true);
			}
		}
		else
		{
			QString&& dcfFile = QString("Config/%1/ntsc.dcf").arg(DCF_FILE_VER);
			if (!QFileInfo(dcfFile).exists())
			{
				setLastError("MOR采集卡丢失DCF配置文件", false, true);
			}
			else
			{
				m_mil->open(dcfFile, m_cardConfig.channel) ? m_mil->startCapture() : setLastError("打开MOR采集卡失败," + m_mil->getLastError(), false, true);
			}
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::closeDevice()
{
	bool result = false;
	do 
	{
		if (!Dt::Base::closeDevice())
		{
			break;
		}
		m_cardConfig.name == "MV800" ? m_mv800.DisConnect() : m_mil->close();
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::checkCanRouseSleep(const MsgNode& msg, const ulong& delay, LaunchProc launchProc, void* args)
{
	bool result = false, success = false;
	do
	{
		setCurrentStatus("检测CAN唤醒");
		m_canSender.AddMsg(msg, delay);
		m_canSender.Start();
		success = launchProc(args);
		m_canSender.DeleteOneMsg(msg.id);
		WRITE_LOG("%s CAN唤醒", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN唤醒 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN唤醒失败");

		success = false;
		setCurrentStatus("检测CAN休眠");
		size_t&& startTime = GetTickCount();
		float current = 0.0f;
		while (true)
		{
			m_power.GetCurrent(&current);

			if (current <= m_defConfig->threshold.canSleep)
			{
				success = true;
				break;
			}

			if (success || GetTickCount() - startTime >= 20000)
			{
				break;
			}
			msleep(300);
		}

		WRITE_LOG("%s CAN休眠", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN休眠 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN休眠失败");
		m_relay.SetOneIO(m_defConfig->relay.acc, true);
		msleep(300);
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::checkCanRouseSleep(const MsgNode& msg, const ulong& delay, LaunchProcEx lauProcEx, void* args, const int& request, MsgProc msgProc)
{
	bool result = false, success = false;
	do
	{
		setCurrentStatus("检测CAN唤醒");
		m_canSender.AddMsg(msg, delay);
		m_canSender.Start();
		success = lauProcEx(args, request, msgProc);
		m_canSender.DeleteOneMsg(msg.id);
		WRITE_LOG("%s CAN唤醒", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN唤醒 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN唤醒失败");

		success = false;
		setCurrentStatus("检测CAN休眠");
		size_t&& startTime = GetTickCount();
		float current = 0.0f;
		while (true)
		{
			m_power.GetCurrent(&current);

			if (current <= m_defConfig->threshold.canSleep)
			{
				success = true;
				break;
			}

			if (success || GetTickCount() - startTime >= 20000)
			{
				break;
			}
			msleep(300);
		}

		WRITE_LOG("%s CAN休眠", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN休眠 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN休眠失败");
		m_relay.SetOneIO(m_defConfig->relay.acc, true);
		msleep(300);
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::checkCanRouseSleep(const MsgNode& msg, const ulong& delay, const int& id, const int& req, MsgProc msgProc)
{
	bool result = false, success = false;
	do
	{
		setCurrentStatus("检测CAN唤醒");
		m_canSender.AddMsg(msg, delay);
		m_canSender.Start();
		success = autoProcessCanMsg(id, req, msgProc);
		m_canSender.DeleteOneMsg(msg.id);
		WRITE_LOG("%s CAN唤醒", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN唤醒 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN唤醒失败");

		success = false;
		setCurrentStatus("检测CAN休眠");
		size_t&& startTime = GetTickCount();
		float current = 0.0f;
		while (true)
		{
			m_power.GetCurrent(&current);

			if (current <= m_defConfig->threshold.canSleep)
			{
				success = true;
				break;
			}

			if (success || GetTickCount() - startTime >= 20000)
			{
				break;
			}
			msleep(300);
		}

		WRITE_LOG("%s CAN休眠", OK_NG(success));
		addListItemEx(Q_SPRINTF("CAN休眠 %s", OK_NG(success)));
		RUN_BREAK(!success, "CAN休眠失败");
		m_relay.SetOneIO(m_defConfig->relay.acc, true);
		msleep(300);
		result = true;
	} while (false);
	return result;
}

void Dt::Function::setCaptureCardAttribute()
{
	m_cardConfig.name = m_defConfig->device.captureName;
	m_cardConfig.channel = m_defConfig->device.captureChannel.toInt();
	m_cardConfig.width = (m_cardConfig.name == "MV800") ? 720 : 640;
	m_cardConfig.height = 480;
	m_cardConfig.size = m_cardConfig.width * m_cardConfig.height * 3;
}

void Dt::Function::startCaptureCard()
{
	m_cardConfig.name == "MV800" ? m_mv800.StartCapture() : m_mil->startCapture();
}

void Dt::Function::endCaptureCard()
{
	m_cardConfig.name == "MV800" ? m_mv800.EndCapture() : m_mil->endCapture();
}

bool Dt::Function::cycleCapture()
{
	bool result = false, success = true;
	do
	{
		m_capture = true;
		int count = 0;
		while (m_capture)
		{
			msleep(100);
			count++;
			if (count > 50)
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Function::saveAnalyzeImage(const QString& name, const IplImage* image, const CvSize& size)
{
	bool result = false;
	do
	{
		if (!m_defConfig->image.saveLog)
		{
			result = true;
			break;
		}

		const QString path = QString("%1\\FcLog\\Images").arg(Misc::getCurrentDir());
		QDir dir;
		if (!dir.exists(path))
		{
			RUN_BREAK(!dir.mkpath(path), QString("创建目录:%1失败").arg(path));
		}

		const QString& fileName = QString("%1\\%2.jpg").arg(path, name);
		IplImage* newImage = cvCreateImage(size, image->depth, image->nChannels);
		cvCopy(image, newImage);
		showImage(newImage, name);
		cvSaveImage(Q_TO_C_STR(fileName), newImage);
		cvReleaseImage(&newImage);

		result = true;
	} while (false);
	return result;
}

inline void Dt::Function::drawRectOnImage(IplImage* cvImage)
{
	if (m_defConfig->image.showBig && (m_rectType == FcTypes::RT_FRONT_BIG))
	{
		auto rect = m_defConfig->image.bigRect;
		cvRectangleR(cvImage, cvRect(rect[0].startX, rect[0].startY, rect[0].width, rect[0].height), CV_RGB(255, 0, 0), 2);
	}
	else if (m_defConfig->image.showBig && (m_rectType == FcTypes::RT_REAR_BIG))
	{
		auto rect = m_defConfig->image.bigRect;
		cvRectangleR(cvImage, cvRect(rect[1].startX, rect[1].startY, rect[1].width, rect[1].height), CV_RGB(255, 0, 0), 2);
	}
	else if (m_defConfig->image.showSmall && (m_rectType == FcTypes::RT_SMALL))
	{
		auto rect = m_defConfig->image.smallRect;
		for (int i = 0; i < 4; i++)
		{
			cvRectangleR(cvImage, cvRect(rect[i].startX, rect[i].startY, rect[i].width, rect[i].height), CV_RGB(0, 255, 0), 2);
		}
	}
	else
	{

	}
	return;
}

bool Dt::Function::checkRectOnImage(IplImage* cvImage, const rectConfig_t& rectConfig, QString& colorData)
{
	bool result = false, success = true;
	do
	{
		cvSetImageROI(cvImage, cvRect(rectConfig.startX, rectConfig.startY, rectConfig.width, rectConfig.height));

		showImage(cvImage, "ROI");

		std::vector<int> vec;

		/*忽略RGB判断*/
		if (m_defConfig->image.ignoreRgb)
		{
			Mat matHsv;
			cvtColor(cvarrToMat(cvImage), matHsv, COLOR_BGR2HSV);

			size_t size = matHsv.cols * matHsv.rows * matHsv.elemSize();
			size_t red = 0, green = 0, blue = 0;
			size_t count = 0;

			/*求ROI平均值*/
			for (size_t i = 0; i < size; i += matHsv.elemSize())
			{
				blue += matHsv.data[i];
				green += matHsv.data[i + 1];
				red += matHsv.data[i + 2];
				count++;
			}

			red /= count;
			green /= count;
			blue /= count;

			vec.push_back(blue);
			vec.push_back(green);
			vec.push_back(red);

			char color[32] = { 0 };

			if ((vec[0] >= 0 && vec[0] <= 180) && (vec[1] >= 0 && vec[1] <= 255) && (vec[2] >= 0 && vec[2] <= 46))
			{
				strcpy(color, "黑色");
			}
			else if ((vec[0] >= 0 && vec[0] <= 180) && (vec[1] >= 0 && vec[1] <= 43) && (vec[2] >= 46 && vec[2] <= 220))
			{
				strcpy(color, "灰色");
			}
			else if ((vec[0] >= 0 && vec[0] <= 180) && (vec[1] >= 0 && vec[1] <= 35) && (vec[2] >= 221 && vec[2] <= 255))
			{
				strcpy(color, "白色");
			}
			else if (((vec[0] >= 0 && vec[0] <= 10) || (vec[0] >= 156 && vec[0] <= 180)) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "红色");
			}
			else if ((vec[0] >= 11 && vec[0] <= 25) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "橙色");
			}
			else if ((vec[0] >= 26 && vec[0] <= 34) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "黄色");
			}
			else if ((vec[0] >= 35 && vec[0] <= 77) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "绿色");
			}
			else if ((vec[0] >= 78 && vec[0] <= 99) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "青色");
			}
			else if ((vec[0] >= 100 && vec[0] <= 124) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "蓝色");
			}
			else if ((vec[0] >= 125 && vec[0] <= 155) && (vec[1] >= 43 && vec[1] <= 255) && (vec[2] >= 46 && vec[2] <= 255))
			{
				strcpy(color, "紫色");
			}
			else
			{
				strcpy(color, "未知颜色");
			}

			QString imageColor = rectConfig.color;

			/*去除imageColor语法中所有空格*/

			imageColor.remove(QRegExp("\\s"));

			if (imageColor.contains("!="))
			{
				success = (imageColor.mid(2, 4) != color);
			}
			else if (imageColor.contains("=="))
			{
				success = (imageColor.mid(2, 4) == color);
			}
			else
			{
				success = false;
			}
			colorData.sprintf("色彩模型RGB[%03d,%03d,%03d]  配置语法[%s]  分析所得颜色[%s]  %s",
				vec[2], vec[1], vec[0], Q_TO_C_STR(rectConfig.color), color, OK_NG(success));
		}
		else
		{
			/*RGB使用均值算法*/
			CvScalar mean, stddev;
			cvAvgSdv(cvImage, &mean, &stddev);

			for (int i = 0; i < 3; i++)
			{
				vec.push_back(mean.val[i]);
			}

			int limit = 0, upper = 0;
			int rgb[3] = { rectConfig.red,rectConfig.green,rectConfig.blue };
			for (int i = 0; i < 3; i++)
			{
				limit = rgb[i] - rectConfig.deviation;
				upper = rgb[i] + rectConfig.deviation;
				if (!((vec[abs(i - 2)] >= limit) && (vec[abs(i - 2)] <= upper)))
				{
					success = false;
				}
			}
			colorData.sprintf("配置RGB[%03d,%03d,%03d]  实测RGB[%03d,%03d,%03d]  允许误差[%03d]  %s",
				rectConfig.red, rectConfig.green, rectConfig.blue,
				vec[2], vec[1], vec[0], rectConfig.deviation, OK_NG(success));
		}

		if (m_defConfig->image.saveLog)
		{
			auto& image = m_defConfig->image;
			if (m_rectType == FcTypes::RT_SMALL)
			{
				QStringList nameList = { "front","rear","left","right" };
				for (int i = 0; i < SMALL_RECT_; i++)
				{
					if (!memcmp(&image.smallRect[i], &rectConfig, sizeof(RectConfig)))
					{
						saveAnalyzeImage(nameList[i], cvImage, cvSize(rectConfig.width, rectConfig.height));
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < BIG_RECT_; i++)
				{
					if (!memcmp(&image.bigRect[i], &rectConfig, sizeof(RectConfig)))
					{
						saveAnalyzeImage(!i ? "frontBig" : "rearBig", cvImage, cvSize(rectConfig.width, rectConfig.height));
						break;
					}
				}
			}
		}

		cvResetImageROI(cvImage);
		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

void Dt::Function::setRectType(const FcTypes::RectType& rectType)
{
	m_rectType = rectType;
}

const FcTypes::RectType& Dt::Function::getRectType()
{
	return m_rectType;
}

void Dt::Function::restoreRectType()
{
	m_rectType = FcTypes::RT_NO;
}

void Dt::Function::updateImage(const QImage& image)
{
	emit updateImageSignal(image);
}

void Dt::Function::showImage(const IplImage* image, const QString& name)
{
#ifdef QT_DEBUG
	cvNamedWindow(Q_TO_C_STR(name), 0);
	cvShowImage(Q_TO_C_STR(name), image);
	waitKey();
#endif
}

void Dt::Function::setCanId(const int& id)
{
	m_canId = id;
}


/************************************************************************/
/* Dt::Avm realize                                                          */
/************************************************************************/
Dt::Avm::Avm(QObject* parent)
{
	m_detectionType = BaseTypes::DetectionType::DT_AVM;
}

Dt::Avm::~Avm()
{
}

bool Dt::Avm::initInstance()
{
	bool result = false;
	do
	{
		if (!Dt::Function::initInstance())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

void Dt::Avm::tiggerAVMByKey()
{
	m_relay.SetOneIO(m_defConfig->relay.key, true);
	msleep(300);
	m_relay.SetOneIO(m_defConfig->relay.key, false);
	msleep(300);
}

void Dt::Avm::setLedLight(bool _switch)
{
	m_relay.SetOneIO(m_defConfig->relay.led, _switch);
	msleep(300);
}

bool Dt::Avm::checkAVMUseMsg(const MsgNode& msg, const size_t& delay, bool(*judgeProc)(void*), void* args)
{
	return false;
}

bool Dt::Avm::checkAVMUseKey(LaunchProc launchProc, RequestProc requestProc, void* args, const int& request, const ulong& delay)
{
	setCurrentStatus("检测AVM视频");
	bool result = false, success = true;
	do
	{
		if (launchProc)
		{
			RUN_BREAK(!launchProc(args), "启动失败");
		}

		if (delay)
		{
			msleep(delay);
		}

		/*此处增加检测按键电压*/
		KeyVolConfig& keyVol = m_hwdConfig->keyVol;
		RUN_BREAK(!m_voltage.ReadVol(&keyVol.lRead), "读取电压表失败");

		(keyVol.lRead >= keyVol.lLLimit) && (keyVol.lRead <= keyVol.lULimit) ? keyVol.lResult = true : keyVol.lResult = success = false;

		addListItem(Q_SPRINTF("按键低电平  %.3f  %s", keyVol.lRead, OK_NG(keyVol.lResult)));

		tiggerAVMByKey();

		RUN_BREAK(!requestProc(args, request), "进入全景失败");

		setRectType(FcTypes::RT_SMALL);
		msleep(3000);

		RUN_BREAK(!m_voltage.ReadVol(&keyVol.hRead), "读取电压表失败");

		(keyVol.hRead >= keyVol.hLLimit) && (keyVol.hRead <= keyVol.hULimit) ? keyVol.hResult = true : keyVol.hResult = success = false;

		addListItem(Q_SPRINTF("按键高电平  %.3f  %s", keyVol.hRead, OK_NG(keyVol.hResult)));

		RUN_BREAK(!success, "检测按键电压失败");

		RUN_BREAK(!cycleCapture(), "抓图失败");

		const char* name[] = { "前","后","左","右" };
		QString colorData;
		for (int i = 0; i < 4; i++)
		{
			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.smallRect[i], colorData))
			{
				success = false;
			}
			addListItem(QString("%1摄像头小图,%2").arg(name[i], colorData));
		}
		RUN_BREAK(!success, "检测AVM视频失败");
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测AVM视频", OK_NG(result));
	addListItem(Q_SPRINTF("检测AVM视频 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Avm::checkAVMUseKey(LaunchProcEx lauProcEx, void* args, ReqList lauList, MsgProc lauFnc,
	RequestProcEx reqProcEx, ReqList reqList, MsgProc reqFnc, const ulong& delay)
{
	setCurrentStatus("检测AVM视频");
	bool result = false, success = true;
	do
	{
		if (lauProcEx)
		{
			RUN_BREAK(!lauProcEx(args, lauList.begin()[0], lauFnc), "启动失败");
		}

		if (delay)
		{
			msleep(delay);
		}

		/*此处增加检测按键电压*/
		KeyVolConfig& keyVol = m_hwdConfig->keyVol;
		RUN_BREAK(!m_voltage.ReadVol(&keyVol.lRead), "读取电压表失败");

		(keyVol.lRead >= keyVol.lLLimit) && (keyVol.lRead <= keyVol.lULimit) ? keyVol.lResult = true : keyVol.lResult = success = false;

		addListItem(Q_SPRINTF("按键低电平  %.3f  %s", keyVol.lRead, OK_NG(keyVol.lResult)));

		tiggerAVMByKey();

		RUN_BREAK(!reqProcEx(args, reqList.begin()[0], reqFnc), "进入全景失败");

		setRectType(FcTypes::RT_SMALL);
		msleep(3000);

		RUN_BREAK(!m_voltage.ReadVol(&keyVol.hRead), "读取电压表失败");

		(keyVol.hRead >= keyVol.hLLimit) && (keyVol.hRead <= keyVol.hULimit) ? keyVol.hResult = true : keyVol.hResult = success = false;
		addListItem(Q_SPRINTF("按键高电平  %.3f  %s", keyVol.hRead, OK_NG(keyVol.hResult)));

		RUN_BREAK(!success, "检测按键电压失败");

		RUN_BREAK(!cycleCapture(), "抓图失败");

		const char* name[] = { "前","后","左","右" };
		QString colorData;
		for (int i = 0; i < 4; i++)
		{
			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.smallRect[i], colorData))
			{
				success = false;
			}
			addListItem(QString("%1摄像头小图,%2").arg(name[i], colorData));
		}

		RUN_BREAK(!success, "检测AVM视频失败");
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测AVM视频", OK_NG(result));
	addListItem(Q_SPRINTF("检测AVM视频 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Avm::checkAVMUseKey(const int& id, const int& req0, MsgProc msgProc0, const ulong& delay, const int& req1, MsgProc msgProc1)
{
	setCurrentStatus("检测AVM视频");
	bool result = false, success = true;
	do
	{
		RUN_BREAK(!autoProcessCanMsg(id, req0, msgProc0, 20000), "启动失败");

		msleep(delay);

		/*此处增加检测按键电压*/
		KeyVolConfig& keyVol = m_hwdConfig->keyVol;
		RUN_BREAK(!m_voltage.ReadVol(&keyVol.lRead), "读取电压表失败");

		(keyVol.lRead >= keyVol.lLLimit) && (keyVol.lRead <= keyVol.lULimit) ? keyVol.lResult = true : keyVol.lResult = success = false;

		addListItem(Q_SPRINTF("按键低电平  %.3f  %s", keyVol.lRead, OK_NG(keyVol.lResult)));

		tiggerAVMByKey();

		RUN_BREAK(!autoProcessCanMsg(id, req1, msgProc1, 10000), "进入全景失败");

		setRectType(FcTypes::RT_SMALL);
		msleep(3000);

		RUN_BREAK(!m_voltage.ReadVol(&keyVol.hRead), "读取电压表失败");

		(keyVol.hRead >= keyVol.hLLimit) && (keyVol.hRead <= keyVol.hULimit) ? keyVol.hResult = true : keyVol.hResult = success = false;
		addListItem(Q_SPRINTF("按键高电平  %.3f  %s", keyVol.hRead, OK_NG(keyVol.hResult)));

		RUN_BREAK(!success, "检测按键电压失败");

		RUN_BREAK(!cycleCapture(), "抓图失败");

		const char* name[] = { "前","后","左","右" };
		QString colorData;
		for (int i = 0; i < 4; i++)
		{
			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.smallRect[i], colorData))
			{
				success = false;
			}
			addListItem(QString("%1摄像头小图,%2").arg(name[i], colorData));
		}

		RUN_BREAK(!success, "检测AVM视频失败");
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测AVM视频", OK_NG(result));
	addListItem(Q_SPRINTF("检测AVM视频 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Avm::checkAVMFRView(MsgList msgList, const ulong& delay, RequestProc requestProc, void* args, const int& request)
{
	setCurrentStatus("检测前后视图");
	bool result = false, success = true;
	do
	{
		RUN_BREAK(msgList.size() != 2,"前后视图msg.size() != 2");

		/*此处检测需要先切后再切前*/
		const char* name[] = { "前","后","左","右" };
		QString colorData;
		int subscript = -1;
		for (int i = 0; i < msgList.size(); i++)
		{
			subscript = abs(i - 1);

			setRectType(static_cast<FcTypes::RectType>(subscript));

			m_canSender.AddMsg(msgList.begin()[subscript], delay);

			msleep(delay + 1000);

			if (requestProc && !requestProc(args,request))
			{
				success = false;
				setLastError(Q_SPRINTF("进入%s大视图失败", name[subscript]));
				break;
			}

			if (!cycleCapture())
			{
				setLastError("抓图失败");
				success = false;
				break;
			}

			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.bigRect[subscript], colorData))
			{
				success = false;
				setLastError("检测前后视图失败");
			}
			addListItem(QString("%1摄像头大图,%2").arg(name[subscript], colorData));
			m_canSender.DeleteOneMsg(msgList.begin()[subscript].id);
		}

		if (!success)
		{
			break;
		}
		msleep(1000);
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测前后视图", OK_NG(result));
	addListItem(Q_SPRINTF("检测前后视图 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Avm::checkAVMFRView(MsgList msgList, const ulong& delay, RequestProcEx requestProcEx, void* args, ReqList reqList, MsgProc reqFnc)
{
	setCurrentStatus("检测前后视图");
	bool result = false, success = true;
	do
	{
		if (msgList.size() != 2)
		{
			setLastError("前后视图msg.size() != 2");
			break;
		}

		/*此处检测需要先切后再切前,提升效率,所以使用abs计算*/
		const char* name[] = { "前","后","左","右" };
		QString colorData;
		int subscript = -1;
		for (int i = 0; i < msgList.size(); i++)
		{
			subscript = abs(i - 1);

			setRectType(static_cast<FcTypes::RectType>(subscript));

			m_canSender.AddMsg(msgList.begin()[subscript], delay);

			m_canSender.Start();

			//msleep(delay + 1000);

			if (!requestProcEx(args, reqList.begin()[subscript], reqFnc))
			{
				success = false;
				setLastError(Q_SPRINTF("进入%s大视图失败", name[subscript]));
				break;
			}

			if (!cycleCapture())
			{
				setLastError("抓图失败");
				success = false;
				break;
			}

			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.bigRect[subscript], colorData))
			{
				success = false;
				setLastError("检测前后视图失败");
			}
			addListItem(QString("%1摄像头大图,%2").arg(name[subscript], colorData));
			m_canSender.DeleteOneMsg(msgList.begin()[subscript].id);
		}

		if (!success)
		{
			break;
		}
		msleep(1000);
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测前后视图", OK_NG(result));
	addListItem(Q_SPRINTF("检测前后视图 %s", OK_NG(result)), false);
	return result;
}

bool Dt::Avm::checkAVMFRView(MsgList msgList, const ulong& msgDelay, const int& id, ReqList reqList, MsgProc msgProc)
{
	setCurrentStatus("检测前后视图");
	bool result = false, success = true;
	do
	{
		RUN_BREAK(msgList.size() != 2, "前后视图msg.size()!=2");

		/*此处检测需要先切后再切前,提升效率,所以使用abs计算*/
		const char* name[] = { "前","后","左","右" };
		QString colorData;
		int subscript = -1;
		for (int i = 0; i < msgList.size(); i++)
		{
			subscript = abs(i - 1);

			setRectType(static_cast<FcTypes::RectType>(subscript));

			m_canSender.AddMsg(msgList.begin()[subscript], msgDelay);

			m_canSender.Start();

			//msleep(delay + 1000);

			if (!autoProcessCanMsg(id, reqList.begin()[subscript], msgProc))
			{
				success = false;
				setLastError(Q_SPRINTF("进入%s大视图失败", name[subscript]));
				break;
			}

			if (!cycleCapture())
			{
				setLastError("抓图失败");
				success = false;
				break;
			}

			if (!checkRectOnImage(m_cvAnalyze, m_defConfig->image.bigRect[subscript], colorData))
			{
				success = false;
				setLastError("检测前后视图失败");
			}
			addListItem(QString("%1摄像头大图,%2").arg(name[subscript], colorData));
			m_canSender.DeleteOneMsg(msgList.begin()[subscript].id);
		}

		if (!success)
		{
			break;
		}
		msleep(1000);
		result = true;
	} while (false);
	restoreRectType();
	WRITE_LOG("%s 检测前后视图", OK_NG(result));
	addListItem(Q_SPRINTF("检测前后视图 %s", OK_NG(result)), false);
	return result;
}

/************************************************************************/
/* Dt::Dvr realize                                                          */
/************************************************************************/
Dt::Dvr::Dvr(QObject* parent)
{
	m_detectionType = BaseTypes::DetectionType::DT_DVR;
}

Dt::Dvr::~Dvr()
{
	Misc::finishApp("win32_demo.exe");

	SAFE_DELETE(m_dvrClient);

	SAFE_DELETE(m_sfrServer);
}

bool Dt::Dvr::initInstance()
{
	bool result = false;
	do
	{
		if (!Dt::Function::initInstance())
		{
			break;
		}

		m_hashCode.systemStatus = typeid(DvrTypes::SystemStatus).hash_code();

		m_hashCode.wifiStatus = typeid(DvrTypes::WifiStatus).hash_code();

		m_hashCode.ethernetStatus = typeid(DvrTypes::EthernetStatus).hash_code();

		m_hashCode.sdCardStatus = typeid(DvrTypes::SdCardStatus).hash_code();

		m_dvrClient = NO_THROW_NEW Nt::DvrClient;
		RUN_BREAK(!m_dvrClient, "Nt::DvrClient分配内存失败");

		m_sfrServer = NO_THROW_NEW Nt::SfrServer;
		RUN_BREAK(!m_sfrServer, "Nt::SfrServer分配内存失败");

		RUN_BREAK(!m_sfrServer->startListen(), m_sfrServer->getLastError());

		Misc::finishApp("win32_demo.exe");

		QString appName = "\\App\\sfr_client\\bin\\win32_demo.exe";
		RUN_BREAK(!Misc::startApp(appName, SW_NORMAL), QString("启动%1应用程序失败").arg(appName));

		result = true;
	} while (false);
	return result;
}

bool Dt::Dvr::prepareTest(LaunchProc launchProc, void* args)
{
	bool result = false;
	do
	{
		if (!Dt::Base::prepareTest(launchProc, args))
		{
			break;
		}

		RUN_BREAK(!m_relay.SetOneIO(m_defConfig->relay.acc, true), "继电器通讯失败,请检查连接");
		msleep(300);

		startTimeSync();

		addListItem("正在检测系统状态");

		size_t&& startTime = GetTickCount();
		RUN_BREAK(!autoProcessStatus<DvrTypes::SystemStatus>(), QString("系统初始化失败,%1").arg(getLastError()));
		
		addListItem(Q_SPRINTF("检测系统状态正常,用时:%.3f秒", float(GetTickCount() - startTime) / 1000.000f));

		result = true;
	} while (false);
	return result;
}

bool Dt::Dvr::finishTest(bool success)
{
	bool result = false;
	do
	{
		if (!Dt::Base::finishTest(success))
		{
			break;
		}

		stopTimeSync();

		RUN_BREAK(!m_relay.SetOneIO(m_defConfig->relay.acc, false), "继电器通讯失败,请检查连接");

		msleep(300);

		if (getSoundLigth())
		{
			RUN_BREAK(!setSoundLight(false), "继电器通讯失败,请检查连接");
		}
		result = true;
	} while (false);
	return result;
}

void Dt::Dvr::startTimeSync()
{
	MsgNode msg;
	memset(&msg, 0x00, sizeof(msg));
	msg.id = 0x511;
	msg.iDLC = 8;
	SYSTEMTIME time;
	GetLocalTime(&time);

	/*发送时间同步*/
	msg.ucData[0] = time.wSecond << 2;
	msg.ucData[1] = (0x1f & time.wHour) >> 3;
	msg.ucData[2] = (0x07 & time.wHour) << 5;
	msg.ucData[1] |= (0x3f & time.wMinute) << 2;
	msg.ucData[2] |= (0x1f & time.wDay) >> 3;
	msg.ucData[3] = (0x07 & time.wDay) << 5;
	msg.ucData[3] |= (0x1f & (time.wYear - 2014)) >> 4;
	msg.ucData[4] = (0x0f & (time.wYear - 2014)) << 4;
	msg.ucData[3] |= (0x0f & time.wMonth) << 1;
	m_canSender.AddMsg(msg, 1000);
	m_canSender.Start();
	msleep(1000);
	return;
}

void Dt::Dvr::stopTimeSync()
{
	m_canSender.DeleteOneMsg(0x511);
	m_canSender.Stop();
	return;
}

bool Dt::Dvr::setSoundLight(bool enable)
{
	bool result = false;
	do
	{
		if (!m_relay.SetOneIO(m_defConfig->relay.led, enable))
		{
			break;
		}

		msleep(300);

		if (!m_relay.SetOneIO(m_defConfig->relay.sound, true))
		{
			break;
		}

		msleep(150);

		if (!m_relay.SetOneIO(m_defConfig->relay.sound, false))
		{
			break;
		}
		m_soundLight = enable;
		result = true;
	} while (false);
	return result;
}

bool Dt::Dvr::getSoundLigth()
{
	return m_soundLight;
}

void Dt::Dvr::setVlcMediaHwnd(HWND vlcHwnd)
{
	m_vlcHwnd = vlcHwnd;
}

bool Dt::Dvr::vlcRtspStart(const QString& url)
{
	bool result = false;
	do
	{
		RUN_BREAK(url.isEmpty(), "RTSP协议地址为空");

		const char* const vlcArgs[] = {
			//"--rtsp-frame-buffer-size=1000000",
			"--ipv4",
			"--no-prefer-system-codecs",
			"--rtsp-caching=300",
			"--network-caching=500",
			"--rtsp-tcp"
		};

		if (!m_vlcInstance)
		{
			m_vlcInstance = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);
			RUN_BREAK(!m_vlcInstance, "创建vlc实例失败,请确认文件内是否包含\n[lua ,plugins ,libvlc.dll ,libvlccore.dll]");
		}

		if (!m_vlcMedia)
		{
			m_vlcMedia = libvlc_media_new_location(m_vlcInstance, url.toStdString().c_str());
			RUN_BREAK(!m_vlcMedia, "创建vlc媒体失败");
		}

		if (!m_vlcMediaPlayer)
		{
			m_vlcMediaPlayer = libvlc_media_player_new_from_media(m_vlcMedia);
			RUN_BREAK(!m_vlcMediaPlayer, "创建vlc媒体播放器失败");
		}

		RUN_BREAK(!m_vlcHwnd, "请调用setVlcMediaHwnd设置播放控件句柄");

		libvlc_media_player_set_hwnd(m_vlcMediaPlayer, m_vlcHwnd);

		RUN_BREAK(libvlc_media_player_play(m_vlcMediaPlayer) == -1, "VLC媒体播放器播放视频失败");

		result = true;
	} while (false);
	return result;
}

bool Dt::Dvr::vlcRtspStop()
{
	bool result = false;
	do
	{
		if (m_vlcInstance)
		{
			libvlc_release(m_vlcInstance);
			m_vlcInstance = nullptr;
		}

		if (m_vlcMedia)
		{
			libvlc_media_release(m_vlcMedia);
			m_vlcMedia = nullptr;
		}

		if (m_vlcMediaPlayer)
		{
			libvlc_media_player_stop(m_vlcMediaPlayer);
			libvlc_media_player_release(m_vlcMediaPlayer);
			m_vlcMediaPlayer = nullptr;
		}
		result = true;
	} while (false);
	return result;
}

const size_t Dt::Dvr::crc32Algorithm(uchar const* memoryAddr, const size_t& memoryLen, const size_t& oldCrc32)
{
	size_t oldcrc32 = oldCrc32, length = memoryLen, crc32, oldcrc;
	uchar ccc, t;

	while (length--)
	{
		t = (uchar)(oldcrc32 >> 24U) & 0xFFU;
		oldcrc = DvrTypes::crc32Table[t];
		ccc = *memoryAddr;
		oldcrc32 = (oldcrc32 << 8U | ccc);
		oldcrc32 = oldcrc32 ^ oldcrc;
		memoryAddr++;
	}
	crc32 = oldcrc32;
	return crc32;
}

bool Dt::Dvr::crcVerify(const uchar* data, const size_t& length, const size_t& oldCrc)
{
	return (oldCrc == crc32Algorithm((uchar*)data, length, oldCrc));
}

bool Dt::Dvr::getFileUrl(QString& url, const DvrTypes::FilePath& filePath, const char* ip, const ushort& port)
{
	bool result = false;
	do
	{
		msleep(1000);
		int tryAgainCount = 0;

		const size_t sendLen = 0x10;
		if (!m_dvrClient->connectServer(ip, port))
		{
			setLastError("连接到服务器失败");
			break;
		}

	tryAgain:

		/*						    0	 1	  2    3    4    5    6    7    8				9			 10   11*/
		char sendData[sendLen] = { 0xEE,0xAA,0x06,0x00,0x00,0x00,0x10,0x02,(char)filePath,(char)filePath,0x01,0x01 };
		size_t crc32 = crc32Algorithm((uchar*)&sendData[2], 10, 0);
		sendData[12] = crc32 & 0xff;
		sendData[13] = (crc32 >> 8) & 0xff;
		sendData[14] = (crc32 >> 16) & 0xff;
		sendData[15] = (crc32 >> 24) & 0xff;

#ifdef QT_DEBUG
		//system("mode con:cols=100 lines=1000");
		qDebug() << Misc::getCurrentTime() << "开始发送" << endl;
		for (size_t i = 0; i < sendLen; i++)
		{
			printf("[%03u:%02x]\t", i, (uchar)sendData[i]);
		}
		qDebug() << endl << Misc::getCurrentTime() << "发送结束" << endl;
#endif

		//writeNetLog(filePath == DvrTypes::FP_EVT ? "evt_send.txt" : "pho_send.txt", sendData, sendLen);

		if (m_dvrClient->send(sendData, sendLen) == -1)
		{
			setLastError("发送失败");
			break;
		}

		char recvData[BUFF_SIZE] = { 0 };

		int total = m_dvrClient->recv(recvData, DvrTypes::NC_FILE_CTRL, DvrTypes::NS_GET_FILE_LIST);
		if (total == -1)
		{
			setLastError("接收失败," + m_dvrClient->getLastError());
			break;
		}
		else if (total == -2)
		{
			tryAgainCount++;
			if (tryAgainCount >= 20)
			{
				break;
			}
			goto tryAgain;
		}

		writeNetLog(filePath == DvrTypes::FP_EVT ? "evt_recv.txt" : "pho_recv.txt", recvData, total);

#ifdef QT_DEBUG
		qDebug() << Misc::getCurrentTime() << "总长度:" << total << "开始接收" << endl;
		for (size_t i = 0; i < total; i++)
		{
			printf("[%03u:%02x]\t", i, (uchar)recvData[i]);
		}
		qDebug() << endl << Misc::getCurrentTime() << "接收结束" << endl;
#endif

		FileList dvrFileList;
		memset(&dvrFileList, 0x00, sizeof(FileList));
		memcpy(&dvrFileList.listCount, &recvData[8], sizeof(size_t));

		dvrFileList.listCount = dvrFileList.listCount > 100 ? 100 : dvrFileList.listCount;

#ifdef QT_DEBUG
		qDebug() << "文件数量:" << dvrFileList.listCount << endl;
#endif
		/*存在没有获取到情况,所以再次获取,原因可能是??未知*/
		if (dvrFileList.listCount == 0)
		{
			tryAgainCount++;
			if (tryAgainCount >= 20)
			{
				break;
			}
			goto tryAgain;
		}

		char* pointer = &recvData[12];
		const char* dvrPath[] = { "NOR/", "EVT/", "PHO/" };
		const char* dvrType[] = { "NOR_", "EVT_", "PHO_", "_D1_" };
		const char* dvrSuffix[] = { ".mp4", ".jpg" };

		int maxDate = 0, flag = 0;

		for (int i = 0; i < dvrFileList.listCount; i++)
		{
			memcpy(&dvrFileList.fileInfo[i].index, pointer, 2);
			pointer += 2;
			memcpy(&dvrFileList.fileInfo[i].path, pointer, 1);
			pointer++;
			memcpy(&dvrFileList.fileInfo[i].type, pointer, 1);
			pointer++;
			memcpy(&dvrFileList.fileInfo[i].suffix, pointer, 1);
			pointer += 4;
			memcpy(&dvrFileList.fileInfo[i].size, pointer, 4);
			pointer += 4;
			memcpy(&dvrFileList.fileInfo[i].date, pointer, 4);
			pointer += 4;

			if (dvrFileList.fileInfo[i].date >= maxDate)
			{
				maxDate = dvrFileList.fileInfo[i].date;
				flag = i;
			}
		}

		int pathId = dvrFileList.fileInfo[flag].path;
		int typeId = dvrFileList.fileInfo[flag].type;

		if ((pathId < 0 || pathId > 2) || (typeId < 0 || typeId > 3))
		{
			setLastError("获取DVR文件列表数据包异常,\n请检测网络连接是否有波动");
			break;
		}

		url.sprintf("http://%s:%d/%s%s", ip, 8080, dvrPath[pathId], dvrType[typeId]);
		/*此处要减去时差*/
		time_t dvrSecond = dvrFileList.fileInfo[flag].date - 8 * 60 * 60;

		/*通过localtime将秒数转换为 年 月 日 时 分 秒*/
		struct tm* dvrDate = localtime(&dvrSecond);
		if (!dvrDate)
		{
			setLastError("localtime触发一个nullptr异常");
			break;
		}

		url.append(Q_SPRINTF("%04d%02d%02d_%02d%02d%02d_%05d",
			dvrDate->tm_year + 1900,
			dvrDate->tm_mon + 1,
			dvrDate->tm_mday,
			dvrDate->tm_hour,
			dvrDate->tm_min,
			dvrDate->tm_sec,
			dvrFileList.fileInfo[flag].index));
		url.append(dvrSuffix[dvrFileList.fileInfo[flag].suffix]);
		result = true;
	} while (false);
	m_dvrClient->closeConnect();
	return result;
}

bool Dt::Dvr::downloadFile(const QString& url, const QString& dirName, bool isVideo)
{
	bool result = false;
	float networkSpeed = 0.0;
	do
	{
		QString path = QString("%1/%2/%3").arg(Misc::getCurrentDir(), dirName, Misc::getCurrentDate());
		if (!QDir(path).exists())
		{
			QDir dir;
			dir.mkpath(path);
		}

		QString destFile = path + url.mid(url.lastIndexOf("/"));

		//QNetworkAccessManager nam;
		//QUrl qurl(url);
		//QNetworkRequest nr(qurl);
		//QNetworkReply* reply = nam.get(nr);
		//
		//QEventLoop loop;
		//connect(&nam, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
		//loop.exec(QEventLoop::ExcludeUserInputEvents);

		//QByteArray bytes = reply->readAll();
		//QFile file(destFile);
		//if (!file.open(QFile::WriteOnly))
		//{
		//	setLastError(QString("写入%1文件失败,%2").arg(destFile, file.errorString()));
		//	break;
		//}
		//file.write(bytes);
		//file.close();
		//reply->deleteLater();
		//reply = nullptr;
		//return true;
		DeleteUrlCacheEntry(Q_TO_WC_STR(url));
		size_t startDownloadTime = GetTickCount();
		HRESULT downloadResult = URLDownloadToFileA(NULL, Q_TO_C_STR(url), Q_TO_C_STR(destFile), NULL, NULL);
		float endDownloadTime = (GetTickCount() - startDownloadTime) / 1000.0f;

		if (downloadResult == S_OK)
		{
			struct _stat64i32 stat;
			_stat64i32(Q_TO_C_STR(destFile), &stat);
			float fileSize = stat.st_size / 1024.0f / 1024.0f;
			QString downloadInfo = Q_SPRINTF("文件大小:%.2fM,下载用时:%.2f秒,平均速度:%.2fM/秒",
				fileSize, endDownloadTime, fileSize / endDownloadTime);
			/*视频下载需要做网速处理*/
			if (isVideo)
			{
				auto& range = m_defConfig->range;
				networkSpeed = fileSize / endDownloadTime;
				if (networkSpeed >= range.minNetworkSpeed && networkSpeed <= range.maxNetworkSpeed)
				{
					result = true;
				}
				downloadInfo.append(Q_SPRINTF(",网速范围:%.2fM~%.2fM", range.minNetworkSpeed, range.maxNetworkSpeed));
			}
			else
			{
				result = true;
			}
			addListItem(downloadInfo.append(" 成功"));
		}
		else
		{
			setLastError("URLDownloadToFile下载文件失败");
		}
	} while (false);
	if (isVideo)
	{
		WRITE_LOG("%s 网速 %.2f", OK_NG(result), networkSpeed);
	}
	return result;
}

bool Dt::Dvr::checkRayAxis(const QString& url, const QString& dirName)
{
	bool result = true;
	do
	{
		QString localPath = QString("%1/%2/%3/%4").arg(Misc::getCurrentDir(), dirName, Misc::getCurrentDate(), Misc::getFileNameByUrl(url));
		IplImage* grayImage = cvLoadImage(Q_TO_C_STR(localPath), CV_LOAD_IMAGE_GRAYSCALE);
		if (!grayImage)
		{
			result = false;
			setLastError(QString("%1 无效的路径").arg(localPath));
			break;
		}
		grayBuffer_t grayBuffer = { 0 };
		grayBuffer.buffer = (unsigned char*)grayImage->imageData;
		grayBuffer.height = grayImage->height;
		grayBuffer.width = grayImage->width;

		threshold_t threshold = { 0 };
		threshold.xAxis = 100;
		threshold.yAxis = 100;

		axisStandard_t axisStandard = { 0 };
		axisStandard.height = 40;
		axisStandard.width = 120;
		axisStandard.x = 100;
		axisStandard.y = 100;

		cross_t cross = { 0 };
		cross = calculateCross(&grayBuffer, &threshold, &axisStandard);

		if (cross.iResult != 0)
		{
			addListItem("计算光轴失败");
		}
		cvReleaseImage(&grayImage);

		bool success = false;
		auto& range = m_defConfig->range;
		if (cross.x >= range.minRayAxisX && cross.x <= range.maxRayAxisX)
		{
			success = true;
		}
		else
		{
			result = success = false;
		}
		addListItem(Q_SPRINTF("光轴X:%.2f,范围:%.2f~%.2f %s"
			, cross.x, range.minRayAxisX, range.maxRayAxisX
			, success ? "OK" : "NG"));
		WRITE_LOG("%s 光轴X %.2f", OK_NG(success), cross.x);

		if (cross.y >= range.minRayAxisY && cross.y <= range.maxRayAxisY)
		{
			success = true;
		}
		else
		{
			result = success = false;
		}
		addListItem(Q_SPRINTF("光轴Y:%.2f,范围:%.2f~%.2f %s"
			, cross.y, range.minRayAxisY, range.maxRayAxisY
			, success ? "OK" : "NG"));
		WRITE_LOG("%s 光轴Y %.2f", OK_NG(success), cross.y);

		if (cross.angle >= range.minRayAxisA && cross.angle <= range.maxRayAxisA)
		{
			success = true;
		}
		else
		{
			result = success = false;
		}
		addListItem(Q_SPRINTF("光轴角度:%.2f,范围:%.2f~%.2f %s"
			, cross.angle, range.minRayAxisA, range.maxRayAxisA
			, success ? "OK" : "NG"));
		WRITE_LOG("%s 光轴A %.2f", OK_NG(success), cross.angle);
	} while (false);
	return result;
}

bool Dt::Dvr::checkSfr(const QString& url, const QString& dirName)
{
	bool result = false;
	do
	{
		QString localPath = QString("%1/%2/%3/%4")
			.arg(Misc::getCurrentDir(), dirName, Misc::getCurrentDate(), Misc::getFileNameByUrl(url));
		IplImage* source = cvLoadImage(Q_TO_C_STR(localPath));
		if (!source)
		{
			setLastError("加载图像失败");
			break;
		}

		QString destFile = localPath;
		destFile.replace(".jpg", ".bmp");
		cvSaveImage(Q_TO_C_STR(destFile), source);
		cvReleaseImage(&source);

		float value = 0.0f;
		if (!m_sfrServer->getSfr(destFile, value))
		{
			setLastError(m_sfrServer->getLastError());
			break;
		}

		auto& range = m_defConfig->range;
		result = ((value >= range.minSfr) && (value <= range.maxSfr));
		addListItem(Q_SPRINTF("图像解像度:%.2f,范围:%.2f~%.2f %s"
			, value, range.minSfr, range.maxSfr, OK_NG(result)));
		WRITE_LOG("%s 解析度 %.2f", OK_NG(result), value);
	} while (false);
	return result;
}

bool Dt::Dvr::formatSdCard(const DvrTypes::FormatSdCard& flag)
{
	setCurrentStatus("格式化SD卡");
	bool result = false;
	do
	{
		if (flag == DvrTypes::FSC_BY_NETWORK)
		{
			if (!m_dvrClient->connectServer("10.0.0.10", 2000))
			{
				setLastError("连接服务器失败");
				break;
			}

			/*暂停录制*/
			/*							0	1	2	 3    4    5    6    7    8*/
			char pauseData[0x0D] = { 0xee,0xaa,0x03,0x00,0x00,0x00,0x02,0x00,0x00 };
			size_t crc32 = crc32Algorithm((uchar*)&pauseData[2], 7, 0);
			pauseData[9] = crc32 & 0xff;
			pauseData[10] = (crc32 >> 8) & 0xff;
			pauseData[11] = (crc32 >> 16) & 0xff;
			pauseData[12] = (crc32 >> 24) & 0xff;
			if (m_dvrClient->send(pauseData, 0x0D) == -1)
			{
				setLastError("发送失败");
				break;
			}

			char recvData[BUFF_SIZE] = { 0 };
			int total = m_dvrClient->recv(recvData, DvrTypes::NC_FAST_CONTROL, DvrTypes::NS_FAST_CYCLE_RECORD);
			if (total < 0)
			{
				setLastError("接收失败");
				break;
			}

			writeNetLog("pause_recv.txt", recvData, total);

			int data = -1;
			memcpy(&data, &recvData[8], sizeof(int));

#ifdef QT_DEBUG
			qDebug() << "暂停录制返回值:" << data << endl;
#endif
			bool success = (data == 0);

			addListItem(Q_SPRINTF("暂停循环录制 %s", OK_NG(success)));
			RUN_BREAK(!success, "暂停循环录制失败");

			/*							 0    1    2    3    4    5    6    7    8*/
			char sendData[0x0D] = { 0xee,0xaa,0x03,0x00,0x00,0x00,0x12,0x20,0x00 };
			crc32 = crc32Algorithm((uchar*)&sendData[2], 7, 0);
			sendData[9] = crc32 & 0xff;
			sendData[10] = (crc32 >> 8) & 0xff;
			sendData[11] = (crc32 >> 16) & 0xff;
			sendData[12] = (crc32 >> 24) & 0xff;
			if (m_dvrClient->send(sendData, 0x0D) == -1)
			{
				setLastError("发送失败");
				break;
			}

			memset(recvData, 0x00, BUFF_SIZE);
			total = m_dvrClient->recv(recvData, DvrTypes::NC_CONFIG_SET, DvrTypes::NS_FORMAT_SD_CARD);
			if (total < 0)
			{
				setLastError("接收失败" + m_dvrClient->getLastError());
				break;
			}

			//writeNetLog("format_recv.txt", recvData, total);

			data = -1;
			memcpy(&data, &recvData[8], sizeof(int));


#ifdef QT_DEBUG
			qDebug() << "格式化返回值:" << data << endl;
#endif
			if (data != 0)
			{
				setLastError("格式化SD卡失败");
				break;
			}
		}
		result = true;
	} while (false);

	if (flag == DvrTypes::FSC_BY_NETWORK)
	{
		m_dvrClient->closeConnect();
	}
	addListItemEx(Q_SPRINTF("格式化SD卡 %s", OK_NG(result)));
	WRITE_LOG("%s 格式化SD卡", OK_NG(result));
	return result;
}

bool Dt::Dvr::writeNetLog(const char* name, const char* data, const size_t& size)
{
	bool result = false;
	do 
	{
		QString path = QString("./FcLog/NetLog/%1/").arg(Misc::getCurrentDate(true));
		Misc::makePath(path);

		QString fileName(name);
		fileName.insert(0, Misc::getCurrentTime(true));
		path.append(fileName);

		QFile file(path);
		if (!file.open(QFile::WriteOnly))
		{
			setLastError("写入网络日志文件失败," + file.errorString());
			break;
		}

		char buffer[0x10];
		sprintf(buffer, "%s\n", name);
		file.write(buffer, strlen(buffer));
		for (size_t i = 0; i < size; i++)
		{
			memset(buffer, 0x00, sizeof(buffer));
			sprintf(buffer, "0x%2x\t", (uchar)data[i]);
			file.write(buffer, strlen(buffer));
			if ((i % 100 == 0) && i != 0)
			{
				file.write("\r\n", strlen("\r\n"));
			}
		}
		file.close();
		result = true;
	} while (false);
	return result;
}


/************************************************************************/
/* Mc::Mil realize                                                          */
/************************************************************************/
void Cc::Mil::run()
{
	static QImage image;
	IplImage* currentImage = cvCreateImage(cvSize(m_function->m_cardConfig.width, m_function->m_cardConfig.height), 8, 3);
	if (!currentImage)
	{
		setLastError("currentImage分配内存失败");
		return;
	}

	while (!m_quit)
	{
		if (m_function->m_connect && m_capture)
		{
			MbufGetColor(MilImage, M_PACKED + M_BGR24, M_ALL_BANDS, currentImage->imageData);
			MbufClear(MilImage, 0);

			if (m_function->m_capture)
			{
				memcpy(m_function->m_cvAnalyze->imageData, currentImage->imageData, m_function->m_cardConfig.size);
				m_function->m_capture = false;
			}

			m_function->drawRectOnImage(currentImage);

			if (Misc::cvImageToQtImage(currentImage, &image))
			{
				m_function->updateImage(image);
			}
		}
		msleep(40);
	}
	cvReleaseImage(&currentImage);
	quit();
}

void Cc::Mil::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << err << endl;
#endif
	m_lastError = err;
}

Cc::Mil::Mil(QObject* parent)
{
	m_function = reinterpret_cast<Dt::Function*>(parent);
}

Cc::Mil::~Mil()
{
	m_quit = true;

	if (isRunning())
	{
		wait(5000);
	}
	m_function = nullptr;
}

bool Cc::Mil::open(const QString& name,const int& channel)
{
	bool result = false;
	do
	{
		m_quit = false;

		if (channel < 0 || channel > 1)
		{
			setLastError(QString("MOR采集卡通道编号为%1,不支持的通道编号").arg(channel));
			break;
		}

		if (!MappAlloc(M_DEFAULT, &MilApplication))
		{
			setLastError("MappAlloc失败");
			break;
		}

		if (!MsysAlloc(M_SYSTEM_MORPHIS, M_DEF_SYSTEM_NUM, M_SETUP, &MilSystem))
		{
			setLastError("MsysAlloc失败");
			break;
		}

		if (!MdigAllocA(MilSystem, M_DEFAULT, name.toLocal8Bit().data(), M_DEFAULT, &MilDigitizer))
		{
			setLastError("MdigAlloc失败");
			break;
		}

		MIL_INT miX = MdigInquire(MilDigitizer, M_SIZE_X, M_NULL);
		MIL_INT miY = MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL);
		MIL_INT miBand = MdigInquire(MilDigitizer, M_SIZE_BAND, M_NULL);
		MbufAllocColor(MilSystem, miBand, miX, miY, 8L + M_UNSIGNED, M_IMAGE + M_BASIC_BUFFER_PURPOSE, &MilImage);
		MdigControl(MilDigitizer, M_GRAB_MODE, M_SYNCHRONOUS);
		MdigControl(MilDigitizer, M_CAMERA_LOCK, M_ENABLE);

		MdigControl(MilDigitizer, M_GRAB_AUTOMATIC_INPUT_GAIN, M_DISABLE);
		MdigControl(MilDigitizer, M_GRAB_INPUT_GAIN, 50);

		MappControl(M_ERROR, M_PRINT_DISABLE);

		MbufClear(MilImage, 0);

		if (!MilDigitizer)
		{
			setLastError("MilDigitizer失败");
			break;
		}
		MdigControl(MilDigitizer, M_CAMERA_LOCK, M_DISABLE);
		MdigControl(MilDigitizer, M_CHANNEL, m_channel[channel]);
		MdigControl(MilDigitizer, M_CAMERA_LOCK, M_ENABLE);
		MdigGrabContinuous(MilDigitizer, MilImage);
		result = true;
	} while (false);
	return result;
}

void Cc::Mil::close()
{
	m_quit = true;
	MdigHalt(MilDigitizer);
	MbufFree(MilImage);
	MdigFree(MilDigitizer);
	MsysFree(MilSystem);
	MappFree(MilApplication);
}

void Cc::Mil::startCapture()
{
	if (!this->isRunning())
	{
		this->start();
	}
	m_capture = true;
}

void Cc::Mil::endCapture()
{
	m_capture = false;
}

const QString& Cc::Mil::getLastError()
{
	return m_lastError;
}

void WINAPI Cc::Mv800Proc(const uchar* head, const uchar* bits, LPVOID param)
{
	static QImage image;
	Dt::Function* function = reinterpret_cast<Dt::Function*>((static_cast<VideoSteamParam*>(param))->pArgs);
	if (!function)
	{
		return;
	}

	if (function->m_connect)
	{
		function->m_cvPainting->imageData = (char*)bits;
		if (function->m_capture)
		{
			memcpy(function->m_cvAnalyze->imageData, bits, function->m_cardConfig.size);
			cvFlip(function->m_cvAnalyze, function->m_cvAnalyze, 0);
			function->m_capture = false;
		}

		/*将镜像视图转为正常视图*/
		cvFlip(function->m_cvPainting, function->m_cvPainting, 0);

		function->drawRectOnImage(function->m_cvPainting);

		if (Misc::cvImageToQtImage(function->m_cvPainting, &image))
		{
			function->updateImage(image);
		}
	}
	return;
}

/************************************************************************/
/* Nt::DvrClient realize                                                */
/************************************************************************/
Nt::DvrClient::DvrClient()
{

}

Nt::DvrClient::~DvrClient()
{
	if (!m_close)
	{
		closesocket(m_socket);
		WSACleanup();
	}
}

bool Nt::DvrClient::connectServer(const char* ipAddr, const ushort& port, const int& count)
{
	bool result = false;
	do
	{
		if (m_init)
		{
			result = true;
			break;
		}

		memset(m_ipAddr, 0x00, sizeof(m_ipAddr));
		strcpy(m_ipAddr, ipAddr);
		m_port = port;

		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			setLastError("初始化失败");
			break;
		}

		m_socket = socket(AF_INET, SOCK_STREAM, 0);

		if (m_socket == -1)
		{
			setLastError("套接字初始化失败");
			break;
		}

		int timeout = 3000;

		setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
		setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));


		memset(&m_sockAddr, 0x00, sizeof(sockaddr_in));
		m_sockAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = htons(port);

		timeval tv;
		fd_set set;
		ulong argp = 1;
		ioctlsocket(m_socket, FIONBIO, &argp);
		bool success = false;
		int error = -1;
		int length = sizeof(int);
		for (size_t i = 0; i < count; i++)
		{
			if (connect(m_socket, (const sockaddr*)&m_sockAddr, sizeof(m_sockAddr)) == -1)
			{
				tv.tv_sec = 1;
				tv.tv_usec = 0;
				FD_ZERO(&set);
				FD_SET(m_socket, &set);

				if (select(m_socket + 1, NULL, &set, NULL, &tv) > 0)
				{
					getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (char*)&error, &length);
					if (error == 0)
					{
						success = true;
						break;
					}
					else
					{
						success = false;
					}
				}
				else
				{
					success = false;
				}
			}
			else
			{
				success = true;
				break;
			}
		}

		argp = 0;
		ioctlsocket(m_socket, FIONBIO, &argp);

		if (!success)
		{
			setLastError("连接服务器超时");
			break;
		}
		m_init = result = true;
		m_close = false;
	} while (false);
	return result;
}

int Nt::DvrClient::send(char* buffer, int len)
{
	int result = 0, count = 0;
	count = len;

	while (count > 0)
	{
		result = ::send(m_socket, buffer, count, 0);
		if (result == SOCKET_ERROR)
		{
			return -1;
		}

		if (result == 0)
		{
			return len - count;
		}

		buffer += result;
		count -= result;
	}
	return len;
}

/*这边的接收处理和文档上数据协议50%不匹配,技术那边的一群混子的自己都搞不懂写的什么垃圾协议,
此处只能用屏蔽其他垃圾数据包来处理,所以代码逻辑比较乱,水很深,如果你看到了不要去乱改!!!*/
int Nt::DvrClient::recv(char* buffer, const uchar& reqCmd, const uchar& reqSub)
{
	/*先接收前8个字节*/
	char first8[8] = { 0 };

	size_t startTime = GetTickCount();

	/*此while循环用于处理,心跳包*/
	while (true)
	{
		/*判断是否接收失败*/
		memset(first8, 0x00, sizeof(first8));

		if (::recv(m_socket, first8, sizeof(first8), 0) != sizeof(first8))
		{
			setLastError("接收数据失败");
			return -1;
		}

		/*包头1,2*/
		uchar head1 = (uchar)first8[0], head2 = (uchar)first8[1];

		/*判断是否为心跳包*/
		uchar cmd = (uchar)first8[6], sub = (uchar)first8[7];

#ifdef QT_DEBUG
		qDebug("head1:%x,head2:%x\n", head1, head2);
		qDebug("cmd:%x,sub:%x\n", cmd, sub);
		qDebug("first8:0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n\n\n", (uchar)first8[0], (uchar)first8[1],
			(uchar)first8[2], (uchar)first8[3], (uchar)first8[4], (uchar)first8[5], (uchar)first8[6], (uchar)first8[7]);
#endif

		/*判断包头是否正确*/
		/*这里不可以判断包头,因还有很多垃圾数据要处理,如果判断90%会失败*/
		//bool right = ((head1 == 0xEE) && (head2 == 0xAA));
		//if (!right)
		//{
		//	setLastError("数据包头错误");
		//	return -1;
		//}

		/*如果是期望的cmd与sub,则是想要获取的数据,跳出屏蔽心跳包循环*/
		bool right = ((cmd == reqCmd) && (sub == reqSub));
		if (right)
		{
			break;
		}
		else
		{
			/*不知道哪里来的垃圾包头0101,在格式化处会出现,此处屏蔽*/
			if (head1 == 0x01 && head2 == 0x01)
			{
				continue;
			}
			char temp[BUFF_SIZE] = { 0 };
			const char* ptr = temp;
			int count = 0;
			memcpy(&count, &first8[2], sizeof(int));
			count -= 2;
			count += 4;

#ifdef QT_DEBUG
			qDebug() << "else count:" << count << endl;
#endif

			/*此处用来处理心跳包*/
			int bytes = 0;
			while (count > 0)
			{
				bytes = ::recv(m_socket, temp, count, 0);
				count -= bytes;
				ptr += bytes;
			}
		}

		if (GetTickCount() - startTime >= 3000)
		{
			setLastError("接收超时");
			return -2;
		}
	}

	/*数据长度*/
	int dataLength = 0;
	memcpy(&dataLength, &first8[2], sizeof(int));

	///*排除cmd和sub的2字节*/
	//dataLength -= 2;
	
	/*加上自己本身*/
	dataLength += 4;

	/*加上crc4个字节长度*/
	dataLength += 4;
	
	/*总字节长度,加上包头EEAA*/
	int dataTotal = 2 + dataLength;

	/*将前8个字节填充到buffer中*/
	memcpy(buffer, first8, sizeof(first8));


	/*计算协议包除CRC之外长度*/

#ifdef QT_DEBUG
	qDebug() << "数据长度[包含CRC]:" << dataLength << endl;
	qDebug() << "总长度:" << dataTotal << endl;
#endif

	/*因前面处理过了前8个字节,此处需要将指针向后移动8个字节*/
	buffer += sizeof(first8);

	while (dataLength > 0)
	{
		int result = ::recv(m_socket, buffer, dataLength, 0);

		/*如果中间有断开操作*/
		if (result == SOCKET_ERROR)
		{
			return -1;
		}

		/*接收完毕*/
		if (result == 0)
		{
			break;
		}
		buffer += result;
		dataLength -= result;
	}
	return dataTotal;
}

const char* Nt::DvrClient::getIpAddr()
{
	return m_ipAddr;
}

const ushort& Nt::DvrClient::getPort()
{
	return m_port;
}

void Nt::DvrClient::closeConnect()
{
	closesocket(m_socket);
	WSACleanup();
	m_init = false;
	m_close = true;
}

void Nt::DvrClient::setLastError(const QString& error)
{
#ifdef QT_DEBUG
	qDebug() << error << endl;
#endif
	m_lastError = error;
}

const QString& Nt::DvrClient::getLastError()
{
	return m_lastError;
}

/************************************************************************/
/* Nt::SfrServer realize                                                    */
/************************************************************************/
void Nt::SfrServer::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << err << endl;
#endif
	m_lastError = err;
}

Nt::SfrServer::SfrServer()
{
}

Nt::SfrServer::~SfrServer()
{
	m_quit = true;
	closesocket(m_socket);
	WSACleanup();
}

static void sfrServerProc(void* arg)
{
	Nt::SfrServer* sfrServer = (Nt::SfrServer*)arg;
	while (!sfrServer->m_quit)
	{
		sockaddr_in clientAddr;
		int addrLen = sizeof(sockaddr_in);
		SOCKET clientSocket = accept(sfrServer->m_socket, (sockaddr*)&clientAddr, &addrLen);
		if (clientSocket == -1)
		{
			break;
		}
		sfrServer->m_client = clientSocket;
		Sleep(100);
	}
	return;
}

bool Nt::SfrServer::startListen(const ushort& port)
{
	bool result = false;
	do
	{
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;
		if (WSAStartup(sockVersion, &wsaData) != 0)
		{
			setLastError("WSAStartup初始化失败");
			break;
		}

		m_socket = socket(AF_INET, SOCK_STREAM, 0);

		if (m_socket == -1)
		{
			setLastError("SOCKET初始化失败");
			break;
		}

		int timeout = 1000, optval = 1;
		setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
		setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
		setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));

		memset(&m_sockAddr, 0x00, sizeof(sockaddr_in));
		m_sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_port = htons(port);

		if (bind(m_socket, (const sockaddr*)&m_sockAddr, sizeof(SOCKADDR_IN)) == -1)
		{
			setLastError("绑定失败");
			break;
		}

		if (listen(m_socket, 128) == -1)
		{
			setLastError("监听失败");
			break;
		}
		_beginthread(sfrServerProc, 0, this);
		result = true;
	} while (false);
	return result;
}

bool Nt::SfrServer::getSfr(const QString& filePath, float& sfr)
{
	bool result = false;
	do
	{
		int sendLen = 208;
		char sendData[256] = { 0 };

		sprintf(sendData, "$THC001%s", Q_TO_C_STR(filePath));
		sendData[sendLen - 1] = '$';
		int count = ::send(m_client, sendData, sendLen, 0);
		if (count != sendLen)
		{
			setLastError("发送失败");
			break;
		}

		int recvLen = 208;
		char recvData[256] = { 0 };
		count = ::recv(m_client, recvData, recvLen, 0);
		if (count == -1 || recvData[0] != '$')
		{
			sfr = 0.0f;
		}
		else
		{
			if (strncmp(recvData, "$HTR000", 7))
			{
				setLastError("SFR客户端数据异常");
				break;
			}

			if (sscanf(&recvData[7], "%f", &sfr) != 1)
			{
				setLastError("SFR客户端数据异常");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

int Nt::SfrServer::send(SOCKET socket, char* buffer, int len)
{
	int count = len, result = 0;
	while (count > 0)
	{
		result = ::send(socket, buffer, count, 0);
		if (result == -1)
		{
			return -1;
		}

		if (result == 0)
		{
			return len - count;
		}

		buffer += result;
		count -= result;
	}
	return len;
}

int Nt::SfrServer::recv(SOCKET socket, char* buffer, int len)
{
	int count = len, result = 0;
	while (count > 0)
	{
		result = ::recv(socket, buffer, count, 0);
		if (result == -1)
		{
			return -1;
		}

		if (result == 0)
		{
			return len - count;
		}

		buffer += result;
		count -= result;
	}
	return len;
}

void Nt::SfrServer::closeServer()
{
	m_quit = true;
}

const QString& Nt::SfrServer::getLastError()
{
	return m_lastError;
}

/************************************************************************/
/* Misc realize                                                         */
/************************************************************************/
bool Misc::cvImageToQtImage(IplImage* cv, QImage* qt)
{
	bool result = false;
	do
	{
		if (!cv || !qt)
		{
			break;
		}
		cvCvtColor(cv, cv, CV_BGR2RGB);
		*qt = QImage((uchar*)cv->imageData, cv->width, cv->height, cv->widthStep, QImage::Format_RGB888);
		result = true;
	} while (false);
	return result;
}

const QString Misc::getFileNameByUrl(const QString& url)
{
	return url.mid(url.lastIndexOf("/") + 1);
}

const QString Misc::getFileNameByPath(const QString& path)
{
	return path.mid(path.lastIndexOf('\\') + 1);
}

const QString Misc::getCurrentFileName()
{
	QString fileName = "";
	do
	{
		char buffer[MAX_PATH] = { 0 };
		if (!GetModuleFileNameA(NULL, buffer, MAX_PATH))
		{
			break;
		}
		QString fullName(G_TO_Q_STR(buffer));
		fileName = fullName.mid(fullName.lastIndexOf('\\') + 1);
	} while (false);
	return fileName;
}

const QString Misc::getCurrentDir()
{
	char buffer[BUFF_SIZE] = { 0 };
	GetCurrentDirectoryA(BUFF_SIZE, buffer);
	return G_TO_Q_STR(buffer);
}

bool Misc::makePath(const QString& path)
{
	bool result = false;
	do 
	{
		if (!QDir(path).exists())
		{
			QDir dir;
			if (!dir.mkpath(path))
			{
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

const QString Misc::getAppVersion()
{
	QString result = "0.0.0";
	char* nameBuffer = nullptr;
	do
	{
		char fullName[MAX_PATH] = { 0 };
		if (!GetModuleFileNameA(NULL, fullName, MAX_PATH))
		{
			break;
		}

		quint32 nameLen = GetFileVersionInfoSizeA(fullName, 0);
		if (!nameLen)
		{
			break;
		}

		nameBuffer = new(std::nothrow) char[nameLen + 1];
		if (!nameBuffer)
		{
			break;
		}

		bool success = GetFileVersionInfoA(fullName, 0, nameLen, nameBuffer);
		if (!success)
		{
			break;
		}

		struct LanguageCodePage
		{
			WORD language;
			WORD codePage;
		} *translate;

		quint32 queryLen = 0;
		success = VerQueryValue(nameBuffer, (TEXT("\\VarFileInfo\\Translation")), (LPVOID*)&translate, &queryLen);
		if (!success)
		{
			break;
		}
		QString str1, str2;
		str1.setNum(translate->language, 16);
		str2.setNum(translate->codePage, 16);
		str1 = "000" + str1;
		str2 = "000" + str2;
		QString verPath = "\\StringFileInfo\\" + str1.right(4) + str2.right(4) + "\\FileVersion";
		void* queryBuffer = nullptr;
		success = VerQueryValue(nameBuffer, (verPath.toStdWString().c_str()), &queryBuffer, &queryLen);
		if (!success)
		{
			break;
		}
		result = QString::fromUtf16((const unsigned short int*)queryBuffer);
	} while (false);
	SAFE_DELETE_A(nameBuffer);
	return result;
}

void Misc::setAppAppendName(const QString& name)
{
	Misc::Var::appendName = name;
}

bool Misc::renameAppByVersion(QWidget* widget)
{
	bool result = false;
	do
	{
		DeviceConfig device = JsonTool::getInstance()->getParsedDeviceConfig();
		const QString&& user = JsonTool::getInstance()->getUserConfigValue("用户名");
		if (!Misc::Var::appendName.isEmpty())
		{
			device.modelName.append(Misc::Var::appendName);
		}
		QString title, newName;
		title = newName = QString("%1%2检测[%3]").arg(device.modelName, device.detectionName, getAppVersion());
		title = QString("%1[%2][权限:%3]").arg(title, JSON_FILE_VER, user);

		widget->setWindowTitle(title);

		QString oldName(getCurrentFileName());
		newName.append(".exe");
		if (oldName != newName)
		{
			QFile::rename(oldName, newName);
		}
		result = true;
	} while (false);
	return result;
}

bool Misc::startApp(const QString& name, const int& show)
{
	bool result = false;
	do
	{
		/*判断是否有附加参数*/
		QString cmdLine;
		if (name.indexOf(" ") != -1)
		{
			cmdLine = name.mid(name.indexOf(" ") + 1);
		}

		QString destProgram = getCurrentDir() + '\\' + name;

		QString destDirectory = destProgram.mid(0, destProgram.lastIndexOf('\\'));

		HINSTANCE hInstance = ShellExecuteW(NULL, L"open", Q_TO_WC_STR(destProgram),
			cmdLine.isEmpty() ? NULL : Q_TO_WC_STR(cmdLine), Q_TO_WC_STR(destDirectory), show);
		if ((int)hInstance <= 32)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Misc::finishApp(const QString& name)
{
	bool result = false;
	do
	{
		QProcess process;
		process.start(QString("cmd.exe /c tasklist | findstr \"%1\"").arg(name));
		process.waitForFinished();

		QString output(process.readAllStandardOutput().data());

		if (output.indexOf(name) == -1)
		{
			break;
		}
		QProcess::execute("cmd.exe", { "/c","taskkill","/im",name,"/f" });
		result = true;
	} while (false);
	return result;
}

const QString Misc::getCurrentTime(bool fileFormat)
{
	return fileFormat ? QTime::currentTime().toString("hh:mm:ss").remove(':')
		: QTime::currentTime().toString("hh:mm:ss.zzz");
}

const QString Misc::getCurrentDate(bool fileFormat)
{
	return fileFormat ? QDate::currentDate().toString("yyyy-MM-dd").remove('-')
		: QDate::currentDate().toString("yyyy-MM-dd");
}

const QString Misc::getCurrentDateTime(bool fileFormat)
{
	QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	if (fileFormat)
	{
		return dateTime.remove('-').remove(':').remove('.');
	}
	return dateTime;
}

Dt::Tap::Tap(QObject* parent)
{
	m_detectionType = BaseTypes::DT_TAP;
}

Dt::Tap::~Tap()
{
	SAFE_DELETE_A(m_serialPortTool);
}

bool Dt::Tap::initInstance()
{
	bool result = false;
	do
	{
		if (!Dt::Function::initInstance())
		{
			break;
		}

		QFileInfo fileInfo("./App/curl/curl.exe");
		RUN_BREAK(!fileInfo.exists(), "丢失插件./App/curl/curl.exe");
		
		m_serialPortTool = new SerialPortTool[2];
		RUN_BREAK(!m_serialPortTool, "串口工具分配内存失败");

		connect(&m_serialPortTool[0], &SerialPortTool::readyReadSignal, this, &Tap::screenUartHandler);
		connect(&m_serialPortTool[1], &SerialPortTool::readyReadSignal, this, &Tap::screenUartHandler);
		result = true;
	} while (false);
	return result;
}

bool Dt::Tap::openDevice()
{
	bool result = false;
	do 
	{
		if (!Dt::Function::openDevice())
		{
			break;
		}

		SerialPortConfig leftConfig, rigthConfig;
		leftConfig.port = m_defConfig->hardware.expandCom1;
		leftConfig.baud = m_defConfig->hardware.expandBaud1;
		leftConfig.dataBit = 8;
		leftConfig.flow = 0;
		leftConfig.stopBit = 1;
		leftConfig.verify = 2;

		rigthConfig = leftConfig;
		rigthConfig.port = m_defConfig->hardware.expandCom2;
		rigthConfig.baud = m_defConfig->hardware.expandBaud2;

		if (!m_serialPortTool[0].openSerialPort(leftConfig))
		{
			setLastError(Q_SPRINTF("打开串口%d失败", leftConfig.port), false, true);
		}

		if (!m_serialPortTool[1].openSerialPort(rigthConfig))
		{
			setLastError(Q_SPRINTF("打开串口%d失败", rigthConfig.port), false, true);
		}
		result = true;
	} while (false);
	return result;
}

bool Dt::Tap::closeDevice()
{
	bool result = false;
	do 
	{
		if (!Dt::Function::closeDevice())
		{
			break;
		}

		m_serialPortTool[0].closeSerialPort();
		m_serialPortTool[1].closeSerialPort();
		result = true;
	} while (false);
	return result;
}

bool Dt::Tap::checkUSBByJson(const QString& url)
{
	setCurrentStatus("检测USB");
	bool result = false;
	do
	{
		QProcess process;
		process.start("./App/curl/curl.exe -i " + url);
		RUN_BREAK(!process.waitForFinished(10000),QString("连接%1失败").arg(url));

		QByteArray bytes = process.readAllStandardOutput();
		QString output(bytes.data());
		int start = output.lastIndexOf("{");
		int end = output.lastIndexOf("}");
		QString json = output.mid(start, end);

		QJsonParseError jsonError;
		QJsonDocument serverJson = QJsonDocument::fromJson(json.toLocal8Bit().data(), &jsonError);
		RUN_BREAK(jsonError.error != QJsonParseError::NoError,"服务器JSON格式错误");

		addListItem(QString("服务器JSON配置:\n%1").arg(serverJson.toJson().data()));
		QString fileName = "./Config/TAPUSBJson.json";
		if (!QFileInfo(fileName).exists())
		{
			QFile file(fileName);
			RUN_BREAK(!file.open(QFile::WriteOnly),"写入TAPUSBJson失败");
			file.write(serverJson.toJson());
			file.close();
		}

		QFile file(fileName);
		RUN_BREAK(!file.open(QFile::ReadOnly), "读取TAPUSBJson失败");
		bytes = file.readAll();
		file.close();

		QJsonDocument configJson(QJsonDocument::fromJson(bytes, &jsonError));
		RUN_BREAK(jsonError.error != QJsonParseError::NoError, QString("%1格式错误").arg(fileName));

		RUN_BREAK(!(serverJson == configJson), "JSON文件配置信息对比失败");
		result = true;
	} while (false);
	WRITE_LOG("%s 检测USB", OK_NG(result));
	addListItemEx(Q_SPRINTF("检测USB %s", OK_NG(result)));
	return result;
}

void Dt::Tap::screenUartHandler(const QString& port, const QByteArray& bytes)
{
	do
	{
		QString hex = bytes.toHex();
		if (hex.length() != 8)
		{
			break;
		}

		QStringList dataList;
		for (int i = 0; i <= 3; i++)
		{
			dataList[i] = hex.mid(i * 2, 2);
		}

		bool valid = true;
		for (int i = 0; i < dataList.length(); i++)
		{
			if (dataList.at(i).isEmpty())
			{
				valid = false;
				break;
			}
		}

		if (!valid)
		{
			break;
		}

		if (!(dataList.at(0) == "80" && dataList.at(1) == "01" && dataList.at(2) == "01"))
		{
			break;
		}

		if (((0 - dataList.at(2).toInt(nullptr, 16)) & 0xff) == dataList.at(3).toInt(nullptr, 16))
		{
			for (int i = 0; i < 2; i++)
			{
				//if (m_dataResult[i].portName == portName)
				//{
				//	m_dataResult[i].isValid = true;
				//}
			}
		}
	} while (false);
	return;
}

Dt::Module::Module(QObject* parent)
{
}

Dt::Module::~Module()
{
}
