#include "BaseBurn.h"

BaseBurn::BaseBurn()
{

}

BaseBurn::~BaseBurn()
{

}

void BaseBurn::setDevice(BaseDevice* device)
{
	m_device = device;
}

void BaseBurn::setChipType(ChipType type)
{
	m_chipType = type;
}

ChipType BaseBurn::getChipType() const
{
	return m_chipType;
}

const QString& BaseBurn::getLastError()
{
	return m_lastError;
}

void BaseBurn::setSlave(ushort slave)
{
	m_slave = slave;
}

ushort BaseBurn::getSlave() const
{
	return m_slave;
}

void BaseBurn::setReadWriteDelay(int readDelay, int writeDelay)
{
	m_readDelay = readDelay;
	m_writeDelay = writeDelay;
}

void BaseBurn::setJump0xFF(int jump)
{
	m_jump0xff = jump;
}

bool BaseBurn::readFlash(uint address, uchar* data, ushort size)
{
	setLastError("子类未实现读取闪存");
	return false;
}

bool BaseBurn::writeFlash(uint address, const uchar* data, ushort size)
{
	setLastError("子类未实现写入闪存");
	return false;
}

bool BaseBurn::readEeprom(uint address, uchar* data, ushort size)
{
	setLastError("子类未实现读取电可擦除只读存储器");
	return false;
}

bool BaseBurn::writeEeprom(uint address, const uchar* data, ushort size)
{
	setLastError("子类未实现写入电可擦除只读存储器");
	return false;
}

bool BaseBurn::lock()
{
	setLastError("子类未实现上锁");
	return false;
}

bool BaseBurn::unlock()
{
	setLastError("子类未实现解锁");
	return false;
}

bool BaseBurn::i2cAddrRead(uint addr, uchar addrLen, uchar* data, ushort dataSize, ushort slave)
{
	bool result = false;
	do
	{
		if (!i2cAddrWrite(addr, addrLen, nullptr, 0, false, slave))
		{
			break;
		}
		//msleep(2);

		int count = i2cRead(data, dataSize, slave);
		if (count != dataSize)
		{
			setLastError(C_SPRINTF("读取地址0x%04x失败,", addr) + getLastError());
			break;
		}
		//msleep(1);

		result = true;
	} while (false);
	return result;
}

bool BaseBurn::i2cAddrWrite(uint addr, uchar addrLen, const uchar* data, ushort dataSize, bool check, ushort slave)
{
	bool result = false, success = true;
	do
	{
		uchar addrData[8] = { 0 };
		for (int i = 0; i < addrLen; i++)
			addrData[i] = addr >> ((addrLen - i - 1) * 8);

		uchar writeData[1024] = { 0 };
		memcpy(writeData, addrData, addrLen);

		int writeLen = addrLen;
		if (dataSize > 0 && data)
		{
			writeLen += dataSize;
			memcpy(&writeData[addrLen], data, dataSize);
		}

		int count = i2cWrite(writeData, writeLen, slave);
		if (count != writeLen)
		{
			setLastError(C_SPRINTF("写入地址0x%04x失败,", addr) + getLastError());
			break;
		}

		//msleep(2);
		if (check)
		{
			if (!i2cAddrRead(addr, addrLen, writeData, dataSize, slave))
			{
				break;
			}

			for (int i = 0; i < dataSize; i++)
			{
				if (data[i] != writeData[i])
				{
					setLastError(C_SPRINTF("写入地址0x%04x校验失败", addr));
					success = false;
					break;
				}
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

bool BaseBurn::i2cAddrWrite(uint addr, uchar addrLen, const std::initializer_list<uchar>& data, ushort slave)
{
	return i2cAddrWrite(addr, addrLen, data.begin(), (ushort)data.size(), false, slave);
}

void BaseBurn::setLastError(const QString& error)
{
	m_lastError = error;
#ifdef QT_DEBUG
	OutputDebugString(m_lastError.toStdWString().c_str());
#endif
}

int BaseBurn::i2cRead(uchar* data, ushort size, ushort slave)
{
	int result = m_device->readData(data, size, !slave ? m_slave : slave);
	if (result != size)
		setLastError(m_device->getLastError());

	if (m_readDelay)
		msleep(m_readDelay);

#ifdef QT_DEBUG
		printLog("R", data, result, slave);
#endif
	return result;
}

int BaseBurn::i2cWrite(const uchar* data, ushort size, ushort slave)
{
	int result = m_device->writeData(data, size, !slave ? m_slave : slave);
	if (result != size)
		setLastError(m_device->getLastError());

	if (m_writeDelay)
		msleep(m_writeDelay);

#ifdef QT_DEBUG 
		printLog("W", data, result, slave);
#endif
	return result;
}

inline int BaseBurn::i2cWrite(const std::initializer_list<uchar>& data, ushort slave)
{
	return i2cWrite(data.begin(), (ushort)data.size(), slave);
}

void BaseBurn::printLog(const QString& type, const uchar* data, int size, ushort slave)
{
	ushort addr = ((!slave ? m_slave : slave) << 1) + (type == "R" ? 1 : 0);

	QString buffer = C_SPRINTF("%ld> %08x %s:[", GetTickCount(), addr, type.toStdString().c_str());

	for (int i = 0; i < size; i++)
		buffer.append(C_SPRINTF("%02x ", data[i]));
	buffer.append("]\n");

	OutputDebugString(buffer.toStdWString().c_str());
}

void BaseBurn::msleep(uint ms)
{
	Sleep(ms);
}

std::deque<uint> BaseBurn::calculateSector(const uchar* buffer, uint size, uint multiple, uchar value)
{
	std::deque<uint> result;
	int modeCount = 0;
	bool find = true;
	for (uint i = 0; i < size; i++)
	{
		if ((i != 0) && (i % multiple == 0))
		{
			for (uint j = modeCount * multiple; j < i - 1; j++)
			{
				if (buffer[j] != value)
				{
					find = false;
					break;
				}
			}

			if (find)
			{
				result.push_back(modeCount * multiple);
			}
			find = true;
			modeCount++;
		}
	}
	return result;
}

uint BaseBurn::findNearAddress(uint address, uint multiple, bool lessThan)
{
	uint result = (uint)-1;
	do
	{
		std::vector<uint> datas(10000);
		std::generate(datas.begin(), datas.end(),
			[multiple, n = 0]()mutable->uint{return n += multiple; });
		bool find = false;
		for (auto& x : datas)
		{
			if (x == address)
			{
				find = true;
				break;
			}
		}

		if (find)
		{
			result = address;
			break;
		}

		datas.push_back(address);

		if (lessThan)
			std::sort(datas.begin(), datas.end(), std::less<uint>());
		else
			std::sort(datas.begin(), datas.end(), std::greater<uint>());

		for (auto iter = datas.begin(); iter != datas.end(); ++iter)
		{
			if (*iter == address)
			{
				result = *std::prev(iter);
				break;
			}
		}
	} while (false);
	return result;
}

int BaseBurn::getPercent(uint current, uint total)
{
	return static_cast<int>(100.0f - (float(total - current) / total) * 100);
}

