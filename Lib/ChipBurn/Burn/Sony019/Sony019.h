#pragma once
#include "../Sony016/Sony016.h"

class Sony019 : public Sony016
{
public:
	Sony019();

	~Sony019();

	bool initialize();

	bool readFile(uchar* data, uint size, int* percent);

	bool writeFile(const uchar* data, uint size, int* percent);

	bool readFlash(uint address, uchar* data, ushort size);

	bool writeFlash(uint address, const uchar* data, ushort size);
protected:
	bool readData(uint address, uchar* data, ushort size);

	bool writeData(uint address, const uchar* data, ushort size);

	bool registerAllDataWriteToFlash();
private:
	bool eraseFlash(uint address);

	std::deque<uint> m_jumpAddress;
};

