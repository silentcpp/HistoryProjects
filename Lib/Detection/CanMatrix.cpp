#include "CanMatrix.h"

const uchar CanMatrix::m_canMatrix[8][8] = {
{07,06,05,04,03,02,01,00},
{15,14,13,12,11,10,9,8},
{23,22,21,20,19,18,17,16},
{31,30,29,28,27,26,25,24},
{39,38,37,36,35,34,33,32},
{47,46,45,44,43,42,41,40},
{55,54,53,52,51,50,49,48},
{63,62,61,60,59,58,57,56}
};

void CanMatrix::setLastError(const std::string& err)
{
	m_lastError = err;
}

bool CanMatrix::getCanMatrixPos(const int& startPos, int& bufferPos, int& bitPos)
{
	bool result = false;
	do
	{
		if (!startPos)
		{
			bufferPos = bitPos = 0;
		}
		else if (!(startPos % 8) && startPos)
		{
			bufferPos = startPos / 8;
			bitPos = 0;
		}
		else if ((startPos % 8) && startPos)
		{
			if (startPos < 8)
			{
				bufferPos = 0;
				bitPos = startPos;
			}
			else
			{
				bufferPos = startPos / 8;
				bitPos = startPos - bufferPos * 8;
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

const ulong CanMatrix::bitSet(const int& length)
{
	return std::bitset<64>().set(length).to_ulong() - 1;
}

CanMatrix::CanMatrix(const MatrixType& matrixType) :
	m_matrixType(matrixType)
{
}

CanMatrix::~CanMatrix()
{

}

const std::string& CanMatrix::getLastError()
{
	return m_lastError;
}

void CanMatrix::setMatrixType(const MatrixType& matrixType)
{
	m_matrixType = matrixType;
}

bool CanMatrix::pack(uchar* buffer, const int& start, const int& length, const int& data)
{
	bool result = false;
	do
	{
		int bufPos = 0, bitPos = 0;
		if (!getCanMatrixPos(start, bufPos, bitPos))
		{
			break;
		}

		try
		{
			if (m_matrixType == MatrixType::MT_INTEL)
			{

			}
			else if (m_matrixType == MatrixType::MT_MOTOROLA_LSB)
			{
				/*	bufPos 4			  */
				/*  start 39    length 19 */
				/*	offset 26,  bitPos 7*/
				int offset = (bitPos + length);
				if (offset > 8)
				{
					/*跨字节*/
					int offCnt = 0;

					while ((offset -= 8) > 8)
					{
						offCnt++;
					}

					/*余数 offset,2*/
					if (offset > 0)
					{
						offCnt++;//3
					}

					/*bufPos 4*/
					/*calcPos 1*/
					int calcPos = bufPos - offCnt;

					/*偏移数量 offCnt,从下往上递减*/
					for (int i = calcPos; i <= bufPos; i++)
					{
						if (i == calcPos)
						{
							buffer[i] |= data >> (length - offset);
						}
						else if (i == bufPos)
						{
							buffer[i] |= (data & bitSet(8 - bitPos)) << bitPos;
						}
						else
						{
							if (i + 1 == bufPos)
							{
								buffer[i] |= data << (8 - bitPos);
							}
							else
							{
								buffer[i] |= data << (i * 8 - (8 * (i - 1)) + (8 - bitPos));
							}
						}
					}
				}
				else
				{
					/*未跨字节*/
					buffer[bufPos] |= (data & bitSet(length)) << bitPos;
				}
			}
			else if (m_matrixType == MatrixType::MT_MOTOROLA_MSB)
			{
				/*MSB需要倒着计算*/
				/*	bufPos 1			  */
				/*	start 9   1		20*/
				int offset = bitPos - length + 1;
				if (offset <= 0)
				{
					/*跨字节*/
					int offCnt = 0;
					offset = abs(offset);
					while ((offset -= 8) > 8)
					{
						offCnt++;
					}

					/*余数 offset*/
					if (offset > 0)
					{
						offCnt++;
					}

					//offCnt = 3
					//offset = 4

					int startPos = bitPos + 1;
					/*	2		4			2*/
					int endPos = offset - startPos;

					int calcPos = bufPos + offCnt;
					for (int i = bufPos + offCnt; i >= bufPos; i--)
					{
						if (i == calcPos)
						{
							buffer[i] |= ((data & bitSet(endPos)) << (8 - endPos));
						}
						else if (i == bufPos)
						{
							buffer[i] |= (data & bitSet(startPos));
						}
						else
						{

						}
					}
				}
				else
				{
					buffer[bufPos] |= (data & bitSet(length)) << offset;
				}
			}
			else
			{
				setLastError("无效的矩阵类型");
				break;
			}
		}
		catch (const std::out_of_range & e)
		{
			setLastError(e.what());
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool CanMatrix::unpack(const uchar* buffer, const int& start, const int& length, uchar& data)
{
	bool result = false;
	do
	{
		memset(&data, 0x00, sizeof(uchar));
		int bufPos = 0, bitPos = 0;
		if (!getCanMatrixPos(start, bufPos, bitPos))
		{
			break;
		}

		try
		{
			if (m_matrixType == MatrixType::MT_INTEL)
			{

			}
			else if (m_matrixType == MatrixType::MT_MOTOROLA_LSB)
			{
				/*	bufPos 4			  */
				/*	start 39   7		19*/
				int offset = (bitPos + length);
				if (offset > 8)
				{
					/*跨字节*/
					int offCnt = 0;

					while ((offset -= 8) > 8)
					{
						offCnt++;
					}

					/*余数 offset*/
					if (offset > 0)
					{
						offCnt++;
					}

					int calcPos = bufPos - offCnt;

					/*偏移数量 offCnt,从下往上递减*/
					for (int i = calcPos; i <= bufPos; i++)
					{

						if (i == calcPos)
						{
							data |= (buffer[i] << (length - offset)) & bitSet(length);
						}
						else if (i == bufPos)
						{
							data |= (buffer[i] >> bitPos)& bitSet(8 - bitPos);
						}
						else
						{
							if (i + 1 == bufPos)
							{
								data |= buffer[i] << (8 - bitPos);
							}
							else
							{
								data |= buffer[i] << (i * 8 - (8 * (i - 1)) + (8 - bitPos));
							}
						}
					}
				}
				else
				{
					/*未跨字节*/
					data |= (buffer[bufPos] >> bitPos)& bitSet(length);
				}
			}
			else if (m_matrixType == MatrixType::MT_MOTOROLA_MSB)
			{

			}
			else
			{
				setLastError("无效的矩阵类型");
				break;
			}
		}
		catch (const std::out_of_range & e)
		{
			setLastError(e.what());
			break;
		}
		result = true;
	} while (false);
	return result;
}

