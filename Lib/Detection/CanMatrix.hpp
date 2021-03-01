#ifndef CAN_MATRIX_H
#define CAN_MATRIX_H

/* 
							CAN矩阵图

		   bit7	   bit6	   bit5	   bit4	   bit3	   bit2	   bit1	   bit0
	byte0	7		6		5		4		3		2		1		0

	byte1	15		14		13		12		11		10		9		8
	
	byte2	23		22		21		20		19		18		17		16
	
	byte3	31		30		29		28		27		26		25		24

	byte4	39		38		37		36		35		34		33		32

	byte5	47		46		45		44		43		42		41		40

	byte6	55		54		53		52		51		50		49		48

	byte7	63		62		61		60		59		58		57		56


	M_MSB矩阵样例[防止忘记计算原理]

	时间同步

	Second		起始位07		信号长度6

	Hour			起始位09		信号长度5

	Minute		起始位15		信号长度6

	Day			起始位17		信号长度5

	Year			起始位24		信号长度5	 偏移量2014

	Month		起始位28		信号长度4

	unsignal char data[8] = {0};

	data[0] = (0x3f & time.wSecond) << 2;

	data[1] = (0x03 & time.wHour) >> 3;
	
	data[2] = (0x07 & time.wHour) << 5;
	
	data[1] |= (0x3f & time.wMinute) << 2;
	
	data[2] |= (0x1f & time.wDay) >> 3;
	
	data[3] = (0x07 & time.wDay) << 5;
	
	data[3] |= (0x1f & (time.wYear - 2014)) >> 4;
	
	data[4] = (0x0f & (time.wYear - 2014)) << 4;
	
	data[3] |= (0x0f & time.wMonth) << 1;


	M_LSB矩阵样例[防止忘记计算原理]
	
	屏幕坐标点击

	Touch Status		起始位20		信号长度02	1按下,2抬起

	Y 坐标			起始位36		信号长度12

	X 坐标			起始位40		信号长度12

	int x = 1011,y = 576;

	data[2] = 1 << 4;

	data[3] = (y >> 4) & 0xFF;

	data[4] |= ((y & 0x0F) << 4);

	data[4] |= ((x >> 8) & 0x0F);

	data[5] = x & 0xFF;
*/

#include <bitset>
#include <string.h>

#define MATRIX_VERSION "1.0.0.0"

#define MATRIX_LENGTH 64

enum class MatrixType {
	MT_MOTOROLA_LSB,
	MT_MOTOROLA_MSB,
	MT_INTEL
};

class CanMatrix
{
public:
	CanMatrix(const MatrixType& type = MatrixType::MT_MOTOROLA_LSB):m_type(type) {}

	~CanMatrix() {}

	const char* getLastError() { return m_lastError; }

	static const char* getVersion() { return MATRIX_VERSION; }

	void setType(const MatrixType& type) { m_type = type; }

	const MatrixType getType() { return m_type; }

	const char* getName()
	{
		const char* name = "Unknown";
		switch (m_type)
		{
		case MatrixType::MT_MOTOROLA_LSB:name = "Motorola LSB";break;
		case MatrixType::MT_MOTOROLA_MSB:name = "Motorola MSB";break;
		case MatrixType::MT_INTEL:name = "Intel";break;
		default:break;
		}
		return name;
	}

	template <class T> bool pack(unsigned char* buffer, const int& start, const int& length, const T& data);

	template <class T> bool unpack(const unsigned char* buffer, const int& start, const int& length, T& data);

protected:
	void setLastError(const char* error) { strcpy(m_lastError, error); }

	const unsigned long long setBit1(const size_t& length)
	{
		std::bitset<MATRIX_LENGTH> bit;
		for (int i = 0; i < length; i++)
			bit.set(i);
		return bit.to_ullong();
	}

	const unsigned long long setBit0(const size_t& length)
	{
		std::bitset<MATRIX_LENGTH> bit;
		for (int i = 0; i < length; i++)
			bit.set(i, false);
		return bit.to_ullong();
	}

	bool getPosition(const int& startPos, int* bytePos, int* bitPos)
	{
		bool result = false;
		do
		{
			if (!startPos)
			{
				*bytePos = *bitPos = 0;
			}
			else if (!(startPos % 8) && startPos)
			{
				*bytePos = startPos / 8;
				bitPos = 0;
			}
			else if ((startPos % 8) && startPos)
			{
				if (startPos < 8)
				{
					*bytePos = 0;
					*bitPos = startPos;
				}
				else
				{
					*bytePos = startPos / 8;
					*bitPos = startPos - *bytePos * 8;
				}
			}
			else
			{
				setLastError("无效的起始位置");
				break;
			}
			result = true;
		} while (false);
		return result;
	}

	bool assertLength(const int& bytePos, const int& bitPos, const int& dataLen)
	{
		bool result = false;
		do
		{
			int bitLen = 0;
			if (m_type == MatrixType::MT_MOTOROLA_LSB)
			{
				bitLen = (bytePos + 1) * 8 - bitPos;
			}
			else if (m_type == MatrixType::MT_MOTOROLA_MSB)
			{
				bitLen = abs((bytePos + 1) * 8 - MATRIX_LENGTH) + bitPos + 1;
			}
			else
			{
				bitLen = abs((bytePos + 1) * 8 - MATRIX_LENGTH) + 8 - bitPos;
			}

			if (dataLen > bitLen)
			{
				setLastError("数据长度已越界,超过0~64范围");
				break;
			}
			result = true;
		} while (false);
		return result;
	}

	template<class T> bool selfTest(const int& start, const int& length, const T& data, int* bytePos, int* bitPos)
	{
		bool result = false;
		do
		{
			if (m_type != MatrixType::MT_INTEL &&
				m_type != MatrixType::MT_MOTOROLA_LSB &&
				m_type != MatrixType::MT_MOTOROLA_MSB)
			{
				setLastError("无效的矩阵类型");
				break;
			}

			if (start < 0 || start > 64)
			{
				setLastError("起始位置超过0~64位范围");
				break;
			}

			if (length < 0 || length > 64)
			{
				setLastError("数据长度超过0~64位范围");
				break;
			}

			if (setBit1(length) < data)
			{
				setLastError("位长度没有足够的空间存放数据");
				break;
			}

			if (length > MATRIX_LENGTH)
			{
				setLastError("位长度超过64位");
				break;
			}

			if (!getPosition(start, bytePos, bitPos) ||
				!assertLength(*bytePos, *bitPos, length))
			{
				break;
			}
			result = true;
		} while (false);
		return result;
	}
private:
	MatrixType m_type = MatrixType::MT_MOTOROLA_LSB;

	char m_lastError[64] = { "No Error" };
};

template<class T> inline bool CanMatrix::pack(unsigned char* buffer, const int& start, const int& length, const T& data)
{
	bool result = false;
	do
	{
		int bytePos = 0, bitPos = 0;
		if (!selfTest(start, length, data, &bytePos, &bitPos))
		{
			break;
		}

		if (m_type == MatrixType::MT_INTEL)
		{
			int offset = bitPos + length;
			if (offset > 8)
			{
				int index = 0;
				while ((offset -= 8) > 8)
				{
					index++;
				}

				if (offset > 0)
				{
					index++;
				}

				//第一个偏移数量,为最小下标所<<
				const int firstOffset = bitPos;

				//第一个数据长度
				const int firstDataLen = 8 - firstOffset;

				//最后一个偏移数量,为最大下标所>>
				const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

				//最后一个数据长度
				const int lastDataLen = length - lastOffset;

				//起始位
				const int startPos = bytePos;

				//结束位
				const int endPos = bytePos + index;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						//必须先&
						buffer[i] |= (data & setBit1(firstDataLen)) << firstOffset;
					}
					else if (i == endPos)
					{
						//必须先>>
						buffer[i] |= (data >> lastOffset) & setBit1(lastDataLen);
					}
					else
					{
						const int tempOffset = (i - startPos - 1) * 8 + firstDataLen;
						buffer[i] |= (data >> tempOffset) & 0xff;
					}
				}
			}
			else
			{
				buffer[bytePos] |= (data & setBit1(length)) << bitPos;
			}
		}
		else if (m_type == MatrixType::MT_MOTOROLA_LSB)
		{
			int offset = bitPos + length;
			if (offset > 8)
			{
				int index = 0;

				while ((offset -= 8) > 8)
				{
					index++;
				}

				if (offset > 0)
				{
					index++;
				}

				//第一个偏移数量,为最小下标所>>
				const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

				//第一个数据长度
				const int firstDataLen = length - firstOffset;

				//最后一个偏移数量,为最大下标所<<
				const int lastOffset = bitPos;

				//最后一个数据长度
				const int lastDataLen = 8 - lastOffset;

				//起始位
				const int startPos = bytePos - index;

				//结束位
				const int endPos = bytePos;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						//必须先>>
						buffer[i] |= (data >> firstOffset) & setBit1(firstDataLen);
					}
					else if (i == endPos)
					{
						//必须先&
						buffer[i] |= (data & setBit1(lastDataLen)) << lastOffset;
					}
					else
					{
						const int tempOffset = (endPos - i - 1) * 8 + lastDataLen;
						buffer[i] |= (data >> tempOffset) & 0xff;
					}
				}
			}
			else
			{
				buffer[bytePos] |= (data & setBit1(length)) << bitPos;
			}
		}
		else if (m_type == MatrixType::MT_MOTOROLA_MSB)
		{
			int offset = bitPos - length + 1;

			if (offset < 0)
			{
				//数组下标
				int index = 0;

				offset = abs(offset);

				//第一个偏移数量,为最小下标所>>
				const int firstOffset = offset;

				//获取需要计算数组的数量
				while ((offset -= 8) > 0)
				{
					index++;
				}

				//如果存在余数,继续累加
				offset = abs(offset);
				if (offset > 0)
				{
					index++;
				}

				//最后一个偏移数量,为最大下标所<<
				const int lastOffset = offset;

				//起始位置长度
				const int firstDataLen = bitPos + 1;

				//结束位置长度
				const int lastDataLen = 8 - offset;

				//起始位
				const int startPos = bytePos;

				//结束位
				const int endPos = bytePos + index;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						buffer[i] |= (data >> firstOffset) & setBit1(firstDataLen);
					}
					else if (i == endPos)
					{
						buffer[i] |= (data & setBit1(lastDataLen)) << lastOffset;
					}
					else
					{
						const int tempOffset = (i - startPos - 1) * 8 + lastDataLen;
						buffer[i] |= (data >> tempOffset) & 0xff;
					}
				}
			}
			else
			{
				buffer[bytePos] |= (data & setBit1(length)) << offset;
			}
		}
		result = true;
	} while (false);
	return result;
}

template<class T> inline bool CanMatrix::unpack(const unsigned char* buffer, const int& start, const int& length, T& data)
{
	bool result = false;
	do
	{
		//必须要清零
		memset(&data, 0, sizeof(T));
		int bytePos = 0, bitPos = 0;
		if (!selfTest(start, length, 0, &bytePos, &bitPos))
		{
			break;
		}

		if (m_type == MatrixType::MT_INTEL)
		{
			int offset = bitPos + length;
			if (offset > 8)
			{
				int index = 0;
				while ((offset -= 8) > 8)
				{
					index++;
				}

				if (offset > 0)
				{
					index++;
				}

				//第一个偏移数量,为最小下标所<<
				const int firstOffset = bitPos;

				//第一个数据长度
				const int firstDataLen = 8 - firstOffset;

				//最后一个偏移数量,为最大下标所>>
				const int lastOffset = ((index - 1) * 8) + 8 - bitPos;

				//最后一个数据长度
				const int lastDataLen = length - lastOffset;

				//起始位
				const int startPos = bytePos;

				//结束位
				const int endPos = bytePos + index;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						//必须先>>
						data |= (buffer[i] >> firstOffset) & setBit1(firstDataLen);
					}
					else if (i == endPos)
					{
						//必须先&
						data |= static_cast<T>(buffer[i] & setBit1(lastDataLen)) << lastOffset;
					}
					else
					{
						const int tempOffset = (i - startPos - 1) * 8 + firstDataLen;
						data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
					}
				}
			}
			else
			{
				data |= (buffer[bytePos] >> bitPos) & setBit1(length);
			}
		}
		else if (m_type == MatrixType::MT_MOTOROLA_LSB)
		{
			int offset = (bitPos + length);
			if (offset > 8)
			{
				//数组下标
				int index = 0;

				while ((offset -= 8) > 8)
				{
					index++;
				}

				if (offset > 0)
				{
					index++;
				}

				//第一个偏移数量,为最小下标所<<
				const int firstOffset = ((index - 1) * 8) + 8 - bitPos;

				//第一个数据长度,目前暂时用不到
				const int firstDataLen = length - firstOffset;

				//最后一个偏移数量,为最大下标所>>
				const int lastOffset = bitPos;

				//最后一个数据长度
				const int lastDataLen = 8 - lastOffset;

				//起始位
				const int startPos = bytePos - index;

				//结束位
				const int endPos = bytePos;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						data |= static_cast<T>(buffer[i] & setBit1(firstDataLen)) << firstOffset;
					}
					else if (i == endPos)
					{
						data |= (buffer[i] >> lastOffset) & setBit1(lastDataLen);
					}
					else
					{
						const int tempOffset = (endPos - i - 1) * 8 + lastDataLen;
						data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
					}
				}
			}
			else
			{
				data |= (buffer[bytePos] >> bitPos) & setBit1(length);
			}
		}
		else if (m_type == MatrixType::MT_MOTOROLA_MSB)
		{
			int offset = bitPos - length + 1;

			if (offset < 0)
			{
				//数组下标
				int index = 0;

				offset = abs(offset);

				//第一个偏移数量,为最小下标所>>
				const int firstOffset = offset;

				//获取需要计算数组的数量
				while ((offset -= 8) > 0)
				{
					index++;
				}

				//如果存在余数,继续累加
				offset = abs(offset);
				if (offset > 0)
				{
					index++;
				}

				//最后一个偏移数量,为最大下标所<<
				const int lastOffset = offset;

				//起始位置长度
				const int firstDataLen = bitPos + 1;

				//结束位置长度
				const int lastDataLen = 8 - offset;

				//起始位
				const int startPos = bytePos;

				//结束位
				const int endPos = bytePos + index;

				for (int i = startPos; i <= endPos; i++)
				{
					if (i == startPos)
					{
						data |= static_cast<T>(buffer[i] & setBit1(firstDataLen)) << firstOffset;
					}
					else if (i == endPos)
					{
						data |= (buffer[i] >> lastOffset) & setBit1(lastDataLen);
					}
					else
					{
						const int tempOffset = (i - startPos - 1) * 8 + lastDataLen;
						data |= static_cast<T>(buffer[i] & 0xff) << tempOffset;
					}
				}
			}
			else
			{
				data |= (buffer[bytePos] >> offset) & setBit1(length);
			}
		}
		result = true;
	} while (false);
	return result;
}
#endif//!CAN_MATRIX_H
