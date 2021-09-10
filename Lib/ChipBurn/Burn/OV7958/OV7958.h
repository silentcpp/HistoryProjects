#pragma once
#include "../BaseBurn.h"

class Ov7958 : public BaseBurn
{
public:
	Ov7958();

	~Ov7958();

	bool initialize();

	bool readFile(uchar* data, uint size, int* percent);

	bool writeFile(const uchar* data, uint size, int* percent);

protected:
	bool readData(uint address, uchar* data, ushort size);

	bool writeData(uint address, const uchar* data, ushort size);

	bool earseAll();

	bool getStatus();

	bool setProtect(bool protect);
};

