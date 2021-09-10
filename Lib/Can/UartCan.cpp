#include "UartCan.h"

UartCan::UartCan(void)
{
}

UartCan::~UartCan(void)
{
}

bool UartCan::open(int baudrate, int extframe, int device, int port)
{
    bool result = false;
    do 
    {
        close();

        if (!m_portMgr.OpenPort(device, baudrate))
        {
			setLastError("打开CAN卡失败");
            break;
        }

		m_open = true;
        result = true;
    } while (false);
    return result;
}

bool UartCan::close()
{
    bool result = false;
    do 
    {
        if (m_open)
        {
            m_open = false;
            if (!m_portMgr.ClosePort())
            {
				setLastError("关闭CAN卡失败");
                break;
            }
        }
        result = true;
    } while (false);
	return result;
}

bool UartCan::clearBuffer()
{
    bool result = false;
    do 
    {
        m_message.clear();
        result = true;
    } while (false);
    return result;
}

#define RM_DATA_TYPE 0x84
#define RM_CHECK_START 2

bool UartCan::send(const MsgNode *msg)
{
	bool result = false;
    do 
    {
        if (!close())
        {
            setLastError("CAN卡未打开");
            break;
        }

        clearBuffer();

        unsigned char data[32] = {0};
        int length = 0;
        
        pack(msg, data, &length);
        
		if (m_portMgr.Send(data, length) != length)
        {
            if (m_debug)
            {
				OutputDebugStringW(L"发送失败\n");
			}
			saveLog("F", msg);
            break;
        }

		const_cast<MsgNode*>(msg)->timeStamp = (float)m_timer.getEndTime();

        outputMsg("S", msg);

		saveLog("S", msg);
        result = true;
    } while (false);
    return result;
}

bool UartCan::multiSend(const MsgNode* msg, int count)
{
    return false;
}

int UartCan::receiveProtected(MsgNode* msg, int size, int ms)
{
    int count = 0;
    do 
    {

		if (!close())
        {
            setLastError("CAN卡未打开");
            break;
        }

        int length = 1;
        if(!unpack(msg, &length) || length <= 0)
        {
            break;
        }
        else
        {
            for(int i = 0; i < length; i++)
            {
				msg[count].timeStamp = (float)m_timer.getEndTime();

                if (++count >= size)
                {
                    break;
                }
            }
            outputMsg("R", msg, count);
			saveLog("R", msg, count);
        }
    } while (false);
    return count;
}

void UartCan::pack(const MsgNode* msg, unsigned char* data, int* length)
{
    data[0] = 0x7e;
    data[1] = 0x43;
    data[2] = RM_DATA_TYPE;
	memcpy(&data[3], &msg->id, 4);
	memcpy(&data[7], msg->data, 8);
    data[15] = 0;
	for (int i = RM_CHECK_START; i < 15; i++)
	{
        data[15] ^= data[i];
	}
    data[16] = 0x7e;
	*length = 17;
}

bool UartCan::unpack(MsgNode* msg, int* length)
{
	bool result = false, find = false;
	DWORD startTime = GetTickCount();
	unsigned char data[64] = { 0 };
	int size = 0;
	for (;;)
	{
        size += m_portMgr.Receive(&data[size], 1);
		if (size == 1 && 0x7e == data[0])
		{
            find = true;
		}

		if (!find)
		{
            size = 0;
		}

		if (find && data[size - 1] == 0x7e &&
			17 == size && checkSumRigth(data, size))
		{
			memcpy(&msg->id, &data[3], 4);
			memcpy(msg->data, &data[7], 8);
            result = true;
			break;
		}
		else
		{
            find = false;
			size = 0;
		}

		if (GetTickCount() - startTime > 5000)
		{
            setLastError("CAN卡解包超时");
			break;
		}
	}
	return result;
}

bool UartCan::checkSumRigth(const unsigned char* data, int length)
{
	unsigned char sum = 0;
	for (int i = RM_CHECK_START; i < length - 2; i++)
	{
        sum ^= data[i];
	}
	return sum == data[length - 2];
}
