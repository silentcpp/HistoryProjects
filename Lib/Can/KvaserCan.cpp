#include "KvaserCan.h"
#include "KvaserCan/INC/canlib.h"
#pragma comment(lib, "canlib32.lib")

Kvaser::Kvaser()
{

}

Kvaser::~Kvaser()
{

}

bool Kvaser::open(int baudrate, int extframe, int device, int port)
{
    bool result = false;
    do 
    {
        close();

        switch (baudrate)
        {
		case 100:m_baudrate = BAUD_100K; break;
		case 125:m_baudrate = BAUD_125K; break;
		case 250:m_baudrate = BAUD_250K; break;
        case 500:m_baudrate = BAUD_500K;break;
		case 1000:m_baudrate = BAUD_1M; break;
        default:m_baudrate = BAUD_500K; break;
        }

        m_extFrame = extframe;

        m_device = device;

        m_port = port;

        canInitializeLibrary();

        m_handle = canOpenChannel(device, canOPEN_ACCEPT_VIRTUAL);
        
        if (m_handle < 0)
        {
			setLastError("打开CAN卡失败");
			break;
        }
        else
        {
            if (canIoCtl(m_handle, canIOCTL_FLUSH_TX_BUFFER, NULL, NULL) != canOK)
            {
				setLastError("CAN卡输入输出控制失败");
                break;
            }
        }

		if (canSetBusParams(m_handle, m_baudrate, 0, 0, 0, 0, 0) < 0)
        {
			setLastError("设置CAN卡参数失败");
			canClose(m_handle);
			break;
		}

        if (canBusOn(m_handle) < 0)
        {
			setLastError("设置CAN卡总线失败");
            canClose(m_handle);
            break;
        }

        clearBuffer();
        m_open = true;
        result = true;
    } while (false);
    return result;
}

bool Kvaser::close()
{
    bool result = false;
    do 
    {
        if (m_open)
        {
            m_open = false;
            if (canClose(m_handle) != canOK)
            {
				setLastError("关闭CAN卡失败");
                break;
            }
        }
        result = true;
    } while (true);
    return result;
}

bool Kvaser::clearBuffer()
{
    m_message.clear();
    return true;
}

bool Kvaser::send(const MsgNode* msg)
{
    bool result = false;
    do 
    {
        if (!m_open)
        {
			setLastError("CAN卡未打开");
            break;
        }

        unsigned int flag = 0;
        flag |= m_extFrame;
		if (canWrite(m_handle, msg->id, (void*)msg->data, getDlc(msg), flag) < 0)
        {
			setLastError("CAN卡发送报文失败");
            break;
        }

        outputMsg("S", msg);

		saveLog("S", msg, 1);

        result = true;
	} while (false);
    return result;
}

bool Kvaser::multiSend(const MsgNode *msg,int count)
{
    return false;
}

int Kvaser::receiveProtected(MsgNode *msg,int size,int ms)
{
    int count = 0;
    do 
    {
        if (!m_open)
        {
            setLastError("CAN卡未打开");
            break;
        }

        unsigned int flag = 0;
        if (canReadWait(m_handle, (long*)(&msg[0].id), (void*)msg[0].data, NULL, &flag, NULL, 200) < 0)
        {
			setLastError("CAN卡读取报文失败");
            break;
        }

        outputMsg("R", msg);
        saveLog("R", msg);
        canFlushReceiveQueue(m_handle);
        count = 1;
    } while (false);
	return count;
}

