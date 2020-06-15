#ifndef CANMATRIX_H
#define CANMATRIX_H
#include <string>
#include <bitset>
#include <stdexcept>
#include <iostream>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

enum class MatrixType {
	INTEL_MATRIX,
	MOTOROLA_LSB_MATRIX,
	MOTOROLA_MSB_MATRIX
};

class CanMatrix
{
private:
	MatrixType m_matrixType;

	std::string m_lastError = "No Error";

	static const uchar m_canMatrix[8][8];
protected:
	void setLastError(const std::string& err);
public:
	CanMatrix(const MatrixType& matrixType = MatrixType::MOTOROLA_MSB_MATRIX);

	~CanMatrix();

	/*起始位置,BUFFER下标,BIT位置*/
	bool getCanMatrixPos(const int& startPos, int& bufferPos, int& bitPos);

	/*最高支持64bit*/
	const ulong bitSet(const int& length);

	const std::string& getLastError();

	void setMatrixType(const MatrixType& matrixType);

	bool pack(uchar* buffer, const int& start, const int& length, const int& data);

	bool unpack(const uchar* buffer, const int& start, const int& length, uchar& data);
};

#endif
