#include "ASX340.h"

enum CmdPool {
	CP_POOL_0,
	CP_POOL_1 = 2,
	CP_POOL_2 = 4,
	CP_POOL_3 = 6,
	CP_POOL_4 = 8,
	CP_POOL_5 = 10,
	CP_POOL_6 = 12,
	CP_POOL_7 = 14,
};

enum CmdCode {
	CC_REG = 0x0040,
	CC_HANDLER = 0x001f
};

enum FlashCode {
	FC_LOCK = 0x8500,
	FC_LOCK_STATUS,
	FC_UNLOCK,
	FC_CONFIG,
	FC_READ,
	FC_WRITE,
	FC_ERASE_BLOCK,
	FC_ERASE_ALL,
	FC_QUERY_DEVICE,
	FC_DEVICE_STATUS,
	FC_CONFIG_DEVICE
};

Asx340::Asx340()
{
}

Asx340::~Asx340()
{
}

bool Asx340::initialize()
{
	bool result = false, success = true;
	do 
	{
		if (m_chipType == CT_ASX340_EEPROM_GEELY_BX11)
		{
			uchar addr[] = { 0x4c,0x58,0x5c,0x5d,0x65 };
			uchar data[] = { 0x01,0x58,0xb0,0x90,0x90 };
			if (sizeof(addr) != sizeof(data))
			{
				setLastError("地址列表与数据列表大小不一致");
				break;
			}

			for (int i = 0; i < sizeof(addr); i++)
			{
				if (!i2cAddrWrite(addr[i], 1, &data[i], 1, true, SLAVE_ADDR_934))
				{
					success = false;
					break;
				}
				msleep(50);
			}

			if (!success || !initEeprom())
			{
				break;
			}
		}
		else if (m_chipType == CT_ASX340_EEPROM_UNIVERSAL_SET)
		{
			if (!initEeprom())
			{
				break;
			}
		}
		else if (m_chipType == CT_ASX340_FLASH_UNIVERSAL_SET)
		{
			if (!initFlash())
			{
				break;
			}
		}
		else
		{
			setLastError("不支持的烧录模式");
			break;
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}


bool Asx340::lock()
{
	bool result = false;
	do
	{
		LIB_RUN_BREAK(!sendHostCmd(FC_LOCK), "上锁失败");

		LIB_RUN_BREAK(!sendHostCmd(FC_LOCK_STATUS), "获取锁状态失败");

		result = true;
	} while (false);
	return result;
}

bool Asx340::unlock()
{
	bool result = false;
	do
	{
		result = sendHostCmd(FC_UNLOCK);
		LIB_RUN_BREAK(!result, "解锁失败");
		result = true;
	} while (false);
	return result;
}

bool Asx340::writeFile(const uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		for (uint i = 0; i < size; i += 8)
		{
			if (!writeData(i, data + i, size - i > 8 ? 8 : size - i))
			{
				success = false;
				break;
			}
			*percent = int(100.0f - (float(size - i) / size) * 100);
		}

		if (!success)
		{
			break;
		}

		if (!unlock())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::readFile(uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		for (uint i = 0; i < size; i += 16)
		{
			if (!readData(i, data + i, size - i > 16 ? 16 : size - i))
			{
				success = false;
				break;
			}
			*percent = int(100.0f - (float(size - i) / size) * 100);
		}

		if (!success)
		{
			break;
		}
		
		if (!unlock())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::writeFlash(uint address, const uchar* data, ushort size)
{
	return writeData(address, data, size);
}

bool Asx340::readFlash(uint address, uchar* data, ushort size)
{
	return readData(address, data, size);
}

bool Asx340::writeData(uint address, const uchar* data, ushort size)
{
	bool result = false, success = true;
	do 
	{
		uchar buffer[512] = { 0 };
		buffer[0] = (address >> 24) & 0xff;
		buffer[1] = (address >> 16) & 0xff;
		buffer[2] = (address >> 8) & 0xff;
		buffer[3] = (address >> 0) & 0xff;
		buffer[4] = (uchar)size;
		memcpy(buffer + 5, data, size);

		uint start = GetTickCount();
		while (true)
		{
			if (!isBusy())
			{
				break;
			}

			if (GetTickCount() - start > 3000)
			{
				success = false;
				setLastError("写入超时");
				break;
			}
			//msleep(2);
		}

		if (!success)
		{
			break;
		}

		if (!i2cAddrWrite(getAddress(), 2, buffer, size + 5))
		{
			break;
		}

		if (!sendHostCmd(FC_WRITE))
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::readData(uint address, uchar* data, ushort size)
{
	bool result = false, success = true;
	do 
	{
		if (!i2cAddrWrite(getAddress(CP_POOL_0), 2, {
			uchar((address >> 24) & 0xff),
			uchar((address >> 16) & 0xff) }))
		{
			break;
		}

		if (!i2cAddrWrite(getAddress(CP_POOL_1), 2, {
			uchar((address >> 8) & 0xff),
			uchar((address >> 0) & 0xff) }))
		{
			break;
		}

		if (!i2cAddrWrite(getAddress(CP_POOL_2), 2, { 0x10,0x00 }))
		{
			break;
		}

		if (!sendHostCmd(FC_READ))
		{
			break;
		}

		if (!sendHostCmd(FC_DEVICE_STATUS))
		{
			break;
		}

		for (int i = 0; i < size; i += 8)
		{
			if (!i2cAddrRead(getAddress(i), 2, data + i,
				size - i > 8 ? 8 : size - i))
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

ushort Asx340::getAddress(int cmdPool)
{
	return 0x8000 | (CC_HANDLER << 10) | cmdPool;
}

bool Asx340::sendHostCmd(ushort cmd)
{
	bool result = false, success = true;
	do
	{
		if (!i2cAddrWrite(0x0040, 2, { (uchar)(cmd >> 8),(uchar)cmd }))
		{
			break;
		}

		uchar data[4] = { 0 };
		uint start = GetTickCount();
		while (true)
		{
			memset(data, 0, sizeof(data));

			if (!i2cAddrRead(0x0040, 2, data, 2))
			{
				success = false;
				break;
			}

			if (!(MAKEWORD(data[1], data[0]) & 0x8000))
			{
				break;
			}

			if (GetTickCount() - start > 3000)
			{
				setLastError(C_SPRINTF("发送命令0x%x超时", cmd));
				success = false;
				break;
			}
			//msleep(10);
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::reset()
{
	bool result = false;
	do 
	{
		if (!i2cAddrWrite(0x001a, 2, { 0x00,0x05 }))
		{
			break;
		}
		msleep(100);

		if (!i2cAddrWrite(0x001a, 2, { 0x00,0x04 }))
		{
			break;
		}
		msleep(100);

		result = true;
	} while (false);
	return result;
}

bool Asx340::isBusy()
{
	bool result = false;
	do 
	{
		if (!sendHostCmd(FC_DEVICE_STATUS))
		{
			result = true;
		}
	} while (false);
	return result;
}

bool Asx340::query()
{
	bool result = false, success = true;
	do
	{
		if (!sendHostCmd(FC_QUERY_DEVICE) || !sendHostCmd(FC_DEVICE_STATUS))
		{
			break;
		}

		for (int i = 0; i < 8; i++)
		{
			uchar temp[32] = { 0 };
			if (!i2cAddrRead(getAddress(CP_POOL_0 + 2 * i), 2, temp, 2))
			{
				success = false;
				break;
			}
			msleep(10);
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::initFlash()
{
	bool result = false;
	do
	{
		if (!reset() || !lock() || !query() || !configI2c())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::initEeprom()
{
	bool result = false, success = true, right = false;
	do
	{
		if (!i2cAddrWrite(0x001c, 2, { 0xa2,0x30 }))
		{
			break;
		}
		msleep(50);

		if (!i2cAddrWrite(0x001a, 2, { 0x08,0x15 }))
		{
			break;
		}
		msleep(50);

		if (!i2cAddrWrite(0x001a, 2, { 0x08,0x14 }))
		{
			break;
		}
		msleep(50);

		uchar data[32] = { 0 };
		for (int i = 0; i < 10; i++)
		{
			memset(data, 0, sizeof(data));
			if (!i2cAddrRead(0x001c, 2, data, 2))
			{
				success = false;
				break;
			}

			if (data[0] == 0x30 && data[1] == 0x30)
			{
				right = true;
				break;
			}
			msleep(10);
		}

		if (!success)
		{
			break;
		}

		if (!right)
		{
			setLastError("未收到正确值0x30");
			break;
		}

		if (!i2cAddrWrite(0xdc07, 2, { 0x03 }))
		{
			break;
		}
		msleep(50);

		if (!i2cAddrWrite(0x001c, 2, { 0x30,0x00 }))
		{
			break;
		}
		msleep(50);

		if (!lock() || !configE2p())
		{
			break;
		}

		result = true;
	} while (false);
	return result;
}

bool Asx340::configI2c()
{
	bool result = false;
	do 
	{
		if (!i2cAddrWrite(getAddress(), 2, { 0x01, 0x00, 0x03, 0x18, 0x00, 0x10, 0x00, 0x00 }))
		{
			break;
		}
		msleep(50);

		if (!sendHostCmd(FC_CONFIG_DEVICE))
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Asx340::configE2p()
{
	bool result = false;
	do
	{
		if (!i2cAddrWrite(getAddress(), 2, { 0x02, 0x00, 0x02, 0x10, 0x00, 0x00, 0xff, 0xff }))
		{
			break;
		}
		msleep(50);

		if (!sendHostCmd(FC_CONFIG_DEVICE))
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}
