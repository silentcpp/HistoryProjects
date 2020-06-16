#include "FunctionThread.h"

extern QString g_code;
using namespace Dt;
using namespace BaseTypes;

bool FunctionThread::writeSN()
{
	setCurrentStatus("写入序列号");
	bool result = false, convert = false;
	do
	{
		//VD331A5K0020B2202123
		int&& seriesNumber = g_code.right(3).toInt();
		ushort&& lineNumber = g_code.right(5).left(2).toUShort();
		int&& year = g_code.right(10).left(2).toInt();
		int&& month = g_code.right(8).left(1).toInt(&convert, 16);
		RUN_BREAK(!convert || month > 12, "条码中月份不符合规则");

		int&& day = g_code.right(7).left(2).toInt();
		int sendSize = 16;
		uchar sendData[32] = { 0 };
		sendData[0] = seriesNumber >> 16;
		sendData[1] = seriesNumber >> 8;
		sendData[2] = seriesNumber;
		sendData[3] = lineNumber >> 8;
		sendData[4] = lineNumber;
		sendData[5] = year;
		sendData[6] = month;
		sendData[7] = day;

		RUN_BREAK(!writeDataByDid(0xf1, 0x8c, sendSize, sendData), "写入序列号失败");
		result = true;
	} while (false);
	WRITE_LOG("%s 写入序列号", OK_NG(result));
	addListItemEx(Q_SPRINTF("写入序列号 %s", OK_NG(result)));
	return result;
}

bool FunctionThread::checkDVRFunction()
{
	setCurrentStatus("检测DVR功能");
	bool result = false, success = false;
	do
	{
		/*发送时间同步*/
		SYSTEMTIME time;
		GetLocalTime(&time);
		MsgNode timeSync = { 0 };
		timeSync.id = 0x35A;
		timeSync.iDLC = 8;
		timeSync.ucData[0] |= (time.wYear - 2000) & 0xff;
		timeSync.ucData[1] |= (time.wMonth & 0x0f) << 4;
		timeSync.ucData[1] |= (time.wDay & 0x1f) >> 1;
		timeSync.ucData[2] |= (time.wDay & 0x01) << 7;
		timeSync.ucData[2] |= (time.wHour & 0x1f) << 2;
		timeSync.ucData[2] |= (time.wMinute & 0x3f) >> 4;
		timeSync.ucData[3] |= (time.wMinute & 0x0f) << 4;
		timeSync.ucData[4] |= 1 & 0x3f;
		timeSync.ucData[3] |= (time.wSecond & 0x3f) >> 2;
		timeSync.ucData[4] |= (time.wSecond & 0x03) << 6;

		m_canSender.AddMsg(timeSync, 500);
		m_canSender.Start();
		msleep(500);

		MsgNode msg;
		memset(&msg, 0x00, sizeof(MsgNode));
		msg.id = 0x54;
		msg.iDLC = 8;

#if REPEAT_TEST
		int repeat = 0;
	tryAgain:
#endif
		/*结束循环录制*/
		msg.ucData[2] = 0x10;
		msg.ucData[3] = 0x01;
		msg.ucData[4] = 0x44;
		msg.ucData[5] = 0xB3;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		m_canSender.Start();
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		/*进入四分格请求*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x2B;
		msg.ucData[4] = 0x32;
		msg.ucData[5] = 0x78;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		m_canSender.Start();
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		/*DVR拍照指令*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x15;
		msg.ucData[4] = 0x84;
		msg.ucData[5] = 0xBB;
		m_canSender.AddMsg(msg, 50, ST_Event, 3);
		msleep(150);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 50, ST_Event, 3);
		//msleep(3000);

		size_t&& startTime = GetTickCount();
		int size = 0;
		uchar buffer[32] = { 0 };
		while (true)
		{
			memset(buffer, 0x00, sizeof(buffer));

			RUN_BREAK(!readDataByDid(0xFF, 0x1D, &size, buffer), getUdsLastError());

			OUTPUT_DEBUG_INFO("拍照 0x%x", buffer[0]);

			if (buffer[0] == 0x01)	success = true;

			if (buffer[0] == 0x02)	break;

			if (success || GetTickCount() - startTime >= 3000)	break;

			msleep(100);
		}

#if REPEAT_TEST
		if (!success && repeat < 3)
		{
			addListItem(Q_SPRINTF("DVR拍照重复测试%d次", repeat + 1));
			repeat++;
			goto tryAgain;
		}
#endif

		WRITE_LOG("%s DVR拍照", OK_NG(success));
		addListItemEx(Q_SPRINTF("DVR拍照 %s", OK_NG(success)));
		RUN_BREAK(!success, "DVR拍照失败," + getLastError());

		msleep(1000);

#if !URGENT_DELIVERY
		/*紧急录制*/
		memset(&msg, 0x00, sizeof(MsgNode));
		msg.id = 0x1AE;
		msg.iDLC = 8;
		msg.ucData[0] = 0xA0;
		m_canSender.AddMsg(msg, 20, ST_Period, 3);
		msleep(100);
		m_canSender.DeleteOneMsg(0x1AE);

		setLedLight(true);
		success = false;
		startTime = GetTickCount();
		addListItem("DVR紧急录制中...");
		while (true)
		{
			memset(buffer, 0x00, sizeof(buffer));
			
			RUN_BREAK(!readDataByDid(0xFF, 0x1C, &size, buffer), getUdsLastError());

			OUTPUT_DEBUG_INFO("紧急录制 0x%x", buffer[0]);

			if (buffer[0] == 0x01)	break;

			if (buffer[0] == 0x02)	success = true;

			if (success || GetTickCount() - startTime >= 20000) break;

			msleep(100);
		}
		setLedLight(false);
		WRITE_LOG("%s DVR紧急录制", OK_NG(success));
		addListItemEx(Q_SPRINTF("DVR紧急录制 %s", OK_NG(success)));
		RUN_BREAK(!success, "DVR紧急录制失败," + getLastError());
		msleep(1000);
#endif
		result = true;
	} while (false);
	m_canSender.DeleteOneMsg(0x35A);
	addListItem(Q_SPRINTF("检测DVR功能 %s", OK_NG(result)));
	return result;
}

bool FunctionThread::checkDVRPlayback()
{
#if URGENT_DELIVERY
	return true;
#endif
	setCurrentStatus("检测DVR回放");
	bool result = false;
	do
	{
		MsgNode msg;
		memset(&msg, 0x00, sizeof(MsgNode));
		msg.id = 0x54;
		msg.iDLC = 8;

		/*相册界面坐标*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x2B;
		msg.ucData[4] = 0x52;
		msg.ucData[5] = 0xE0;
		m_canSender.AddMsg(msg, 500, ST_Event, 3);
		m_canSender.Start();
		msleep(1500);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 500, ST_Event, 3);
		msleep(1500);

		/*发送目录切换指令到紧急录制*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x02;
		msg.ucData[4] = 0xC2;
		msg.ucData[5] = 0x13;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		/*发送开始回放指令*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x0C;
		msg.ucData[4] = 0xD0;
		msg.ucData[5] = 0xBC;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		/*进度条跳转到第19s*/
		msg.ucData[2] = 0x10;
		msg.ucData[3] = 0x28;
		msg.ucData[4] = 0x23;
		msg.ucData[5] = 0x73;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		RUN_BREAK(!setQuestionBoxEx("提示", "DVR是否回放?"), "DVR回放失败");

		/*退出回放指令*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x00;
		msg.ucData[4] = 0xA0;
		msg.ucData[5] = 0x36;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		result = true;
	} while (false);
	WRITE_LOG("%s 检测DVR回放", OK_NG(result));
	addListItemEx(Q_SPRINTF("检测DVR回放 %s", OK_NG(result)));
	return result;
}

bool FunctionThread::formatSDCard()
{
	setCurrentStatus("格式化SD卡");
	bool result = false, success = false;
	do
	{
		MsgNode msg = { 0 };
		msg.id = 0x54;
		msg.iDLC = 8;

		/*进入设置界面*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x2A;
		msg.ucData[4] = 0x44;
		msg.ucData[5] = 0xBF;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		m_canSender.Start();
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

#if REPEAT_TEST
		int repeat = 0;
	tryAgain:
#endif
		/*格式化SD卡请求*/
		msg.ucData[2] = 0x10;
		msg.ucData[3] = 0x1A;
		msg.ucData[4] = 0x62;
		msg.ucData[5] = 0xA2;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		/*确认SD卡格式化请求*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x1F;
		msg.ucData[4] = 0x83;
		msg.ucData[5] = 0x51;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		//msleep(3000);

		size_t&& startTime = GetTickCount();
		int size = 0;
		uchar buffer[32] = { 0 };
		addListItem("正在格式化SD卡...");
		while (true)
		{
			memset(buffer, 0x00, sizeof(buffer));

			RUN_BREAK(!readDataByDid(0xFF, 0x1B, &size, buffer), getUdsLastError());

			OUTPUT_DEBUG_INFO("格式化SD卡 0x%x", buffer[0]);

			if (buffer[0] == 0x4) success = true;
			
			if (((buffer[0] == 0x1) && success) || GetTickCount() - startTime >= 10000) break;
			msleep(100);
		}

#if REPEAT_TEST
		if (!success && repeat < 3)
		{
			addListItem(Q_SPRINTF("格式化SD卡重复测试%d次", repeat + 1));
			repeat++;
			goto tryAgain;
		}
#endif

		WRITE_LOG("%s 格式化SD卡", OK_NG(success));
		addListItemEx(Q_SPRINTF("格式化SD卡 %s", OK_NG(success)));
		RUN_BREAK(!success, "格式化SD失败");

		/*退出设置界面*/
		msg.ucData[2] = 0x30;
		msg.ucData[3] = 0x2A;
		msg.ucData[4] = 0xB0;
		msg.ucData[5] = 0x39;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(300);
		msg.ucData[2] = 0x20;
		m_canSender.AddMsg(msg, 100, ST_Event, 3);
		msleep(1000);

		success = autoProcessCanMsg(0x344, 0x0, [](const int& req, const MsgNode& msg)->bool {return req == (msg.ucData[7] & 0x01); });

		WRITE_LOG("%s 模拟退出全景", OK_NG(success));
		addListItemEx(Q_SPRINTF("模拟退出全景 %s", OK_NG(success)));
		RUN_BREAK(!success, "模拟退出全景失败");
		result = true;
	} while (false);
	return result;
}

void FunctionThread::run()
{
	bool success = false;
	while (!m_quit)
	{
		if (m_connect)
		{
			switch (m_testSequence)
			{
			case TS_SCAN_CODE:
				success = false;
				setScanCodeDlg();
				m_testSequence = TestSequence::TS_PRE_TEST;
				break;
			case TestSequence::TS_PRE_TEST:
				if (!prepareTest(0x344))
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				//m_testSequence = TestSequence::TS_CHECK_SC;
				m_testSequence = TestSequence::TS_CHECK_UART2;
				break;
			case TestSequence::TS_CHECK_SC:
				if (!checkStaticCurrent())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_RS;
				break;
			case TestSequence::TS_CHECK_RS:
				if (!checkCanRouseSleep({ 0x539,8,{0,0,0,0,0,0,0,0x39} }, 200, 0x344))
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_WRITE_SN;
				break;
			case TestSequence::TS_WRITE_SN:
				if (!writeSN())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_VER;
				break;
			case TestSequence::TS_CHECK_VER:
				if (!checkVersion())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_VIDEO;
				break;
			case TestSequence::TS_CHECK_VIDEO:
				if (!checkAVMUseKey(0x344, 0, nullptr, 10000, 1, [](const int& req, const MsgNode& msg)
					->bool {return req == (msg.ucData[7] & 0x01); }))
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_UART2;
				break;
			case TestSequence::TS_CHECK_UART2:
				if (!autoTemplateCanFnc("检测串口2", 0x344, 1, [](const int& req, const MsgNode& msg)
					->bool {return req == (msg.ucData[7] & 0x01); }, { {0x2BB,8,{0x0E}} }, 10))
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				//m_testSequence = TestSequence::TS_CHECK_FRVIEW;
				m_testSequence = TestSequence::TS_CHECK_SD_CARD;
				break;
			case TestSequence::TS_CHECK_FRVIEW:
				if (!checkAVMFRView({ {0x2BB,8, { 0x0C }}, { 0x2BB,8,{ 0x0E } } }, 10, 0x344, { 1,2 },
					[](const int& req, const MsgNode& msg)->bool {return req == ((msg.ucData[2] >> 4) & 0x0f); }))//0x0C前进,0x0E倒车
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_SD_CARD;
				break;
			case TestSequence::TS_CHECK_SD_CARD:
				if (!autoTemplateCanFnc("检测SD卡", 0x344, 0, [](const int& req, const MsgNode& msg)
					->bool {return req == ((msg.ucData[0] & 0x02) >> 1); }))
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_DVR_FNC;
				break;
			case TestSequence::TS_CHECK_DVR_FNC:
				if (!checkDVRFunction())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_DVR_PB;
				break;
			case TestSequence::TS_CHECK_DVR_PB:
				if (!checkDVRPlayback())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_FORMAT_SD;
				break;
			case TestSequence::TS_FORMAT_SD:
				if (!formatSDCard())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CHECK_CUR;
				break;
			case TestSequence::TS_CHECK_CUR:
				if (!checkCurrent())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				m_testSequence = TestSequence::TS_CLEAR_DTC;
				break;
			case TestSequence::TS_CLEAR_DTC:
				if (!clearDtc())
				{
					m_testSequence = TestSequence::TS_SAVE_LOG;
					break;
				}
				success = true;
				m_testSequence = TestSequence::TS_SAVE_LOG;
				break;
			case TestSequence::TS_SAVE_LOG:
				if (!saveLog(success))
				{
					setMessageBox("保存日志", getLastError());
				}
				m_testSequence = TS_SCAN_CODE;
				break;
			default:
				break;
			}
		}
		msleep(100);
	}
}
