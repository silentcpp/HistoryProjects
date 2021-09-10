#include "GCanFd.h"
#include "GCAN/ECanFDVci.h"
#pragma comment(lib,"ECANFDVCI.lib")

GCanFd::GCanFd()
{
	InitializeCriticalSection(&m_cs);
}

GCanFd::~GCanFd()
{
	close();
	DeleteCriticalSection(&m_cs);
}

bool GCanFd::open(int baudrate, int extFrame, int device, int port)
{
	bool result = false;
	do 
	{
		m_baudrate = baudrate;

		m_device = device;

		m_port = port;

		m_extFrame = extFrame;

		if (OpenDeviceFD(USBCANFD, device) != CAN_STATUS_OK)
		{
			setLastError("打开CAN卡失败");
			break;
		}

		INIT_CONFIG config = { 0 };
		config.CanReceMode = GLOBAL_STANDARD_AND_EXTENDED_RECEIVE;
		config.CanSendMode = POSITIVE_SEND;
		unsigned char bitRate = BAUDRATE_500K;
		switch (baudrate)
		{
		case 100: bitRate = BAUDRATE_100K; break;
		case 125: bitRate = BAUDRATE_125K; break;
		case 200: bitRate = BAUDRATE_200K; break;
		case 250: bitRate = BAUDRATE_250K; break;
		case 400: bitRate = BAUDRATE_400K; break;
		case 500: bitRate = BAUDRATE_500K; break;
		case 800: bitRate = BAUDRATE_800K; break;
		case 1000: bitRate = BAUDRATE_1M; break;
		default:bitRate = BAUDRATE_500K; break;
		}
		config.NominalBitRateSelect = bitRate;
		config.DataBitRateSelect = DATARATE_2M;

		if (CAN_STATUS_OK != InitCANFD(USBCANFD, device, port, &config))
		{
			setLastError("初始化CAN卡失败");
			CloseDeviceFD(USBCANFD, m_device);
			break;
		}

		if (CAN_STATUS_OK != StartCANFD(USBCANFD, device, port))
		{
			setLastError("启动CAN卡失败");
			CloseDeviceFD(USBCANFD, m_device);
			break;
		}
		m_open = true;
		result = true;
	} while (false);
    return result;
}

bool GCanFd::close()
{
	bool result = false;
	do 
	{
		stopReceiveThread();

		flushLogFile();

		if (m_open)
		{
			m_open = false;
			
			Sleep(200);

			StopCANFD(USBCANFD, m_device, m_port);

			//Sleep(100);

			//ResetCANFD(USBCANFD, m_device, m_port);

			Sleep(300);

			if (CloseDeviceFD(USBCANFD, m_device) != CAN_STATUS_OK)
			{
				setLastError("关闭CAN卡失败");
				break;
			}
		}
		result = true;
	} while (false);
	return result;
}

bool GCanFd::clearBuffer()
{
	m_message.clear();
	return true;
}

bool GCanFd::send(const MsgNode* msg)
{
	bool result = false;
	do 
	{
		if (!m_open)
		{
			setLastError("CAN卡未连接");
			break;
		}

		CANFD_OBJ obj = { 0 };
		obj.CanORCanfdType.proto = m_useFd ? CANFD_TYPE : CAN_TYPE;
		obj.CanORCanfdType.format = m_extFrame ? EXTENDED_FORMAT : STANDARD_FORMAT;
		obj.ID = msg->id;
		obj.DataLen = getDlc(msg);
		memcpy(obj.Data, msg->data, getDlc(msg));

		EnterCriticalSection(&m_cs);
		DWORD value = TransmitFD(USBCANFD, m_device, m_port, &obj, 1);
		LeaveCriticalSection(&m_cs);

		if (value != CAN_STATUS_OK)
		{
			if (m_debug)
			{
				OutputDebugStringW(L"发送失败\n");
			}

			saveLog("F", msg, 1);
			setLastError("发送报文失败");
			break;
		}

		const_cast<MsgNode*>(msg)->timeStamp = (float)m_timer.getEndTime();

		outputMsg("S", msg);

		saveLog("S", msg);

		result = true;
	} while (false);
	return result;
}

bool GCanFd::multiSend(const MsgNode* msg,int count)
{
	bool result = false;
	do 
	{
		if (!m_open)
		{
			setLastError("CAN卡未连接");
			break;
		}
		
		count = min(100, count);
		CANFD_OBJ obj[100] = { 0 };

		for (int i = 0; i < count; i++)
		{
			obj[i].CanORCanfdType.proto = m_useFd ? CANFD_TYPE : CAN_TYPE;
			obj[i].CanORCanfdType.format = m_extFrame ? EXTENDED_FORMAT : STANDARD_FORMAT;
			obj[i].ID = msg[i].id;
			obj[i].DataLen = getDlc(&msg[i]);
			memcpy(obj[i].Data, msg[i].data, getDlc(&msg[i]));
		}

		EnterCriticalSection(&m_cs);
		DWORD value = TransmitFD(USBCANFD, m_device, m_port, obj, count);
		LeaveCriticalSection(&m_cs);

		if (value != CAN_STATUS_OK)
		{
			if (m_debug)
			{
				OutputDebugStringW(L"发送失败\n");
			}

			saveLog("F", msg, count);
			setLastError("发送报文失败");
			break;
		}

		for (int i = 0; i < count; i++)
		{
			const_cast<MsgNode*>(msg)[i].timeStamp = (float)m_timer.getEndTime();
		}

		outputMsg("S", msg, count);

		saveLog("S", msg, count);

		result = true;
	} while (false);
	return result;
}

int GCanFd::receiveProtected(MsgNode* msg, int size, int ms)
{
	int index = 0;
	DWORD count = 0;
	do
	{
		if (!m_open)
		{
			setLastError("CAN卡未连接");
			break;
		}

		CANFD_OBJ obj[MAX_FRAME_COUNT] = { 0 };
		if (ReceiveFD(USBCANFD, m_device, m_port, obj, &count) != CAN_STATUS_OK)
		{
			setLastError("CAN卡接收报文失败");
			break;
		}
		else
		{
			for (DWORD i = 0; i < count; i++)
			{
				msg[i].id = obj[i].ID;
				msg[i].extFrame = (bool)obj[i].CanORCanfdType.format;
				msg[i].remFrame = (bool)obj[i].CanORCanfdType.type;
				msg[i].dlc = obj[i].DataLen;
				memcpy(msg[i].data, obj[i].Data, obj[i].DataLen);

				msg[i].timeStamp = (float)m_timer.getEndTime();

				if (index >= size)
				{
					break;
				}
				index++;
			}
			outputMsg("R", msg, index);
			saveLog("R", msg, index);
		}
	} while (false);
	return index;
}

