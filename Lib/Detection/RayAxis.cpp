#include "RayAxis.h"
#include <string.h>
#define GREEN_LINE_X      960//320
#define GREEN_LINE_Y      540//234
/*#define LX    (stGray_Buffer->width/2 - stAxis_Standard->x/2 - SELECT_BOX_WIDTH -1)
#define RX    (stGray_Buffer->width/2 + stAxis_Standard->x/2 - SELECT_BOX_WIDTH -1)
#define Y     (stGray_Buffer->height/2 - SELECT_BOX_HEIGHT - 1)

#define X     (stGray_Buffer->width/2 - SELECT_BOX_HEIGHT -1)
#define AY    (stGray_Buffer->height/2 - stAxis_Standard->y/2 - SELECT_BOX_WIDTH -1)
#define UY    (stGray_Buffer->height/2 + stAxis_Standard->y/2 - SELECT_BOX_WIDTH -1)*/

#define SELECT_BOX_UD_WIDTH        (stAxis_Standard->width / 2)
#define SELECT_BOX_UD_HEIGHT       (stAxis_Standard->height / 2)

#define SELECT_BOX_LR_WIDTH        (stAxis_Standard->height / 2)
#define SELECT_BOX_LR_HEIGHT       (stAxis_Standard->width / 2)

/* Start Position */
#define LX    (GREEN_LINE_X - stAxis_Standard->x/2 - SELECT_BOX_LR_WIDTH -1)
#define RX    (GREEN_LINE_X + stAxis_Standard->x/2 - SELECT_BOX_LR_WIDTH -1)
#define Y     (GREEN_LINE_Y - SELECT_BOX_LR_HEIGHT - 1)

#define X     (GREEN_LINE_X - SELECT_BOX_UD_WIDTH -1)
#define UY    (GREEN_LINE_Y - stAxis_Standard->y/2 - SELECT_BOX_UD_HEIGHT -1)
#define DY    (GREEN_LINE_Y + stAxis_Standard->y/2 - SELECT_BOX_UD_HEIGHT -1)

static unsigned int _CalculateMean(unsigned int* input, unsigned int length,
	unsigned int StartY, unsigned int EndY,
	unsigned int StartX, unsigned int EndX)
{
	unsigned int i;
	unsigned int uiSub = 0;
	if (length == 0)
	{
		uiSub = 1;      /* no black point */
	}
	else if (length > (EndY - StartY)* (EndX - StartX) / 10 * 9)
	{
		uiSub = 2;      /* no white point */
	}

	else
	{
		for (i = 0; i < length; i++)
		{
			uiSub += input[i];
		}
		if (length != 0)
			uiSub = (float)uiSub / length + 0.5;
	}
	return uiSub;
}

static unsigned int _CalculatePositionY(const grayBuffer_t* Buffer, unsigned char ucThreshold,
	unsigned int StartY, unsigned int EndY,
	unsigned int StartX, unsigned int EndX)
{
	unsigned int* result = (unsigned int*)malloc(((EndY - StartY) * (EndX - StartX)) * sizeof(unsigned int));
	unsigned int i, j, z = 0, uiMean = 0;
	unsigned char* pucTemp = 0;

	unsigned char* pMybuffer = (unsigned char*)malloc((EndY - StartY) * (EndX - StartX));
	for (i = 0; i < EndY - StartY; i++) {
		memcpy(pMybuffer + i * (EndX - StartX), Buffer->buffer + (StartY + i) * Buffer->width + StartX, EndX - StartX);
	}

	//     for(j = 0; j < EndY - StartY; j++)
	//     {
	//         for(i = 0; i < EndX - StartX; i++)
	//         {
	//             if(pMybuffer[j * (EndX - StartX) + i] <= ucThreshold){
	//                 pMybuffer[j * (EndX - StartX) + i] = 0;
	//             }
	//             else{
	//                 pMybuffer[j * (EndX - StartX) + i] = 255;
	//             }
	//         }
	//     }
	// 
	//      IplImage* pImage = cvCreateImageHeader(cvSize(EndX - StartX, EndY - StartY), 8, 1);
	//      pImage->imageData = (char*)pMybuffer;
	//      cvSaveImage("y.bmp", pImage);
	//      cvReleaseImageHeader(&pImage);

	for (j = 0; j < EndY - StartY; j++)
	{
		for (i = 0; i < EndX - StartX; i++)
		{
			if (pMybuffer[j * (EndX - StartX) + i] <= ucThreshold) {
				result[z] = j;
				z++;
			}
		}
	}
	uiMean = _CalculateMean(result, z, StartY, EndY, StartX, EndX);
	uiMean += StartY;
	free(result);
	free(pMybuffer);
	return uiMean;
}

static unsigned int _CalculatePositionX(const grayBuffer_t* Buffer, unsigned char ucThreshold,
	unsigned int StartY, unsigned int EndY,
	unsigned int StartX, unsigned int EndX)
{
	unsigned int* result = (unsigned int*)malloc(((EndY - StartY) * (EndX - StartX)) * sizeof(unsigned int));
	unsigned int i, j, z = 0, uiMean = 0;
	unsigned char* pucTemp = 0;

	unsigned char* pMybuffer = (unsigned char*)malloc((EndY - StartY) * (EndX - StartX));
	for (i = 0; i < EndY - StartY; i++) {
		memcpy(pMybuffer + i * (EndX - StartX), Buffer->buffer + (StartY + i) * Buffer->width + StartX, EndX - StartX);
	}

	//     for(j = 0; j < EndY - StartY; j++)
	//     {
	//         for(i = 0; i < EndX - StartX; i++)
	//         {
	//             if(pMybuffer[j * (EndX - StartX) + i] <= ucThreshold){
	//                 pMybuffer[j * (EndX - StartX) + i] = 0;
	//             }
	//             else{
	//                 pMybuffer[j * (EndX - StartX) + i] = 255;
	//             }
	//         }
	//     }
	// 
	//      IplImage* pImage = cvCreateImageHeader(cvSize(EndX - StartX, EndY - StartY), 8, 1);
	//      pImage->imageData = (char*)pMybuffer;
	//      cvSaveImage("x.bmp", pImage);
	//      cvReleaseImageHeader(&pImage);

	for (j = 0; j < EndY - StartY; j++)
	{
		for (i = 0; i < EndX - StartX; i++)
		{
			if (pMybuffer[j * (EndX - StartX) + i] <= ucThreshold) {
				result[z] = i;
				z++;
			}
		}
	}
	uiMean = _CalculateMean(result, z, StartY, EndY, StartX, EndX);
	uiMean += StartX;
	free(result);
	free(pMybuffer);
	return uiMean;
}


static cross_t _GetCrossPoint(pointPosition_t P1, pointPosition_t P2, pointPosition_t P3, pointPosition_t P4)
{
	cross_t result1;
	result1.iResult = 0;

	float a1, a2, b1, b2;
	if (0 == (P2.x - P1.x))
	{
		if (0 == (P4.x - P3.x)) {
			result1.iResult = -1;
			return result1;
		}
		a2 = ((float)P4.y - (float)P3.y) / ((float)P4.x - (float)P3.x);
		b2 = (float)P3.y - a2 * (float)P3.x;

		result1.x = P2.x;
		result1.y = a2 * result1.x + b2;
		result1.angle = 0;
	}
	else
	{
		if ((0 == (P2.x - P1.x)) || (0 == (P4.x - P3.x))) {
			result1.iResult = -2;
			return result1;
		}
		a1 = ((float)P2.y - (float)P1.y) / ((float)P2.x - (float)P1.x);
		b1 = (float)P1.y - a1 * (float)P1.x;

		a2 = ((float)P4.y - (float)P3.y) / ((float)P4.x - (float)P3.x);
		b2 = (float)P3.y - a2 * (float)P3.x;

		if (0 == (a1 - a2)) {
			result1.iResult = -3;
			return result1;
		}
		result1.x = (b2 - b1) / (a1 - a2);
		result1.y = a1 * result1.x + b1;
		result1.angle = atan(a2) * 180 / PI;
	}
	return result1;
}

cross_t calculateCross(const grayBuffer_t* ptGray_Buffer, threshold_t* stThreshold, axisStandard_t* stAxis_Standard)
{
	pointPosition_t L, R, U, D;
	cross_t CalculatePoint;

	//     IplImage * pImage = cvCreateImageHeader(cvSize(640,480), 8, 1);
	//     pImage->imageData = (char*)ptGray_Buffer->buffer;
	//     cvSaveImage("3.bmp", pImage);
	//     cvReleaseImageHeader(&pImage);

	memset(&CalculatePoint, 0x00, sizeof(cross_t));

	L.y = _CalculatePositionY(ptGray_Buffer, stThreshold->xAxis, Y, Y + SELECT_BOX_LR_HEIGHT * 2, LX, LX + SELECT_BOX_LR_WIDTH * 2);
	if (L.y <= 2) {
		CalculatePoint.iResult = -1;
		return CalculatePoint;
	}
	L.x = LX + SELECT_BOX_LR_WIDTH;

	R.y = _CalculatePositionY(ptGray_Buffer, stThreshold->xAxis, Y, Y + SELECT_BOX_LR_HEIGHT * 2, RX, RX + SELECT_BOX_LR_WIDTH * 2);
	if (R.y <= 2) {
		CalculatePoint.iResult = -2;
		return CalculatePoint;
	}
	R.x = RX + SELECT_BOX_LR_WIDTH;

	U.x = _CalculatePositionX(ptGray_Buffer, stThreshold->yAxis, UY, UY + SELECT_BOX_UD_HEIGHT * 2, X, X + SELECT_BOX_UD_WIDTH * 2);
	if (U.x <= 2) {
		CalculatePoint.iResult = -4;
		return CalculatePoint;
	}
	U.y = UY + SELECT_BOX_UD_HEIGHT;

	D.x = _CalculatePositionX(ptGray_Buffer, stThreshold->yAxis, DY, DY + SELECT_BOX_UD_HEIGHT * 2, X, X + SELECT_BOX_UD_WIDTH * 2);
	if (D.x <= 2) {
		CalculatePoint.iResult = -3;
		return CalculatePoint;
	}
	D.y = DY + SELECT_BOX_UD_HEIGHT;

	CalculatePoint = _GetCrossPoint(U, D, L, R);
	if (CalculatePoint.iResult < 0)
	{
		CalculatePoint.iResult = -5;
		return CalculatePoint;
	}

	return CalculatePoint;
}


