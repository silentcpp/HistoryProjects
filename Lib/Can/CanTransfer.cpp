#include "CanTransfer.h"
#include <process.h>

UINT WINAPI CanTransfer::receiveThread(void* args)
{
	CanTransfer* transfer = static_cast<CanTransfer*>(args);
	if (!transfer)
	{
		return 1;
	}

	MsgNode msg[MAX_FRAME_COUNT] = { 0 };

	while (!transfer->m_quit)
	{
		if (!transfer->m_open)
		{
			Sleep(200);
			continue;
		}

		int count = transfer->receiveProtected(msg, MAX_FRAME_COUNT, 10);
		for (int i = 0; i < count; i++)
		{
			transfer->m_message.save(&(msg[i]), 1);
		}
	}
	return 0;
}

int CanTransfer::getDlc(const MsgNode* msg)
{
	return msg->dlc == 0 ? 8 : msg->dlc;
}

void CanTransfer::formatMsg(const char* type, const MsgNode& msg, char* text)
{
	sprintf(text,
		"%s:%x,[%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x],%06d\n",
		type,
		msg.id,
		msg.data[0],
		msg.data[1],
		msg.data[2],
		msg.data[3],
		msg.data[4],
		msg.data[5],
		msg.data[6],
		msg.data[7],
		(int)msg.timeStamp);
}

void CanTransfer::outputMsg(const char* type, const MsgNode* msg, int count)
{
	if (!m_debug)
		return;

	char text[260] = { 0 };
	for (int i = 0; i < count; i++)
	{
		formatMsg(type, msg[i], text);
		OutputDebugStringA(text);
	}
}

void CanTransfer::setDlc(int length)
{
	m_dlc = length;
}


CanTransfer::CanTransfer()
{
	m_message.clear();
	m_timer.getStartTime();
	InitializeCriticalSection(&m_cs);
}

CanTransfer::~CanTransfer()
{
	if (m_logMgr)
	{
		delete m_logMgr;
		m_logMgr = nullptr;
	}

	stopReceiveThread();

	DeleteCriticalSection(&m_cs);
}

void CanTransfer::setMatrixType(MatrixType matrix)
{
	m_matrix.setType(matrix);
}

void CanTransfer::enableSaveLog(bool on)
{
	m_saveLog = on;
}

void CanTransfer::enableDebug(bool on)
{
	m_debug = on;
}

int CanTransfer::quickReceive(MsgNode* msg, int size, int ms)
{
	return m_threadHandle ? m_message.get(msg, size) : receiveProtected(msg, size, ms);
}

int CanTransfer::safeReceive(MsgNode* msg, int size, int ms, int recvID, int cmdID)
{
	int count = 0;
	int tick = (int)m_timer.getEndTime();
	do
	{
		count = m_threadHandle ? m_message.get(msg,size) : receiveProtected(msg, size, 20);

		bool find = false;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				if ((-1 == recvID || recvID == msg[i].id) &&
					(-1 == cmdID || cmdID == msg[i].data[0]))
				{
					find = true;
					break;
				}
			}
		}

		if (find || m_timer.getEndTime() - tick > ms)
		{
			break;
		}
	} while (true);
	return count;
}

int CanTransfer::receive(MsgNode* msg, int size, int ms, int recvID, int cmdID)
{
	int count = 0, iter = 0;
	iter = max(ms / (CONTINUE_RECEIVE_TIMES * CONTINUE_RECEIVE_INTERVAL), 1);
	for (int j = 0; j < iter; j++)
	{
		for (int i = 0; i < CONTINUE_RECEIVE_TIMES; i++)
		{
			if (count = (m_threadHandle ? m_message.get(msg, size) : receiveProtected(msg, size)))
			{
				break;
			}
			Sleep(CONTINUE_RECEIVE_INTERVAL);
		}

		bool find = false;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				if ((-1 == recvID || recvID == msg[i].id) && (-1 == cmdID || cmdID == msg[i].data[0]))
				{
					find = true;
					break;
				}
			}
		}

		if (find)
		{
			break;
		}
	}
	return count;
}

bool CanTransfer::saveLog(const char* type, const MsgNode* msg, int count)
{
	if (!m_saveLog)
	{
		if (m_fnc)
		{
			for (int i = 0; i < count; i++)
			{
				m_fnc(type, msg[i]);
			}
		}
	}
	else
	{
		if (!m_logMgr)
		{
			SYSTEMTIME time = { 0 };
			GetLocalTime(&time);

			QString pathName = QString("%1\\Can\\%2\\").arg(m_dirName).arg(QString().
				sprintf("%04d-%02d-%02d", time.wYear, time.wMonth, time.wDay));

			if (!QDir(pathName).exists())
			{
				QDir().mkpath(pathName);
			}
			
			QString fileName = pathName + QString("%1_%2_%3").arg(m_modelName,
				m_codeName).arg(QString().sprintf("%02d-%02d-%02d.can", time.wHour,
					time.wMinute, time.wSecond));

			m_logMgr = new CLogMgr(fileName.toLocal8Bit());
		}

		EnterCriticalSection(&m_cs);
		for (int i = 0; i < count; i++)
		{
			if (m_fnc)
			{
				m_fnc(type, msg[i]);
			}

			SYSTEMTIME time;
			GetLocalTime(&time);
			m_logMgr->LogPrint(
				"%02d:%02d:%02d.%03d,"
				"%s:0x%x,"
				"[%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x],"
				"%06d\n",
				time.wHour,
				time.wMinute,
				time.wSecond,
				time.wMilliseconds,
				type,
				msg[i].id,
				msg[i].data[0],
				msg[i].data[1],
				msg[i].data[2],
				msg[i].data[3],
				msg[i].data[4],
				msg[i].data[5],
				msg[i].data[6],
				msg[i].data[7],
				(int)msg[i].timeStamp);
		}
		LeaveCriticalSection(&m_cs);
	}
	return true;
}

bool CanTransfer::flushLogFile()
{
	if (m_saveLog)
	{
		if (m_logMgr)
		{
			delete m_logMgr;
			m_logMgr = nullptr;
		}
	}
	return true;
}

bool CanTransfer::clearLogFile()
{
	return m_logMgr && m_logMgr->Clear();
}

bool CanTransfer::isOpened()
{
	return m_open;
}

bool CanTransfer::startReceiveThread()
{
	bool result = true;
	do
	{
		if (m_threadHandle)
		{
			break;
		}

		m_quit = false;
		m_threadHandle = (HANDLE)_beginthreadex(nullptr, 0, receiveThread, this, 0, 0);

		if (!m_threadHandle)
		{
			setLastError("开启接收线程失败");
			break;
		}
		result = true;
	} while (true);
	return result;
}

bool CanTransfer::stopReceiveThread()
{
	bool result = true;
	do
	{
		if (m_threadHandle)
		{
			m_quit = true;
			if (WAIT_TIMEOUT == WaitForSingleObject(m_threadHandle, 2000))
			{
				TerminateThread(m_threadHandle, 0);
			}
			m_threadHandle = nullptr;
		}
	} while (false);
	return result;
}

const QString& CanTransfer::getLastError()
{
	return m_lastError;
}

void CanTransfer::setSaveLogInfo(const QString& dirName, const QString& moduleName, const QString& codeName)
{
	if (!m_saveLog) return;

	if (!dirName.isEmpty())
		m_dirName = dirName;

	if (!moduleName.isEmpty())
		m_modelName = moduleName;

	if (!codeName.isEmpty())
		m_codeName = codeName;
}

void CanTransfer::setProcessFnc(const std::function<void(const char*, const MsgNode&)>& fnc)
{
	m_fnc = fnc;
}

int CanTransfer::getDlc() const
{
	return m_dlc;
}

bool CanTransfer::getUseFd() const
{
	return m_useFd;
}

void CanTransfer::setUseFd(bool on)
{
	m_useFd = on;
}

void CanTransfer::setLastError(const QString& error)
{
	m_lastError = error;
}
