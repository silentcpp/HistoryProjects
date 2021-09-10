#include "CanFactory.h"

#include "ZlgCan.h"
#include "AdvCan.h"
#include "KvaserCan.h"
#include "UartCan.h"
#include "GCanFd.h"

CanTransfer* CanFactory::m_transfer[MAX_CAN_TRANSFER_COUNT] = { 0 };

int CanFactory::m_count = 0;

CanTransfer* CanFactory::allocTransfer(const QString& cardName)
{
	CanTransfer* transfer = nullptr;
	if (cardName == nullptr)
		return transfer;

	if (m_count > MAX_CAN_TRANSFER_COUNT - 1)
	{
		return nullptr;
	}

	if (cardName == "ZLG")
	{
		if (!m_transfer[m_count])
		{
			m_transfer[m_count] = new ZlgCan;
		}
	}
	else if (cardName == "KVASER")
	{
		if (!m_transfer[m_count])
		{
			m_transfer[m_count] = new Kvaser;
		}
	}
	else if (cardName == "ADV")
	{
		if (!m_transfer[m_count])
		{
			m_transfer[m_count] = new AdvCan;
		}
	}
	else if (cardName == "UART")
	{
		if (!m_transfer[m_count])
		{
			m_transfer[m_count] = new UartCan;
		}
	}
	else if (cardName == "GCANFD")
	{
		if (!m_transfer[m_count])
		{
			m_transfer[m_count] = new GCanFd;
		}
	}
	transfer = m_transfer[m_count++];
	return transfer;
}

void CanFactory::freeTransfer(CanTransfer* transfer)
{
	if (transfer == nullptr)
	{
		for (int i = 0; i < MAX_CAN_TRANSFER_COUNT; i++)
		{
			if (m_transfer[i])
			{
				delete m_transfer[i];
				m_transfer[i] = nullptr;
			}
		}
		m_count = 0;
	}
	else
	{
		int index = 0;
		for (int i = 0; i < MAX_CAN_TRANSFER_COUNT; i++)
		{
			if (!memcmp(m_transfer[i], transfer, sizeof(CanTransfer)))
			{
				delete m_transfer[i];
				m_transfer[i] = nullptr;
				m_count--;
				break;
			}
			index++;
		}

		for (int i = index; i < MAX_CAN_TRANSFER_COUNT - 1; i++)
		{
			m_transfer[i] = m_transfer[i + 1];
		}
		m_transfer[MAX_CAN_TRANSFER_COUNT - 1] = nullptr;
	}

}

int CanFactory::getTransferCount()
{
	return m_count;
}

CanTransfer* CanFactory::getTransferValue(int index)
{
	if (index < 0 || index > MAX_CAN_TRANSFER_COUNT - 1)
		return nullptr;
	return m_transfer[index];
}

int CanFactory::getTransferIndex(const CanTransfer* transfer)
{
	bool find = false;
	int index = 0;
	for (int i = 0; i < MAX_CAN_TRANSFER_COUNT; i++)
	{
		if (!memcmp(m_transfer[i], transfer, sizeof(CanTransfer)))
        {
			find = true;
            break;
        }
        index++;
    }

	if (!find)
		index = -1;
	return index;
}

QStringList CanFactory::getSupportCan()
{
	QStringList supportCan = {
	"ZLG",
	"KVASER",
	"ADV",
	"UART",
	"GCANFD"
	};
	return supportCan;
}
