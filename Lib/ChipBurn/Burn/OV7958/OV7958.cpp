#include "OV7958.h"

Ov7958::Ov7958()
{
}

Ov7958::~Ov7958()
{
}

bool Ov7958::initialize()
{
	bool result = false, success = true;
	do
	{
		if (m_chipType == CT_OV7958_FLASH_UNIVERSAL_SET)
		{
			uchar addr[] = { 0x4c,0x58,0x5c,0x5d,0x65 };
			uchar data[] = { 0x01,0x58,0xb4,0x80,0x80 };
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
		else
		{
			setLastError("不支持的烧录模式");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Ov7958::readFile(uchar* data, uint size, int* percent)
{
	bool result = false;
	do {

		const char* error = "Ov7958读取数据失败";
		uchar data[1] = { 0x00 };
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		msleep(14);
		data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		msleep(14);
		data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		data[0] = 0x0b; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);

		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);

		uint count = 0;
		for (uint value_i = 0; value_i <= size; value_i++)
		{
			if (((value_i % 257) == 0) && (value_i / 257 > 0))
			{
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				msleep(52);
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);

				msleep(14);
				data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0x0b; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);

				data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = uchar(value_i / 257); LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
			}

			LIB_RUN_BREAK(!i2cAddrRead(0x6231, 2, data, 1), error);
			if (value_i % 257)
			{
				data[count++] = data[0];
				(*percent) = (count * 100) / size;
				msleep(1);
			}
		}
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		result = true;
	} while (false);
	return result;
}

bool Ov7958::writeFile(const uchar* data, uint size, int* percent)
{
	bool result = false;
	do
	{
		LIB_RUN_BREAK(!setProtect(false), "解保护失败");
		if (!earseAll())
		{
			break;
		}

		for (uint i = 0; i < 10; i++)
		{
			(*percent)++;
			msleep(500);
		}

		const char* error = "Ov7958写入数据失败";
		uchar data[] = { 0x00 };
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		msleep(14);
		data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		msleep(14);
		data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		msleep(14);
		data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		data[0] = 0x02; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
		data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);

		for (uint val_i = 0; val_i < size; val_i++)
		{
			if (((val_i % 256) == 0) && (val_i / 256 > 0))
			{
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				msleep(14);
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				msleep(14);
				data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0x06; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				msleep(14);
				data[0] = 0xfb; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
				data[0] = 0x02; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = uchar(val_i / 256); LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
				data[0] = 0x00; LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, data, 1), error);
			}
			*percent = (val_i * 80 / size) + 10;
			LIB_RUN_BREAK(!i2cAddrWrite(0x6217, 2, &data[val_i], 1), error);
			msleep(1);
		}
		data[0] = 0x3b; LIB_RUN_BREAK(!i2cAddrWrite(0x6202, 2, data, 1), error);
		for (uint i = 0; i < 10; i++)
		{
			(*percent)++;
			msleep(500);
		}
		LIB_RUN_BREAK(!setProtect(true), "写保护失败");
		result = true;
	} while (false);
	return result;
}

bool Ov7958::readData(uint address, uchar* data, ushort size)
{
	return false;
}

bool Ov7958::writeData(uint address, const uchar* data, ushort size)
{
	return false;
}

bool Ov7958::earseAll()
{
	bool result = false, success = true;
	do
	{
		ushort addr[] = {
			0x6202,0x6202,0x6217,0x6202,0x6202,
			0x6202,0x6202,0x6202,0x6202,0x6202,
			0x6202,0x6202,0x6217,0x6202,0x6202,
			0x6202,0x6202,0x6202,0x6202,0x6202,
			0x6202,0x6202
		};

		uchar data[] = {
			0x3b,0xfb,0x06,0x3b,0x3b,
			0x3b,0x3b,0x3b,0x3b,0x3b,
			0x3b,0xfb,0xc7,0x3b,0x3b,
			0x3b,0x3b,0x3b,0x3b,0x3b,
			0x3b,0x3b
		};

		for (int i = 0; i < sizeof(addr); i++)
		{
			if (!i2cAddrWrite(addr[i], 2, &data[i], 1, true))
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

bool Ov7958::getStatus()
{
	bool result = false;
	do
	{
		uchar data[1] = { 0 };
		if (!i2cAddrRead(0x3003, 2, data, 1))
		{
			break;
		}
		/*0x1C硬件通讯成功,FLASH是空的*/

		/*0x13硬件通讯成功,FLASH有数据*/

		/*0x00硬件通讯失败*/
		if (!*data)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Ov7958::setProtect(bool protect)
{
	bool result = false, success = true;
	do
	{
		ushort addr[] = 
		{
			0x6202,0x6202,0x6217,0x6202,0x6202,
			0x6202,0x6202,0x6202,0x6202,0x6202,
			0x6202,0x6217,0x6217,0x6217,0x6202,
			0x6202,0x6202,0x6202,0x6202,0x6202,
			0x6202 
		};

		uchar value = protect ? 0xfc : 0x00;
		uchar data[] = 
		{
			0x3b,0xfb,0x06,0x3b,0x3b,0x3b,0x3b,
			0x3b,0x3b,0x3b,0xfb,0x01,value,0x00,
			0x3b,0x3b,0x3b,0x3b,0x3b,0x3b,0x3b
		};

		if (sizeof(addr) / sizeof(ushort) != sizeof(data))
		{
			setLastError("地址列表与数据列表大小不一致");
			break;
		}

		for (int i = 0; i < sizeof(addr); i++)
		{
			if (!i2cAddrWrite(addr[i], 2, &data[i], 1, true))
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			break;
		}
		msleep(100);
		result = true;
	} while (false);
	return result;
}
