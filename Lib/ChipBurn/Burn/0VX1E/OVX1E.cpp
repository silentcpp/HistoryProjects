#include "OVX1E.h"

#define OVX1E_DELAY 50

Ovx1e::Ovx1e()
{
}

Ovx1e::~Ovx1e()
{

}

bool Ovx1e::initialize()
{
	bool result = false, success = true;
	do 
	{
		if (m_chipType == CT_OVX1E_FLASH_UNIVERSAL_SET)
		{
			uchar addr[] = { 0x0d,0x07,0x04 };
			uchar data[] = { 0x87,0x86,0x47 };

			if (sizeof(addr) != sizeof(data))
			{
				setLastError("µÿ÷∑¡–±Ì”Î ˝æ›¡–±Ì¥Û–°≤ª“ª÷¬");
				break;
			}

			for (int i = 0; i < sizeof(addr); i++)
			{
				if (!i2cAddrWrite(addr[i], 1, &data[i], 1, true,
					sizeof(addr) - i != 1 ? SLAVE_ADDR_96706 : SLAVE_ADDR_96701))
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

			if (!initChip())
			{
				break;
			}
		}
		else
		{
			setLastError("≤ª÷ß≥÷µƒ…’¬ºƒ£ Ω");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Ovx1e::readFile(uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10a, 2, { 0x00 }), "0xa10a–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa11e, 2, { 0x7f }), "0xa11e–¥0x7f ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa11d, 2, { 0x00 }), "0xa11d–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa110, 2, { 0x80 }), "0xa11d–¥0x80 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa10f, 2, { 0x18 }), "0xa10f–¥0x18 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa10e, 2, { 0x4c }), "0xa10e–¥0x4c ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa10d, 2, { 0x00 }), "0xa10d–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		for (uint i = 0; i < size; i += 4096)
		{
			if (!readData(i, data + i, size - i > 4096 ? 4096 : size - i))
			{
				success = false;
				break;
			}
			*percent = getPercent(i, size);
		}

		if (!success)
		{
			break;
		}
		uninitChip();
		result = true;
	} while (false);
	return result;
}

bool Ovx1e::writeFile(const uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		for (uint i = 0; i < size; i += 4096)
		{
			if (!writeData(i, data + i, size - i > 4096 ? 4096 : size - i))
			{
				success = false;
				break;
			}
			*percent = getPercent(i, size);
		}

		if (!success)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Ovx1e::readData(uint address, uchar* data, ushort size)
{
	bool result = false, success = true;
	do
	{
		uchar buffer[512] = { 0 };
		uint segment = 0;
		for (uint i = 0; i < size; i += 0x100)
		{
			segment = size - i > 0x100 ? 0x100 : size - i;
			buffer[0] = 0x81;
			buffer[1] = 0x00;
			buffer[2] = 0x00;
			buffer[3] = 0x06;
			buffer[4] = 0x12;
			buffer[5] = ((address + i) >> 16) & 0xff;
			buffer[6] = ((address + i) >> 8) & 0xff;
			buffer[7] = ((address + i) >> 0) & 0xff;
			buffer[8] = (segment >> 8) & 0xff;
			buffer[9] = (segment >> 0) & 0xff;

			if (!i2cAddrWrite(0x8181, 2, { 0 }))
			{
				success = false;
				setLastError("0x8181–¥»Î ˝æ› ß∞‹");
				break;
			}

			if (!sendHostCmd(buffer, 10))
			{
				success = false;
				break;
			}

			for (uint j = 0; j < segment; j += 32)
			{
				if (!i2cAddrRead(0xe700 + j, 2, data + i + j,
					segment - j > 32 ? 32 : segment - j))
				{
					success = false;
					setLastError(C_SPRINTF("∂¡»°0x%x ˝æ› ß∞‹", 0xe700 + j));
					break;
				}
			}

			if (!success)
			{
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

bool Ovx1e::writeData(uint address, const uchar* data, ushort size)
{
	bool result = false, success = true;
	do
	{
		uchar buffer[512] = { 0 };
		buffer[0] = 0x81;
		buffer[1] = 0x00;
		buffer[2] = 0x00;
		buffer[3] = 0x04;
		buffer[4] = 0x10;
		buffer[5] = (address >> 16) & 0xff;
		buffer[6] = (address >> 8) & 0xff;
		buffer[7] = (address >> 0) & 0xff;
		buffer[8] = 0x00;
		buffer[9] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8181, 2, { 0 }), "writeData–¥»Î ß∞‹");

		if (!sendHostCmd(buffer, 10))
		{
			break;
		}

		uint segment = 0;
		for (uint i = 0; i < size; i += 0x100)
		{
			segment = size - i > 0x100 ? 0x100 : size - i;

			memset(buffer, 0, sizeof(buffer));
			buffer[0] = 0x81;
			buffer[1] = 0x00;
			buffer[2] = ((segment + 7) >> 8) & 0xff;
			buffer[3] = ((segment + 7) >> 0) & 0xff;
			buffer[4] = 0x11;
			buffer[5] = 0x00;
			buffer[6] = ((address + i) >> 16) & 0xff;
			buffer[7] = ((address + i) >> 8) & 0xff;
			buffer[8] = ((address + i) >> 0) & 0xff;
			buffer[9] = (segment >> 8) & 0xff;
			buffer[10] = (segment >> 0) & 0xff;

			if (!i2cAddrWrite(0xe400, 2, buffer, 11))
			{
				setLastError("writeData–¥»Î ˝æ› ß∞‹");
				success = false;
				break;
			}

			memcpy(buffer, data + i, segment);

			if (!sendHostCmd(buffer, segment))
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

bool Ovx1e::sendHostCmd(const uchar* data, uint size)
{
	bool result = false, success = true;
	do
	{
		uint pageAddr = 0, segment = 0;
		for (uint i = 0; i < size; i += 32)
		{
			segment = size - i > 32 ? 32 : size - i;

			if (size == 10)
				pageAddr = 0xe400 + i;
			else
				pageAddr = 0xe40b + i;

			if (!i2cAddrWrite(pageAddr, 2, data + i, (ushort)segment))
			{
				success = false;
				setLastError("hostCmd–¥»Î ß∞‹");
				break;
			}
		}

		if (!success)
		{
			break;
		}

		if (!getStatus())
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Ovx1e::initChip()
{
	bool result = false;
	do 
	{
		uchar data[32] = { 0 };

		LIB_RUN_BREAK(!i2cAddrRead(0x300a, 2, data, 1), "0x300a∂¡»° ß∞‹");;
		LIB_RUN_BREAK(data[0] != 0x58, "0x300a∂¡»°◊¥Ã¨≤ªŒ™0x58");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrRead(0x81a8, 2, data, 1), "0x81a8∂¡»° ß∞‹");
		msleep(OVX1E_DELAY);

		if ((data[0] & 0x0f) != 0x05)
		{
			data[0] = 0x80;
			LIB_RUN_BREAK(!i2cAddrWrite(0x8057, 2, data, 1), "0x8058–¥0x80 ß∞‹");
			msleep(OVX1E_DELAY);

			LIB_RUN_BREAK(!i2cAddrWrite(0x805F, 2, data, 1), "0x805F–¥0x80 ß∞‹");
			msleep(OVX1E_DELAY);

			data[0] = 0x01;
			LIB_RUN_BREAK(!i2cAddrWrite(0xA00D, 2, data, 1), "0xA00D–¥0x01 ß∞‹");
			msleep(OVX1E_DELAY);
		}

		data[0] = 0xff;
		LIB_RUN_BREAK(!i2cAddrWrite(0xA013, 2, data, 1), "0xA013–¥0xff ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xA014, 2, data, 1), "0xA014–¥0xff ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xA015, 2, data, 1), "0xA015–¥0xff ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xA016, 2, data, 1), "0xA016–¥0xff ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x3d;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8000, 2, data, 1), "0x8000–¥0x3d ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x01;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8003, 2, data, 1), "0x8003–¥0x01 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrRead(0x8000, 2, data, 1), "0x8000∂¡»° ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] |= 2;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8000, 2, data, 1), "0x8000–¥Ω·π˚ ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x08;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8088, 2, data, 1), "0x8088–¥0x08 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10a, 2, data, 1), "0xa10a–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x7f;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa11e, 2, data, 1), "0xa11e–¥0x7f ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa11d, 2, data, 1), "0xa11d–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x80;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa110, 2, data, 1), "0xa110–¥0x80 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x18;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10f, 2, data, 1), "0xa10f–¥0x18 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10e, 2, data, 1), "0xa10e–¥0x18 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa10d, 2, data, 1), "0xa10d–¥0x18 ß∞‹");
		msleep(OVX1E_DELAY);

		if (!writeInitData())
		{
			break;
		}

		LIB_RUN_BREAK(!i2cAddrRead(0x8000, 2, data, 1), "0x8000∂¡»° ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0x801b, 2, { 0 }), "0x801b–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = (data[0] & (~0x3c)) | 0x3c;//0x3d
		LIB_RUN_BREAK(!i2cAddrWrite(0x8000, 2, data, 1), "0x8000–¥0x3d ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0x8088, 2, data, 1), "0x8088–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0xa10a, 2, data, 1), "0xa10a–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x7f;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa11e, 2, data, 1), "0xa11e–¥0x7f ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa11d, 2, data, 1), "0xa11d–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x80;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa110, 2, data, 1), "0xa110–¥0x80 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x18;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10f, 2, data, 1), "0xa10f–¥0x18 ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x4c;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10e, 2, data, 1), "0xa10e–¥0x4c ß∞‹");
		msleep(OVX1E_DELAY);

		data[0] = 0x00;
		LIB_RUN_BREAK(!i2cAddrWrite(0xa10d, 2, data, 1), "0xa10e–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrRead(0x8195, 2, data, 1), "∂¡»°0x8195 ß∞‹");
		LIB_RUN_BREAK(data[0] != 0x5a, "“˝µºƒ£ Ω0x%x‘À–– ß∞‹", data[0]);
		msleep(OVX1E_DELAY);

		result = true;
	} while (false);
	return result;
}

bool Ovx1e::uninitChip()
{
	bool result = false;
	do
	{
		LIB_RUN_BREAK(!i2cAddrWrite(0x8010, 2, { 0x00 }), "0x8010–¥0x00 ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0x801c, 2, { 0x00,0x00,0x00,0x00 }), "0x801c–¥∂‡ ˝æ› ß∞‹");
		msleep(OVX1E_DELAY);

		LIB_RUN_BREAK(!i2cAddrWrite(0x8018, 2, { 0x00,0x04,0x00,0xc0 }), "0x8018–¥∂‡ ˝æ› ß∞‹");
		msleep(OVX1E_DELAY);

		result = true;
	} while (false);
	return result;
}

bool Ovx1e::writeInitData()
{
	const uchar* data = OVX1E_INIT_DATA;
	uint size = sizeof(OVX1E_INIT_DATA);
	bool result = false, mapping = false, success = true;
	do
	{
		uint sectorSize = 0;
		for (uint i = 0; i < size; i += 4096)
		{
			sectorSize = size - i > 4096 ? 4096 : size - i;
			uint segment = 0, pageAddr = 0;
			for (uint j = 0; j < sectorSize; j += 32)
			{
				segment = sectorSize - j > 32 ? 32 : sectorSize - j;
				pageAddr = 0xb000 + i + j;

				if (pageAddr > 0xffff)
				{
					if (!mapping)
					{
						i2cAddrWrite(0xa10a, 2, { 0x00 });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa11e, 2, { 0x7f });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa11d, 2, { 0x00 });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa110, 2, { 0x80 });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa10f, 2, { 0x18 });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa10e, 2, { 0x50 });
						msleep(OVX1E_DELAY);

						i2cAddrWrite(0xa10d, 2, { 0x00 });
						msleep(OVX1E_DELAY);

						mapping = true;
					}
					pageAddr -= 0x5000;
				}

				if (!i2cAddrWrite(pageAddr, 2, data + i + j, segment))
				{
					success = false;
					setLastError("writeInit–¥»Î ß∞‹");
					break;
				}
			}

			if (!success)
			{
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

bool Ovx1e::getStatus()
{
	bool result = false, success = false;
	do
	{
		//»∑»œ¡¨Ω”
		LIB_RUN_BREAK(!i2cAddrWrite(0x8160, 2, { 0x01 }), "0x8160–¥0x01 ß∞‹");
		msleep(OVX1E_DELAY);

		uchar data[64] = { 0 };
		uint startTime = GetTickCount();
		while (true)
		{
			memset(data, 0x00, sizeof(data));
			if (!i2cAddrRead(0x8180, 2, data, 1))
			{
				setLastError("—≠ª∑∂¡»°0x8180 ß∞‹");
				break;
			}

			if (data[0] == 0x99)
			{
				success = true;
				break;
			}

			if (GetTickCount() - startTime > 5000)
			{
				setLastError("—≠ª∑∂¡»°0x8180≥¨ ±");
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
