#pragma once
#pragma execution_character_set("utf-8")

#include <QString>

#include "../DetectionExt/Lib/XML/include/libxml/parser.h"
#include "../DetectionExt/Lib/XML/include/libxml/tree.h"

#pragma comment(lib, "../DetectionExt/Lib/XML/lib/libxml2.lib")
#pragma comment(lib, "../DetectionExt/Lib/XML/lib/zlib.lib")
#pragma comment(lib, "../DetectionExt/Lib/XML/lib/iconv.lib")

#include <CxImage/CxImage.h>
#pragma comment(lib,"CxImageW.lib")

#include <CvvImage/CvvImage.h>
#pragma comment(lib, "CvvImage.lib")

#include "TSCPrinter.h"

#define XML_MAX_COUNT 100

struct PrinterSetup
{
	char szName[64];

	char szLabelWidth[64];

	char szLabelHeight[64];

	char szGap[64];

	char szGapOffset[64];

	char szSpeed[64];

	char szDensity[64];

	char szInductorType[64];

	char szCmdDirection[64];

	char szCmdReference[64];

	char szPrintSet[64];

	char szPrintCopy[64];

	char szCmdOffset[64];

	char szCmdFeed[64];

	char szCmdBackFeed[64];
};

struct TextInfo
{
	bool bValid;

	int iX;

	int iY;

	int iHeight;

	int iAngle;

	int iShape;

	int iUnderline;

	char szFont[32];

	bool bAuto;

	char szContent[128];
};

struct PictureInfo
{
	bool bValid;

	int iX;

	int iY;

	char szPath[256];
};

struct QRcodeInfo
{
	bool bValid;

	int iX;

	int iY;

	char cEcc;

	int iWidth;

	char cMode;

	int iAngle;

	char szVersion[8];

	char szMask[8];

	bool bAuto;

	char szContent[128];
};

struct DataMatrix
{
	bool bValid;

	int iX;

	int iY;

	int iHeight;

	int iWidth;

	int iSize;

	int iRow;

	int iColumn;

	bool bAuto;

	char szContent[128];
};

struct BoxInfo
{
	bool bValid;
};

struct BarcodeInfo
{
	bool bValid;
};

struct PrintEvt
{
	TextInfo stTXT[XML_MAX_COUNT];

	PictureInfo stPic[XML_MAX_COUNT];

	QRcodeInfo stQRcode[XML_MAX_COUNT];

	BarcodeInfo stBarcode[XML_MAX_COUNT];

	BoxInfo stBox[XML_MAX_COUNT];

	DataMatrix stDMatrix[XML_MAX_COUNT];
};

class PrinterInfo
{
public:
	PrinterInfo();

	explicit PrinterInfo(const QString& file);

	~PrinterInfo() {}

	void setXmlFile(const QString& file);

	bool initLibrary();

	bool openDevice();

	bool closeDevice();

	bool printLabel(const char* code);

	const QString& getLastError();
protected:

	void setLastError(const QString& error);

	bool codeConvert(char* szFromCharset, char* szToCharset, char* szInbuf,
		int iInSize, char* szOutbuf, int iOutSize);

	bool parseSetupNote(xmlNodePtr setupNote, PrinterSetup* pstPS);

	bool parseTextNote(xmlNodePtr textNote, TextInfo* pstText);

	bool parsePicNote(xmlNodePtr picNote, PictureInfo* pstPic);

	bool parseQRNote(xmlNodePtr qrNote, QRcodeInfo* pstQRcode);

	bool parseDMNote(xmlNodePtr dmNote, DataMatrix* pstDMatrix);

	bool loadConfigFile(const char* szPath,PrinterSetup* pstPS, PrintEvt* pstPE);

protected:

	bool putTxt(TextInfo* pstTxt, const char* szAutotxt);

	bool putPicture(PictureInfo* pstPic);

	bool putQRcode(QRcodeInfo* pstQRcode,const char* szAutotxt);

	bool putDMatrix(DataMatrix* pstDMatrix,const char* szAutotxt);

	bool char_to_wchar(const char* cptr, wchar_t* wcptr);

private:
	QString m_fileName = ".\\Config\\Other\\Printer.xml";

	TSCPrinter m_printer;

	QString m_lastError = "No Error";

	PrinterSetup m_stPS = { 0 };

	PrintEvt m_stPE = { 0 };
};

