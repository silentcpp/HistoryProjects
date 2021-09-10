#include "CanMessage.h"
#include <Windows.h>

CanMessage::CanMessage()
{
	m_cs = new CRITICAL_SECTION;
	InitializeCriticalSection((LPCRITICAL_SECTION)m_cs);
}

CanMessage::~CanMessage()
{
	DeleteCriticalSection((LPCRITICAL_SECTION)m_cs);
	delete m_cs;
	m_cs = nullptr;
}

void CanMessage::save(const MsgNode* msg, int size)
{
	EnterCriticalSection((LPCRITICAL_SECTION)m_cs);
	for (int i = 0; i < size; i++)
	{
		if (!full())
		{
			memcpy(&(m_msg[m_writeIndex]), &(msg[i]), sizeof(MsgNode));
			m_writeIndex = (m_writeIndex + 1) % MAX_SAVE_MSG_COUNT;
		}
	}
	LeaveCriticalSection((LPCRITICAL_SECTION)m_cs);
}

int CanMessage::get(MsgNode* msg, int size)
{
	int count = 0;
	EnterCriticalSection((LPCRITICAL_SECTION)m_cs);
	while (!empty() && count < size)
	{
		memcpy(msg + count, &(m_msg[m_readIndex]), sizeof(MsgNode));
		m_readIndex = (m_readIndex + 1) % MAX_SAVE_MSG_COUNT;
		count++;
	}
	LeaveCriticalSection((LPCRITICAL_SECTION)m_cs);
	return count;
}

void CanMessage::clear()
{
	EnterCriticalSection((LPCRITICAL_SECTION)m_cs);
	m_readIndex = 0;
	m_writeIndex = 0;
	memset(m_msg, 0, sizeof(MsgNode) * MAX_SAVE_MSG_COUNT);
	LeaveCriticalSection((LPCRITICAL_SECTION)m_cs);
}

bool CanMessage::empty()
{
	return m_readIndex == m_writeIndex;
}

bool CanMessage::full()
{
	return (m_writeIndex + 1) % MAX_SAVE_MSG_COUNT == m_readIndex;
}

