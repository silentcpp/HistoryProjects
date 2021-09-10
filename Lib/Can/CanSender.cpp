#include "CanSender.h"
#include <process.h>

CanSender::CanSender()
{
	m_handle = (HANDLE)_beginthreadex(nullptr, 0, &sendProcThread, this, 0, 0);
}

CanSender::CanSender(CanTransfer* transfer)
{
	m_transfer = transfer;
	m_handle = (HANDLE)_beginthreadex(nullptr, 0, &sendProcThread, this, 0, 0);
}

CanSender::~CanSender()
{
	if (m_handle)
	{
		m_quit = true;
		if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 2000))
		{
			TerminateThread(m_handle, 0);
		}
		m_handle = nullptr;
	}
}

const QString& CanSender::getLastError()
{
	return m_lastError;
}

bool CanSender::init(CanTransfer* transfer)
{
	bool result = false;
	do
	{
		if (!transfer)
		{
			setLastError("CAN传输为空指针");
			break;
		}
		m_transfer = transfer;
		result = true;
	} while (false);
	return result;
}

bool CanSender::addMsg(const MsgNode& msg, int delay, SendType type, int count, SendProc proc)
{
	bool result = false;
	do
	{
		bool find = false;
		for (int i = 0; i < MAX_MSG_COUNT; i++)
		{
			if (m_msgs[i].valid)
			{
				if (m_msgs[i].msg.id == msg.id)
				{
					memcpy(&m_msgs[i].msg, &msg, sizeof(MsgNode));
					m_msgs[i].delay = delay;
					m_msgs[i].count = count;
					m_msgs[i].type = type;
					m_msgs[i].fnc = proc;
					find = true;
					break;
				}
			}
		}

		if (!find)
		{
			//新增
			for (int i = 0; i < MAX_MSG_COUNT; i++)
			{
				if (!m_msgs[i].valid)
				{
					memcpy(&m_msgs[i].msg, &msg, sizeof(MsgNode));
					m_msgs[i].count = count;
					m_msgs[i].type = type;
					m_msgs[i].delay = delay;
					m_msgs[i].fnc = proc;
					m_msgs[i].valid = true;
					m_msgs[i].time = 0;

					//if (type != ST_EVENT)
					//{
					//	m_msgsBackup[i] = m_msgs[i];
					//}
					find = true;
					break;
				}
			}
		}

		if (!find)
		{
			setLastError("报文缓存区已满");
			break;
		}

		result = true;
	} while (false);
	return result;
}

bool CanSender::addMsg(SendProc proc, int delay, SendType type, int count)
{
	return addMsg({}, delay, type, count, proc);
}

bool CanSender::addMsg(const CanMsg& msg)
{
	return addMsg(msg.msg, msg.delay, msg.type, msg.count, msg.fnc);
}

bool CanSender::addMsg(const std::initializer_list<CanMsg>& msg)
{
	bool result = false, success = true;
	do 
	{
		for (size_t i = 0; i < msg.size(); i++)
		{
			if (!addMsg(msg.begin()[i]))
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

bool CanSender::addMsg(const CanMsg& msg, int start, int length, ULONGLONG data)
{
	bool result = false;
	do
	{
		CanMsg _msg = msg;
		if (!m_transfer->m_matrix.pack(_msg.msg.data, start, length, data))
		{
			setLastError(m_transfer->m_matrix.getLastError());
			break;
		}
		addMsg(_msg);
		result = true;
	} while (false);
	return result;
}

bool CanSender::addPeriodEventMsg(const CanMsg& msg)
{
	bool result = false;
	for (int i = 0; i < MAX_MSG_COUNT; i++)
	{
		if (!m_msgsBackup[i].valid)
		{
			result = true;
			m_msgsBackup[i] = msg;
			break;
		}
	}
	if (!result)
	{
		setLastError("报文缓存区已满");
	}
	return result;
}

void CanSender::deleteMsgs(const std::initializer_list<MsgNode>& msgs)
{
	for (auto& x : msgs)
		deleteOneMsg(x.id);
	return;
}

void CanSender::deleteMsgs(const std::initializer_list<int>& ids)
{
	for (auto& x : ids)
		deleteOneMsg(x);
	return;
}

void CanSender::deleteOneMsg(const MsgNode& msg)
{
	deleteOneMsg(msg.id);
	return;
}

void CanSender::deleteOneMsg(const CanMsg& msg)
{
	deleteOneMsg(msg.msg.id);
}

void CanSender::deleteOneMsg(int id)
{
	for (int i = 0; i < MAX_MSG_COUNT; i++)
	{
		if (m_msgs[i].msg.id == id)
		{
			memset(&m_msgs[i], 0, sizeof(CanMsg));
			break;
		}
	}
	return;
}

void CanSender::deleteAllMsgs()
{
	for (int i = 0; i < MAX_MSG_COUNT; i++)
	{
		if (m_msgs[i].valid)
		{
			memset(&m_msgs[i], 0x00, sizeof(CanMsg));
		}
	}
	return;
}

void CanSender::pauseMsg(const std::initializer_list<MsgNode>& msg)
{
	for (size_t i = 0; i < MAX_MSG_COUNT; i++)
	{
		for (size_t j = 0; j < msg.size(); j++)
		{
			if (m_msgs[i].msg.id == msg.begin()[j].id)
			{
				m_msgs[i].valid = false;
				break;
			}
		}
	}
	return;
}

void CanSender::continueMsg(const std::initializer_list<MsgNode>& msg)
{
	for (size_t i = 0; i < MAX_MSG_COUNT; i++)
	{
		for (size_t j = 0; j < msg.size(); j++)
		{
			if (m_msgs[i].msg.id == msg.begin()[j].id)
			{
				m_msgs[i].valid = true;
				break;
			}
		}
	}
	return;
}

void CanSender::start()
{
	m_timer.getStartTime();
	for (int i = 0; i < MAX_MSG_COUNT; i++)
	{
		if (m_msgs[i].valid)
		{
			m_msgs[i].time = 0;
		}
	}
	m_start = true;
	return;
}

void CanSender::stop()
{
	m_start = false;
	return;
}

bool CanSender::getMsgData(int id, UCHAR* data)
{
	bool result = false;
	do
	{
		bool find = false;
		for (int i = 0; i < MAX_MSG_COUNT; i++)
		{
			if (!m_msgs[i].valid)
			{
				continue;
			}

			if (id == m_msgs[i].msg.id)
			{
				memcpy(data, m_msgs[i].msg.data, m_msgs[i].msg.dlc);
				find = true;
			}
		}

		if (!find)
		{
			setLastError("未找到报文");
			break;
		}

		result = true;
	} while (false);
	return result;
}

bool CanSender::setMsgData(int id, const UCHAR* data)
{
	bool result = false;
	do
	{
		bool find = false;
		for (int i = 0; i < MAX_MSG_COUNT; i++)
		{
			if (!m_msgs[i].valid)
			{
				continue;
			}

			if (id == m_msgs[i].msg.id)
			{
				memcpy(m_msgs[i].msg.data, data, m_msgs[i].msg.dlc);
				find = true;
			}
		}

		if (!find)
		{
			setLastError("未找到报文");
			break;
		}
		result = true;
	} while (false);
	return result;
}

void CanSender::setLastError(const QString& error)
{
	m_lastError = error;
}

UINT WINAPI CanSender::sendProcThread(void* args)
{
	CanSender* sender = static_cast<CanSender*>(args);
	MsgNode msgs[100] = { 0 };
	int endTime = 0, count = 0;

	while (!sender->m_quit)
	{
		while (sender->m_start)
		{
			endTime = (int)sender->m_timer.getEndTime();
			for (int i = 0; i < MAX_MSG_COUNT; i++)
			{
				if (sender->m_msgs[i].valid && endTime - sender->m_msgs[i].time >= sender->m_msgs[i].delay)
				{
					sender->m_msgs[i].time = endTime;

					if (sender->m_msgs[i].fnc)
						sender->m_msgs[i].fnc(sender->m_msgs[i].msg);

					memcpy(&msgs[count], &sender->m_msgs[i].msg, sizeof(MsgNode));
					if (sender->m_msgs[i].type == ST_EVENT)
					{
						sender->m_msgs[i].count--;
						if (sender->m_msgs[i].count <= 0)
						{
							//停止发送
							sender->m_msgs[i].valid = false;
						}
					}
					else if (sender->m_msgs[i].type == ST_PE)
					{
						if (sender->m_msgs[i].count > 0)
						{
							sender->m_msgs[i].count--;
							if (sender->m_msgs[i].count <= 0)
							{
								//发送默认值
								for (int j = 0; j < MAX_MSG_COUNT; j++)
								{
									if (sender->m_msgs[i].msg.id == sender->m_msgsBackup[j].msg.id)
									{
										sender->m_msgs[i] = sender->m_msgsBackup[j];
										break;
									}
								}
							}
						}
					}

					count++;
					if (count >= 100)
					{
						break;
					}
				}
			}

			if (count > 0)
			{
				sender->m_transfer->multiSend(msgs, count);
				count = 0;
			}
			Sleep(1);
		}
		Sleep(100);
	}
	return 0;
}

