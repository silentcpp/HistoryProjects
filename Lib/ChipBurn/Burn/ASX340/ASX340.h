#pragma once
#include "../BaseBurn.h"

class Asx340 : public BaseBurn
{
public:
	Asx340();

	~Asx340();

	bool initialize();

	bool lock();

	bool unlock();

	bool writeFile(const uchar* data, uint size, int* percent);

	bool readFile(uchar* data, uint size, int* percent);

	bool writeFlash(uint address, const uchar* data, ushort size);

	bool readFlash(uint address, uchar* data, ushort size);
protected:
	bool writeData(uint address, const uchar* data, ushort size);

	bool readData(uint address, uchar* data, ushort size);

	ushort getAddress(int cmdPool = 0);

	bool sendHostCmd(ushort cmd);

	bool reset();

	bool isBusy();

	bool query();

	bool initFlash();

	bool initEeprom();

	bool configI2c();

	bool configE2p();
};

