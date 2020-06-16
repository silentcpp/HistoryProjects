#ifndef __AXIS__H
#define __AXIS__H

#include <stdio.h>
#include <math.h>
#include <malloc.h>

//#define SELECT_BOX_WIDTH    20/2
//#define SELECT_BOX_HEIGHT    100/2
#define PI  3.14159265358979323846

typedef struct Cross
{
	int iResult;
	float x;
	float y;
	double angle;
}cross_t;

typedef struct GrayBuffer
{
	unsigned char* buffer;
	unsigned int width;
	unsigned int height;
}grayBuffer_t;

typedef struct AxisStandard
{
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
}axisStandard_t;

typedef struct PointPosition
{
	unsigned int x;
	unsigned int y;
}pointPosition_t;

typedef struct Threshold
{
	unsigned int xAxis;
	unsigned int yAxis;
}threshold_t;

extern cross_t calculateCross(const grayBuffer_t* stGray_Buffer, threshold_t* stThreshold, axisStandard_t* stAxis_Standard);

#endif//__AXIS__H

