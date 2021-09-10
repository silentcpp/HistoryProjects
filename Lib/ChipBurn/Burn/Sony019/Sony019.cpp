#include "Sony019.h"

Sony019::Sony019()
{
	m_cmdAddrLen = 4;
}

Sony019::~Sony019()
{
}

bool Sony019::initialize()
{
	bool result = false, success = true;
	do 
	{
		if (m_chipType == CT_SONY019_FLASH_UNIVERSAL_SET)
		{
			uchar addr[] = { 0x0d,0x07,0x04 };
			uchar data[] = { 0x87,0x86,0x47 };
			if (sizeof(addr) != sizeof(data))
			{
				setLastError("地址列表与数据列表大小不一致");
				break;
			}

			ushort slave = SLAVE_ADDR_96706;
			for (int i = 0; i < sizeof(addr); i++)
			{
				if (i == 2)
				{
					slave = SLAVE_ADDR_96701;
				}

				if (!i2cAddrWrite(addr[i], 1, &data[i], 1, true, slave))
				{
					success = false;
					break;
				}
				msleep(50);
			}

			if (!success)
			{
				break;
			}
		}
		else if (m_chipType == CT_SONY019_FLASH_CHANGAN_IMS)
		{
			uchar addr[] = { 0x4c,0x58,0x5c,0x5d,0x65 };
			uchar data[] = { 0x01,0x58,0xb0,0x34,0x34 };
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

			if (!success)
			{
				break;
			}
		}
		else if (m_chipType == CT_SONY019_FLASH_EP30TAP_DMS)
		{

		}
		else
		{
			setLastError("不支持的烧录模式");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Sony019::readFile(uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do 
	{
		std::deque<uint> address = m_jumpAddress; 
		std::deque<bool> record(address.size(), true);

		LIB_RUN_BREAK(!unlock(), "解锁失败");

		for (uint i = 0; i < size; i += 128)
		{
			*percent = getPercent(i, size);

			if (i >= 0x7e000 && i < 0x7f000)
			{
				memset(data + i, 0xff, 128);
			}
			else
			{
				if (address.size() && (address.front() == i))
				{
					memset(data + i, 0xff, 128);
					if (record.front())
					{
						address.front() += 128;
						record.front() = false;
					}
					else
					{
						address.pop_front();
						record.pop_front();
					}
					continue;
				}

				if (!readData(i, data + i, size - i > 128 ? 128 : size - i))
				{
					success = false;
					break;
				}
			}
		}

		if (!success)
		{
			break;
		}

		LIB_RUN_BREAK(!lock(), "加锁失败");

		result = true;
	} while (false);
	return result;
}

bool Sony019::writeFile(const uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		m_jumpAddress = calculateSector(data, size, 256, 0xff);
		std::deque<uint> address = m_jumpAddress; 
		std::deque<bool> record(address.size(), true);

		LIB_RUN_BREAK(!unlock(), "解锁失败");
		for (uint i = 0; i < size; i += 128)
		{
			*percent = getPercent(i, size);

			if (i >= 0x7e000 && i < 0x7f000)
			{
				//跳过用户区域
			}
			else
			{
				if (!(i % 4096) && !eraseFlash(i))
				{
					break;
				}

				if (address.size() && (address.front() == i))
				{
					if (record.front())
					{
						address.front() += 128;
						record.front() = false;
					}
					else
					{
						address.pop_front();
						record.pop_front();
					}
					continue;
				}

				if (!writeData(i, data + i, size - i > 128 ? 128 : size - i))
				{
					success = false;
					break;
				}
			}
		}

		if (!success)
		{
			break;
		}
		LIB_RUN_BREAK(!lock(), "加锁失败");
		result = true;
	} while (false);
	return result;
}

bool Sony019::readFlash(uint address, uchar* data, ushort size)
{
	return Sony016::readEeprom(address, data, size);
}

bool Sony019::writeFlash(uint address, const uchar* data, ushort size)
{
	return BaseBurn::writeFlash(address, data, size);
}

bool Sony019::readData(uint address, uchar* data, ushort size)
{
	return Sony016::readData(address, data, size);
}

bool Sony019::writeData(uint address, const uchar* data, ushort size)
{
	return Sony016::writeData(address, data, size);
}

bool Sony019::registerAllDataWriteToFlash()
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };
		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_ALL_SAVE_REG_TO_EEP_019;
		frame.cmd[0].total_cmd_byte = 2;
		if (!writeFrame(frame))
		{
			break;
		}

		msleep(1000);
		memset(&frame, 0, sizeof(SonyCmdFrame));
		if (!readFrame(&frame, 5))
		{
			break;
		}

		if (SC016_SUCCESS != frame.cmd[0].cmd_and_status_code)
		{
			setErrorInfo(frame.cmd[0].cmd_and_status_code);
			break;
		}

		LIB_RUN_BREAK(frame.total_byte != 5, "总字节长度错误");

		result = true;
	} while (false);
	return result;
}

bool Sony019::eraseFlash(uint address)
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };

		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_ERASE_EEP_019;

		if (m_cmdAddrLen == 2)
		{
			frame.cmd[0].data[0] = (address >> 8) & 0xFF;
			frame.cmd[0].data[1] = (address >> 0) & 0xFF;
		}
		else if (m_cmdAddrLen == 4)
		{
			frame.cmd[0].data[0] = (address >> 24) & 0xFF;
			frame.cmd[0].data[1] = (address >> 16) & 0xFF;
			frame.cmd[0].data[2] = (address >> 8) & 0xFF;
			frame.cmd[0].data[3] = (address >> 0) & 0xFF;
		}
		else
		{
			setLastError("地址长度必须为2字节或4字节");
			break;
		}

		frame.cmd[0].total_cmd_byte = 2 + m_cmdAddrLen;
		if (!writeFrame(frame))
		{
			break;
		}

		//此处延时不可修改,默认100
		msleep(100);

		memset(&frame, 0, sizeof(SonyCmdFrame));
		if (!readFrame(&frame, 5))
		{
			break;
		}

		if (SC016_SUCCESS != frame.cmd[0].cmd_and_status_code)
		{
			setErrorInfo(frame.cmd[0].cmd_and_status_code);
			break;
		}

		LIB_RUN_BREAK(frame.total_byte != 5, "总字节长度错误");

		result = true;
	} while (false);
	return result;
}
