#include "AardvarkDevice.h"

AardvarkDevice::AardvarkDevice()
{

}

AardvarkDevice::~AardvarkDevice()
{
	close();
}

bool AardvarkDevice::open(int port, int bitrate, int timeout)
{
	bool result = false;
	do
	{
		Aardvark handle = aa_open(port);
		if (handle <= 0)
		{
			setLastError(QString().sprintf("打开烧录器通道%d失败", port));
			break;
		}

		aa_configure(handle, AA_CONFIG_SPI_I2C);

		aa_i2c_pullup(handle, AA_I2C_PULLUP_BOTH);

		aa_target_power(handle, AA_TARGET_POWER_BOTH);

		aa_i2c_slave_disable(handle);

		if (bitrate != aa_i2c_bitrate(handle, bitrate))
		{
			setLastError("设置波特率错误");
			aa_close(handle);
			break;
		}

		if (timeout != aa_i2c_bus_timeout(handle, timeout))
		{
			setLastError("设置超时错误");
			aa_close(handle);
			break;
		}

		m_handle = handle;
		m_port = port;
		m_open = true;
		result = true;
	} while (false);
	return result;
}

bool AardvarkDevice::close()
{
	bool result = false;
	do
	{
		if (m_open && (aa_close(m_handle) != 1))
		{
			setLastError("关闭烧录器失败");
			break;
		}

		m_open = false;
		m_handle = 0;
		m_port = -1;
		result = true;
	} while (false);
	return result;
}

int AardvarkDevice::readData(uchar* data, ushort size, ushort slave)
{
	int result = aa_i2c_read(m_handle, slave, AA_I2C_NO_FLAGS, size, data);
	if (result < 0)
	{
		setLastError(QString().sprintf("读取失败,%s", aa_status_string(result)));
	}
	else if (result == 0)
	{
		setLastError("读取失败,从地址不正确或解码板故障");
	}
	else if (result != size)
	{
		setLastError(QString().sprintf("读取丢失%d个字节,解码板不稳定或速率太快", size - result));
	}
	return result;
}

int AardvarkDevice::writeData(const uchar* data, ushort size, ushort slave)
{
	int result = aa_i2c_write(m_handle, slave, AA_I2C_NO_FLAGS, size, data);
	if (result < 0)
	{
		setLastError(QString().sprintf("写入失败,%s", aa_status_string(result)));
	}
	else if (result == 0)
	{
		setLastError("写入失败,从地址不正确或解码板故障");
	}
	else if (result != size)
	{
		setLastError(QString().sprintf("写入丢失%d个字节,解码板不稳定或速度太快", size - result));
	}
	return result;
}
