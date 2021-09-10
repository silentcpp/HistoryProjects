#pragma once
#include "../BaseDevice.h"
#include "aardvark.h"

class AardvarkDevice : public BaseDevice
{
public:
	AardvarkDevice();

	~AardvarkDevice();

	bool open(int port, int bitrate /* = 400 */, int timeout /* = 150 */);

	bool close();

	int readData(uchar* data, ushort size, ushort slave);

	int writeData(const uchar* data, ushort size, ushort slave);
private:
	Aardvark m_handle = 0;
};

