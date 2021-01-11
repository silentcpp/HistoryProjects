#include "Function.h"

Fnc::BAIC::BAIC(QObject* parent)
{
	setSysStatusMsg(DvrTypes::SSM_BAIC);
	setSdCardStatus(DvrTypes::SCS_NORMAL);
	setSystemStatus(DvrTypes::SS_GENERAL_RECORD);
	setAddressPort("10.0.0.10", 2000);
}

Fnc::BAIC::~BAIC()
{

}

bool Fnc::BAIC::setOtherAction()
{
	MsgNode msg = { 0 };
	msg.id = 0x511;
	msg.dlc = 8;
	SYSTEMTIME time;
	GetLocalTime(&time);

	/*发送时间同步*/
	msg.data[0] = time.wSecond << 2;
	msg.data[1] = (0x1f & time.wHour) >> 3;
	msg.data[2] = (0x07 & time.wHour) << 5;
	msg.data[1] |= (0x3f & time.wMinute) << 2;
	msg.data[2] |= (0x1f & time.wDay) >> 3;
	msg.data[3] = (0x07 & time.wDay) << 5;
	msg.data[3] |= (0x1f & (time.wYear - 2014)) >> 4;
	msg.data[4] = (0x0f & (time.wYear - 2014)) << 4;
	msg.data[3] |= (0x0f & time.wMonth) << 1;
	m_canSender.AddMsg(msg, 1000);
	msleep(1000);
	return true;
}

Fnc::CHJAutoMotive::CHJAutoMotive(QObject* parent)
{
	setSysStatusMsg(DvrTypes::SSM_CHJ);
	setAddressPort("192.168.42.1", 2000); 
}

Fnc::CHJAutoMotive::~CHJAutoMotive()
{

}

bool Fnc::CHJAutoMotive::setOtherAction()
{
	bool result = false;
	do
	{
		m_canSender.AddMsg({ 0x440,8,{0} }, 100, ST_Event, 10);
		msleep(1000);
		m_canSender.AddMsg(SEND_PROC_FNC() {
			time_t tm = time(NULL) * 1000;
			uchar temp[6] = { 0 };
			memcpy(temp, &tm, 6);
			FMSG.id = 0x179;
			FMSG.dlc = 8;
			for (int i = 1; i <= 6; ++i)
				FMSG.data[i] = temp[6 - i];
			FMSG.data[7] = 0x21;
		}, 10);
		m_startGetCur = true;
		m_vector.clear();
		RUN_BREAK(0 >= (!m_startThread ? _beginthread(getCurrentThread, NULL, this) : true), "创建getCurrentThread失败");
		result = true;
	} while (false);
	return result;
}

bool Fnc::CHJAutoMotive::checkSn()
{
	setCurrentStatus("检测序列号");
	bool result = false;
	do
	{
		int size = 0;
		uchar readData[32] = { 0 }, cmpData[32] = { 0 };
		RUN_BREAK(!readDataByDid(0xf1, 0x8c, &size, readData), "读取序列号失败," + getUdsLastError());
		RUN_BREAK(size != 16, "序列号长度错误");
		sprintf((char*)cmpData, "M01 %s", Q_TO_C_STR(g_code.right(10)));
		RUN_BREAK(memcmp(readData, cmpData, 16), "序列号对比失败");
		result = true;
	} while (false);
	WRITE_LOG("%s 检测序列号", OK_NG(result));
	addListItemEx(Q_SPRINTF("检测序列号 %s", OK_NG(result)));
	return result;
}

bool Fnc::CHJAutoMotive::checkMaxCurrent()
{
	setCurrentStatus("检测最大电流");
	bool result = false, success = false;
	float current = 0.0f, minRange = 0.0f, maxRange = 0.0f;
	do
	{
		RUN_BREAK(m_vector.empty(), "获取电流列表为空");
		qSort(m_vector.begin(), m_vector.end());
		current = m_vector.back();
		minRange = m_defConfig->range.maxCurrent0;
		maxRange = m_defConfig->range.maxCurrent1;
		success = (current >= minRange && current <= maxRange);
		addListItem(Q_SPRINTF("检测最大电流  %.2fA  %.2fA~%.2fA  %s", current, minRange, maxRange, OK_NG(success)));
		RUN_BREAK(!success, "检测最大电流失败");
		result = true;
	} while (false);
	m_startGetCur = false;
	WRITE_LOG("%s 检测最大电流 %.2f %.2f %.2f", OK_NG(result), current, minRange, maxRange);
	addListItem(Q_SPRINTF("检测最大电流 %s", OK_NG(result)), false);
	return result;
}

bool Fnc::CHJAutoMotive::checkRecord(const ulong& timeout)
{
	setCurrentStatus("检测紧急录制");
	bool result = false, success = false;
	do
	{
		addListItem("检测紧急录制中,请耐心等待...");
		m_canSender.AddMsg({ 0x39a,8,{0} }, 100, ST_Event, 3);
		msleep(300);
		m_canSender.AddMsg({ 0x39a,8,{0,0,0,0,2} }, 100, ST_Event, 3);
		msleep(300);
		RUN_BREAK(!setSoundLight(true), "打开音响和灯光失败");
		success = autoProcessStatus(DvrTypes::SS_HARDWARE_KEY, timeout);
		addListItem(Q_SPRINTF("触发紧急录制 %s", OK_NG(success)));
		m_canSender.AddMsg({ 0x39a,8,{0} }, 100, ST_Event, 3);
		msleep(300);
		RUN_BREAK(!success, "触发紧急录制失败");
		result = true;
	} while (false);
	m_canSender.DeleteOneMsg(0x39a);
	WRITE_LOG("%s 检测紧急录制", OK_NG(success));
	addListItemEx(Q_SPRINTF("检测紧急录制 %s", OK_NG(success)));
	return result;
}

bool Fnc::CHJAutoMotive::writeDate()
{
	setCurrentStatus("写入生产日期");
	bool result = false;
	do
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		uchar data[32] = { 0 };
		data[0] = time.wYear % 100;
		data[1] = time.wMonth;
		data[2] = time.wDay;

		RUN_BREAK(!writeDataByDidEx({ 0x01, 0xFD, 0x00,0x00,0x00 }, 0xf1, 0x8b, 3, data), "写入生产日期失败," + getUdsLastError());
		result = true;
	} while (false);
	WRITE_LOG("%s 写入生产日期", OK_NG(result));
	addListItemEx(Q_SPRINTF("写入生产日期 %s", OK_NG(result)));
	return result;
}

void Fnc::CHJAutoMotive::getCurrentThread(void* args)
{
	DEBUG_INFO_EX("获取电流线程ID:%lu已启动", GetCurrentThreadId());
	Fnc::CHJAutoMotive* self = static_cast<Fnc::CHJAutoMotive*>(args);
	self->m_startThread = true;
	float current = 0.0f;
	while (!self->m_quit)
	{
		if (self->m_connect && self->m_startGetCur)
		{
			if (!self->m_power.GetCurrent(&current))
			{
				self->setLastError("getCurrentThread获取电流失败");
				break;
			}
			self->m_vector.push_back(current);
		}
		msleep(100);
	}
	self->m_startThread = false;
	DEBUG_INFO_EX("获取电流线程ID:%lu已退出", GetCurrentThreadId());
}

bool Fnc::CHJAutoMotive::getWifiInfo(bool rawData, bool showLog)
{
	bool result = false, success = false;
	do
	{
		memset(&m_wifiInfo, 0x00, sizeof(WIFIInfo));
		if (showLog) addListItem("正在获取WIFI信息...");
		const int account = 0x515, password = 0x516;
		success = autoProcessCanMsgEx({ account ,password }, { 0 ,0 },
			MSG_PROC_FNC(&)
		{
			if (FMSG.id == account)
			{
				if (rawData)
				{
					memcpy(m_wifiInfo.account, FMSG.data, 8);
				}
				else
				{
					sprintf(m_wifiInfo.account, "M01_DVR_%02X%02X%02X%02X%02X%02X",
						FMSG.data[0], FMSG.data[1], FMSG.data[2],
						FMSG.data[3], FMSG.data[4], FMSG.data[5]);
				}
			}
			else
			{
				sprintf(m_wifiInfo.password, "%c%c%c%c%c%c%c%c",
					FMSG.data[0], FMSG.data[1], FMSG.data[2],
					FMSG.data[3], FMSG.data[4], FMSG.data[5],
					FMSG.data[6], FMSG.data[7]);
			}
			return true;
		}
		);
		strcpy(m_wifiInfo.mode, MODE_MANUAL);
		strcpy(m_wifiInfo.auth, AUTH_WPA2PSK);
		strcpy(m_wifiInfo.encrypt, ENCR_AES);
		if (showLog)
		{
			addListItem(Q_SPRINTF("获取WIFI信息 %s", OK_NG(success)));
			addListItem(Q_SPRINTF("WIFI名称:%s WIFI密码:%s", m_wifiInfo.account, m_wifiInfo.password));
			addListItem(Q_SPRINTF("连接模式:%s 认证方式:%s 加密方式:%s", m_wifiInfo.mode, m_wifiInfo.auth, m_wifiInfo.encrypt));
		}

		if (!success)
			break;
		result = true;
	}
	while (false);
	return result;
}

bool Fnc::GAC::writeSn()
{
	//VD331A5K0020B2202123
	//SE305A20002050220999
	setCurrentStatus("写入序列号");
	bool result = false, convert = false;
	do
	{
		uchar data[32] = { 0 };
		int size = 0;
		RUN_BREAK(!generateSn(data, &size), "条码为空");
		RUN_BREAK(!writeDataByDid(0xf1, 0x8c, size, data), "写入序列号失败," + getUdsLastError());
		result = true;
	} while (false);
	WRITE_LOG("%s 写入序列号", OK_NG(result));
	addListItemEx(Q_SPRINTF("写入序列号 %s", OK_NG(result)));
	return result;
}

bool Fnc::GAC::checkSn()
{
	setCurrentStatus("检测序列号");
	bool result = false, convert = false;
	do
	{
		uchar readData[32] = { 0 };
		int readSize = 0;
		RUN_BREAK(!readDataByDid(0xf1, 0x8c, &readSize, readData), "读取序列号失败," + getUdsLastError());
		RUN_BREAK(readSize != 16, "读取序列号长度不等于16");

		uchar cmpData[32] = { 0 };
		RUN_BREAK(!generateSn(cmpData), "条码为空");
		RUN_BREAK(memcmp(readData, cmpData, 8), "序列号对比失败");
		result = true;
	} while (false);
	WRITE_LOG("%s 检测序列号", OK_NG(result));
	addListItemEx(Q_SPRINTF("检测序列号 %s", OK_NG(result)));
	return result;
}

bool Fnc::GAC::generateSn(uchar* data, int* const size)
{
	bool result = false, convert = false;
	do
	{
		if (g_code.isEmpty())
			break;

		if (size)
			*size = 16;

		int&& seriesNumber = g_code.right(3).toInt();
		QString lineNumber = g_code.right(5).left(2);
		int&& year = g_code.right(10).left(2).toInt();
		int&& month = g_code.right(8).left(1).toInt(&convert, 16);
		RUN_BREAK(!convert || month > 12, "条码中月份不符合规则");

		int&& day = g_code.right(7).left(2).toInt();
		data[0] = seriesNumber >> 16;
		data[1] = seriesNumber >> 8;
		data[2] = seriesNumber;
		data[3] = Q_TO_C_STR(lineNumber)[0];
		data[4] = Q_TO_C_STR(lineNumber)[1];
		data[5] = year;
		data[6] = month;
		data[7] = day;
		result = true;
	} while (false);
	return result;
}
