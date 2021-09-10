#include "AdvCan.h"
#include "AdvCAN/AdvCANIO.cpp"

AdvCan::AdvCan()
{

}

AdvCan::~AdvCan()
{
    clearBuffer();
    close();
}

bool AdvCan::open(int baudrate, int extFrame, int device, int port)
{
	bool result = false;
    do 
    {
		close();

        wchar_t name[64] = {0};
		swprintf(name, L"can%d", port);

		m_handle = acCanOpen(name, false);

        if (INVALID_HANDLE_VALUE == m_handle)
        {
			setLastError("¥Úø™CANø® ß∞‹");
			acCanClose(m_handle);
			break;
		}

		if (SUCCESS != acEnterResetMode(m_handle))
		{
			setLastError("÷ÿ÷√CANø® ß∞‹");
			acCanClose(m_handle);
			break;
		}

		if (SUCCESS != acSetBaud(m_handle, baudrate))
		{
			setLastError("…Ë÷√CANø®≤®Ãÿ¬  ß∞‹");
			acCanClose(m_handle);
			break;
		}

		if (SUCCESS != acSetTimeOut(m_handle, 300, 300))
		{
			setLastError("…Ë÷√CANø®≥¨ ± ß∞‹");
			acCanClose(m_handle);
			break;
		}

		m_extFrame = extFrame;

		ULONG ulCode = 0;
		ULONG ulMask = 0;
		if (0 == m_extFrame)
		{
			ulMask = 0x001fffff;
			ulCode = m_recvID << 21;
		}
		else
		{
			ulMask = 0;
			ulCode = m_recvID << 3;
		}

		if (m_filter)
		{
			if (SUCCESS != acSetAcceptanceFilter(m_handle, ulCode, ulMask))
			{
				setLastError("…Ë÷√CANø®π˝¬À∆˜ ß∞‹");
				acCanClose(m_handle);
				break;
			}
		}

		if (SUCCESS != acEnterWorkMode(m_handle))
		{
			setLastError("Ω¯»ÎCANø®π§◊˜ƒ£ Ω ß∞‹");
			acCanClose(m_handle);
			break;
		}

		if (!clearBuffer())
		{
			acCanClose(m_handle);
			break;
		}

		m_open = true;
		result = true;
	} while (false);
	return result;
}

bool AdvCan::close()
{
    bool result = false;
    do 
    {
		m_open = false;

        if (SUCCESS != acCanClose(m_handle))
        {
			setLastError("πÿ±’CANø® ß∞‹");
            break;
        }
        result = true;
    } while (false);
    return result;
}

bool AdvCan::clearBuffer()
{
    bool result = false;
    do 
    {
		m_message.clear();
        result = true;
	} while (false);
    return result;
}

bool AdvCan::send(const MsgNode *msg)
{
    bool result = false;
	OVERLAPPED ov = { 0 };
	ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    do 
    {
        if (!m_open)
        {
			setLastError("CANø®Œ¥¥Úø™");
            break;
        }

		canmsg_t can = { 0 };
        can.id = msg->id;
        can.length = getDlc(msg);
        can.cob = 0;
		memcpy(can.data, msg->data, getDlc(msg));
		if (m_extFrame)
		{
            can.flags = MSG_EXT;
        }

        ULONG writeCount = 0;
        if(SUCCESS != acCanWrite(m_handle, &can, 1, &writeCount, &ov))
        {
            if (m_debug)
            {
				OutputDebugStringW(L"∑¢ÀÕ ß∞‹\n");
			}

			saveLog("F", msg, 1);
            break;
        }

        const_cast<MsgNode*>(msg)->timeStamp = (float)m_timer.getEndTime();

		outputMsg("S", msg);

		saveLog("S", msg, 1);

        result = true;
    } while (false);
    CloseHandle(ov.hEvent);
    return result;
}

bool AdvCan::multiSend(const MsgNode* msg, int count)
{
    return false;
}

int AdvCan::receiveProtected(MsgNode* msg, int size, int ms)
{
	int count = 0;
	OVERLAPPED ov = { 0 };
	ov.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    do
    {
		canmsg_t can[512] = { 0 };
		Sleep(10);
		ULONG ulErrorCode = 0;
		if (acClearCommError(m_handle, &ulErrorCode) != SUCCESS)
		{
			setLastError("«Âø’CANø®ª∫¥Ê ß∞‹");
			break;
		}

		ULONG read = 0;
		if (SUCCESS != acCanRead(m_handle, can, 512, (ULONG*)&read, &ov))
		{
			setLastError("CANø®Ω” ’±®Œƒ ß∞‹");
			break;
		}
		else
		{
			for (ULONG i = 0; i < read; i++)
			{
				msg[count].id = can[i].id;
				memcpy(msg[count].data, can[i].data, can[i].length);
				msg[count].timeStamp = (float)m_timer.getEndTime();
				if (++count >= size)
				{
					break;
				}
			}
			outputMsg("R", msg, count);
			saveLog("R", msg, count);
		}
		acClearRxFifo(m_handle);
	} while (false);
	CloseHandle(ov.hEvent);
	return count;
}


