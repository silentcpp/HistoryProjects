#include "Sony016.h"

Sony016::Sony016()
{
	m_cmdAddrLen = 2;
}

Sony016::~Sony016()
{

}

bool Sony016::initialize()
{
	bool result = false, success = true;
	do
	{
		if (m_chipType == CT_SONY016_EEPROM_UNIVERSAL_SET)
		{
			uchar addr[] = { 0x0d,0x07,0x04,0x0e };
			uchar data[] = { 0x87,0x86,0x47,0x02 };
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
		else
		{
			setLastError("不支持的烧录模式");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool Sony016::lock()
{
	bool result = false, success = true;
	do
	{
		uchar wdata[9] = { 0x09,0x01,0x06,0x00,0x57,0x52,0x44,0x53,0x50 };
		uchar rdata[5] = { 0x05,0x01,0x02,0x01,0x09 };
		uchar req[5] = { 0 };

		if (9 != i2cWrite(wdata, 9))
		{
			break;
		}

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}

		result = true;
	} while (false);
	return result;
}

bool Sony016::unlock()
{
	bool result = false, success = true;
	do
	{
		uchar wdata[9] = { 0x09,0x01,0x06,0x00,0x57,0x52,0x45,0x4e,0x4c };
		uchar rdata[5] = { 0x05,0x01,0x02,0x01,0x09 };
		uchar req[5] = { 0 };

		if (9 != i2cWrite(wdata, 9))
		{
			break;
		}

		msleep(100);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(100);

		result = true;
	} while (false);
	return result;
}

bool Sony016::readFile(uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		LIB_RUN_BREAK(!unlock(), "解锁失败");

		for (uint i = 0; i < size; i += 8)
		{
			if (!readData(i, data + i, size - i > 8 ? 8 : size - i))
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

		LIB_RUN_BREAK(!protect(), "写保护失败");

		LIB_RUN_BREAK(!lock(), "加锁失败");
		result = true;
	} while (false);
	return result;
}

bool Sony016::writeFile(const uchar* data, uint size, int* percent)
{
	bool result = false, success = true;
	do
	{
		LIB_RUN_BREAK(!unlock(), "解锁失败");
		for (uint i = 0; i < size; i += 8)
		{
			if (!writeData(i, data + i, size - i > 8 ? 8 : size - i))
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
		LIB_RUN_BREAK(!lock(), "加锁失败");
		result = true;
	} while (false);
	return result;
}

bool Sony016::readEeprom(uint address, uchar* data, ushort size)
{
	return readData(address, data, size);
}

bool Sony016::writeEeprom(uint address, const uchar* data, ushort size)
{
	return writeData(address, data, size);
}

bool Sony016::readData(uint address, uchar* data, ushort size)
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };

		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_READ_EEP;

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

		frame.cmd[0].data[m_cmdAddrLen] = (uchar)size;
		frame.cmd[0].total_cmd_byte = 3 + m_cmdAddrLen;
		if (!writeFrame(frame))
		{
			break;
		}

		memset(&frame, 0, sizeof(SonyCmdFrame));
		if (!readFrame(&frame, 5 + size))
		{
			break;
		}

		if (SC016_SUCCESS != frame.cmd[0].cmd_and_status_code)
		{
			setErrorInfo(frame.cmd[0].cmd_and_status_code);
			break;
		}

		LIB_RUN_BREAK(frame.total_byte != size + 5, "总字节长度错误");

		memcpy(data, frame.cmd[0].data, size);

		result = true;
	} while (false);
	return result;
}

bool Sony016::writeData(uint address, const uchar* data, ushort size)
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };
		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_WRITE_EEP;

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

		memcpy(&frame.cmd[0].data[m_cmdAddrLen], data, size);
		frame.cmd[0].total_cmd_byte = 2 + size + m_cmdAddrLen;
		if (!writeFrame(frame))
		{
			break;
		}

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

bool Sony016::packFrame(SonyCmdFrame i2cCmd, uchar* data)
{
	bool result = false;
	do
	{
		if (i2cCmd.cmd_cnt > SONY_CMD_MAX_CNT)
		{
			setLastError(C_SPRINTF("命令行总数为%d大于上限%d", i2cCmd.cmd_cnt, SONY_CMD_MAX_CNT));
			break;
		}

		data[1] = i2cCmd.cmd_cnt;
		uchar* pcmd = &data[2];
		for (int i = 0; i < i2cCmd.cmd_cnt; i++)
		{
			memcpy(&pcmd[0], &i2cCmd.cmd[i].total_cmd_byte, 1);
			memcpy(&pcmd[1], &i2cCmd.cmd[i].cmd_and_status_code, 1);
			memcpy(&pcmd[2], i2cCmd.cmd[i].data, i2cCmd.cmd[i].total_cmd_byte - 2);

			pcmd += i2cCmd.cmd[i].total_cmd_byte;
			i2cCmd.total_byte += i2cCmd.cmd[i].total_cmd_byte;
		}
		i2cCmd.total_byte += 3;
		data[0] = i2cCmd.total_byte;
		pcmd[0] = 0;
		for (int i = 0; i < i2cCmd.total_byte - 1; i++)
		{
			pcmd[0] += data[i];
		}
		result = true;
	} while (false);
	return result;
}

bool Sony016::unpackFrame(SonyCmdFrame* frame, const uchar* data, uchar size)
{
	bool result = false, success = true;
	do
	{
		if (data[0] != size)
		{
			for (int i = 1; i < size; i++)
			{
				if (data[i] != 0)
				{
					success = false;
					break;
				}
			}

			if (success)
			{
				frame->cmd[0].cmd_and_status_code = data[0];
				return true;
			}

			size = data[0];
		}

		if (data[1] <= 0)
		{
			setLastError("命令行总数不能小于等于0");
			break;
		}

		uchar checkSum = 0;
		for (int i = 0; i < size - 1; i++)
		{
			checkSum += data[i];
		}

		if (checkSum != data[size - 1])
		{
			setLastError("校验和错误");
			break;
		}

		frame->total_byte = size;
		frame->cmd_cnt = data[1];
		frame->check_sum = data[size - 1];
		const uchar* pcmd = &data[2];
		for (int i = 0; i < frame->cmd_cnt; i++)
		{
			frame->cmd[i].total_cmd_byte = pcmd[0];
			frame->cmd[i].cmd_and_status_code = pcmd[1];
			memcpy(frame->cmd[i].data, &pcmd[2], frame->cmd[i].total_cmd_byte - 2);
			pcmd += frame->cmd[i].total_cmd_byte;
		}
		result = true;
	} while (false);
	return result;
}

bool Sony016::readFrame(SonyCmdFrame* frame, uchar size)
{
	bool result = false;
	do
	{
		uchar data[SONY_CMD_FRAME_MAX_LEN * 2] = { 0 };
		int count = i2cRead(data, size);
		if (count <= 0)
		{
			break;
		}

		if (!unpackFrame(frame, data, count))
		{
			break;
		}

		//msleep(1);
		result = true;
	} while (false);
	return result;
}

bool Sony016::writeFrame(SonyCmdFrame frame)
{
	bool result = false;
	do
	{
		if (frame.cmd_cnt <= 0)
		{
			setLastError("命令行写入长度小于等于0");
			break;
		}

		uchar data[SONY_CMD_FRAME_MAX_LEN * 2] = { 0 };
		if (!packFrame(frame, data))
		{
			break;
		}

		int count = i2cWrite(data, data[0]);
		if (count != data[0])
		{
			break;
		}

		//msleep(2);
		result = true;
	} while (false);
	return result;
}

bool Sony016::readRegister(uchar category, ushort addrOffset, uchar* data, uchar dataSize)
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };
		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_READ_REG;
		frame.cmd[0].data[0] = category;
		frame.cmd[0].data[1] = (addrOffset & 0xFF00) >> 8;
		frame.cmd[0].data[2] = addrOffset & 0x00FF;
		frame.cmd[0].data[3] = dataSize;
		frame.cmd[0].total_cmd_byte = 6;
		if (!writeFrame(frame))
		{
			break;
		}

		memset(&frame, 0, sizeof(SonyCmdFrame));
		if (!readFrame(&frame, 5 + dataSize))
		{
			break;
		}

		if (SC016_SUCCESS != frame.cmd[0].cmd_and_status_code)
		{
			setErrorInfo(frame.cmd[0].cmd_and_status_code);
			break;
		}

		LIB_RUN_BREAK(frame.total_byte != dataSize + 5, "总字节长度错误");
		memcpy(data, frame.cmd[0].data, dataSize);

		result = true;
	} while (false);
	return result;
}

bool Sony016::writeRegister(uchar category, ushort addrOffset, const uchar* data, uchar dataSize)
{
	bool result = false;
	do
	{
		SonyCmdFrame frame = { 0 };

		frame.cmd_cnt = 1;
		frame.cmd[0].cmd_and_status_code = CMD_WRITE_REG;
		frame.cmd[0].data[0] = category;
		frame.cmd[0].data[1] = (addrOffset & 0xFF00) >> 8;
		frame.cmd[0].data[2] = addrOffset & 0x00FF;
		memcpy(&frame.cmd[0].data[3], data, dataSize);
		frame.cmd[0].total_cmd_byte = 5 + dataSize;
		if (!writeFrame(frame))
		{
			break;
		}

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

bool Sony016::tempInit()
{
	bool result = false, success = true;
	do
	{
		uchar wdata1[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x60,0x8c,0x0a };
		uchar wdata2[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x64,0x01,0x83 };
		uchar wdata3[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x6c,0x01,0x8b };
		uchar wdata4[9] = { 0x09,0x01,0x06,0x01,0x0c,0x00,0x68,0x01,0x86 };
		uchar rdata[5] = { 0x05,0x01,0x02,0x01,0x09 };
		uchar rdata1[6] = { 0x06,0x01,0x03,0x01,0x8c,0x97 };
		uchar req[5] = { 0 }, req1[6] = { 0 };

		if (9 != i2cWrite(wdata1, 9))
		{
			break;
		}
		msleep(100);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata2, 9))
		{
			break;
		}
		msleep(100);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata3, 9))
		{
			break;
		}
		msleep(20);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata4, 9))
		{
			break;
		}
		msleep(20);

		if (6 != i2cRead(req1, 6))
		{
			break;
		}

		for (int i = 0; i < 6; i++)
		{
			if (rdata1[i] != req1[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		result = true;
	} while (false);
	return result;
}

bool Sony016::tempUnint()
{
	bool result = false, success = true;
	do
	{
		uchar wdata1[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x60,0x80,0xfe };
		uchar wdata2[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x64,0x01,0x83 };
		uchar wdata3[9] = { 0x09,0x01,0x06,0x02,0x0c,0x00,0x6c,0x01,0x8b };
		uchar wdata4[9] = { 0x09,0x01,0x06,0x01,0x0c,0x00,0x68,0x01,0x86 };
		uchar rdata[5] = { 0x05,0x01,0x02,0x01,0x09 };
		uchar rdata1[6] = { 0x06,0x01,0x03,0x01,0x80,0x8b };
		uchar req[5] = { 0 }, req1[6] = { 0 };

		if (9 != i2cWrite(wdata1, 9))
		{
			break;
		}
		msleep(100);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata2, 9))
		{
			break;
		}
		msleep(100);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata3, 9))
		{
			break;
		}
		msleep(20);

		if (5 != i2cRead(req, 5))
		{
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			if (rdata[i] != req[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		if (9 != i2cWrite(wdata4, 9))
		{
			break;
		}
		msleep(20);

		if (6 != i2cRead(req1, 6))
		{
			break;
		}

		for (int i = 0; i < 6; i++)
		{
			if (rdata1[i] != req1[i])
			{
				success = false;
				break;
			}
		}

		if (!success)
		{
			setErrorInfo(req[3]);
			break;
		}
		msleep(10);

		result = true;
	} while (false);
	return result;
}

void Sony016::setErrorInfo(uchar code)
{
	switch (code)
	{
	case SC016_SUCCESS:
		setLastError("成功");
		break;

	case SC016_ERR_EFFI_NUM:
		setLastError("效率通信字节数错误");
		break;

	case SC016_ERR_CMD_NUM_NOT_EXIST:
		setLastError("命令编号错误(命令行不存在)");
		break;

	case SC016_ERR_CAT_NUM:
		setLastError("类别号错误");
		break;

	case SC016_ERR_ADDR_OFFSET:
		setLastError("字节偏移量错误");
		break;

	case SC016_ERR_ACCESS:
		setLastError("访问错误");
		break;

	case SC016_ERR_CMD_NUM_NOT_MATCH:
		setLastError("命令编号错误(命令不匹配)");
		break;

	case SC016_ERR_CHECK_SUM:
		setLastError("校验和错误");
		break;

	case SC016_ERR_TOTAL_BYTE_NUM:
		setLastError("总字节数错误");
		break;

	case SC016_ERR_EEP_ACCESS:
		setLastError("EEPROM访问错误");
		break;

	case SC016_ERR_COMMUNICATION:
		setLastError("通信错误");
		break;

	default:
		setLastError("未知错误,可能速率太快");
		break;
	}
	return;
}

bool Sony016::protect()
{
	bool result = false;
	do
	{
		uchar data[256] = { 0 };
		data[0] = 0x02;
		if (!i2cAddrWrite(0x0E, 1, data, 1, true, SLAVE_ADDR_96701))
		{
			break;
		}
		msleep(100);

		data[0] = 0x8c;
		if (!writeRegister(0x0c, 0x0060, data, 1))
		{
			break;
		}
		msleep(300);

		data[0] = 0x01;
		if (!writeRegister(0x0c, 0x0064, data, 1))
		{
			break;
		}
		msleep(100);

		data[0] = 0x01;
		if (!writeRegister(0x0c, 0x006c, data, 1))
		{
			break;
		}
		msleep(100);

		if (!readRegister(0x0c, 0x0068, data, 1))
		{
			break;
		}

		LIB_RUN_BREAK(data[0] != 0x8c, "0x0c寄存器不等于0x8c");
		msleep(100);

		if (!unlock())
		{
			break;
		}
		msleep(100);

		if (!readData(0x0126, data, 1))
		{
			break;
		}
		msleep(10);

		uchar value = data[0] + 1;
		if (!writeData(0x0126, &value, 1))
		{
			break;
		}
		msleep(10);

		value = data[0] + 2;
		if (!readData(0x0126, &value, 1))
		{
			break;
		}
		msleep(10);

		if (value == data[0] + 1)
		{
			if (!writeData(0x0126, data, 1))
			{
				break;
			}
			msleep(10);

			if (!readData(0x0126, &value, 1))
			{
				break;
			}
			msleep(10);

			if (value != data[0])
			{
				setLastError("地址0x0126对比失败");
				break;
			}
			break;
		}

		if (!lock())
		{
			break;
		}
		msleep(10);

		result = true;
	} while (false);
	return result;
}

bool Sony016::unprotect()
{
	bool result = false;
	do
	{
		uchar data[256] = { 0 };
		data[0] = 0x02;
		if (!i2cAddrWrite(0x0E, 1, data, 1, true, SLAVE_ADDR_96701))
		{
			break;
		}
		msleep(100);

		data[0] = 0x80;
		if (!writeRegister(0x0c, 0x0060, data, 1))
		{
			break;
		}
		msleep(300);

		data[0] = 0x01;
		if (!writeRegister(0x0c, 0x0064, data, 1))
		{
			break;
		}
		msleep(1100);

		data[0] = 0x01;
		if (!writeRegister(0x0c, 0x006c, data, 1))
		{
			break;
		}
		msleep(300);

		if (!readRegister(0x0c, 0x0068, data, 1))
		{
			break;
		}

		if (data[0] != 0x80)
		{
			setLastError("0x0c寄存器不等于0x80");
			break;
		}
		msleep(100);

		if (!unlock())
		{
			break;
		}
		msleep(10);

		if (!readData(0x0126, data, 1))
		{
			break;
		}
		msleep(10);

		uchar value = data[0] + 1;
		if (!writeData(0x0126, &value, 1))
		{
			break;
		}
		msleep(100);

		value = data[0] + 2;
		if (!readData(0x0126, &value, 1))
		{
			break;
		}
		msleep(100);

		if (value != data[0] + 1)
		{
			setLastError("地址0x0126对比1失败");
			break;
		}

		if (!writeData(0x0126, data, 1))
		{
			break;
		}
		msleep(100);

		if (!readData(0x0126, &value, 1))
		{
			break;
		}
		msleep(100);

		if (value != data[0])
		{
			setLastError("地址0x0126对比2失败");
			break;
		}

		if (!lock())
		{
			break;
		}
		msleep(100);
		result = true;
	} while (false);
	return result;
}

bool Sony016::convertToAddress()
{
	uchar data[1] = { 0 };
	return writeData(0x0154, data, 1);
}

bool Sony016::changeFlashStatus()
{
	/*
	* @索尼016"FLASH"
	* @notice,FLASH已弃用,
	* 现在为EEPROM.
	* 地址0xffff
	* 写0xf1,改变为读状态
	* 写0xf0,改编为写状态
	*/
	return i2cAddrWrite(0xFFFF, 2, { 0xf1 });
}


