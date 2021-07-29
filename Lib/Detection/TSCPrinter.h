#pragma once

typedef int(_stdcall* lpopenport)(char*);

typedef int(_stdcall* lpcloseport)();

typedef int(_stdcall* lpsendcommand)(char*);

typedef int(_stdcall* lpsetup)(char*, char*, char*, char*, char*, char*, char*);

typedef int(_stdcall* lpdownloadpcx)(char* filename, char* image_name);

typedef int(_stdcall* lpbarcode)(char*, char*, char*, char*, char*, char*, char*, char*, char*);

typedef int(_stdcall* lpprinterfont)(char*, char*, char*, char*, char*, char*, char*);

typedef int(_stdcall* lpclearbuffer)();

typedef int(_stdcall* lpprintlabel)(char*, char*);

typedef int(_stdcall* lpformfeed)();

typedef int(_stdcall* lpnobackfeed)();

typedef int(_stdcall* lpwindowsfont)(int x, int y, int fontheight, int rotation, int fontstyle, int fontunderline, char* szFaceName, char* content);

class TSCPrinter
{
public:
	TSCPrinter();

	~TSCPrinter();

	bool init();

	bool open(char* szWidth = "63", char* szHeight = "38", char* szGap = "1.5", char* szGapOffset = "0",
		char* szCmdDirection = "DIRECTION 0,0",
		char* szCmdReference = "REFERENCE 0,0");

	bool close();

	bool clearBuffer();

	bool downloadPcx(char* pszPCXName);

	bool sendCommand(char* pszCommand);

	bool printLabel(char* pszSet, char* pszCopy);

	bool nobackFeed();

	bool formFeed();

	bool windowsFont(int ix, int iy, int iHeight, int iAngle,
		int iSharp, int iLine, char* szFontname, char* szCode);

	bool barcode(char* x, char* y, char* codetype, char* height,
		char* bshowtext, char* angle, char* narrow, char* wide, char* code);

private:
	void* m_hModule = nullptr;

	lpopenport m_fpopenport = nullptr;

	lpcloseport m_fpcloseport = nullptr;

	lpsendcommand m_fpsendcommand = nullptr;

	lpsetup m_fpsetup = nullptr;

	lpdownloadpcx m_fpdownloadpcx = nullptr;

	lpbarcode m_fpbarcode = nullptr;

	lpprinterfont m_fpprinterfont = nullptr;

	lpclearbuffer m_fpclearbuffer = nullptr;

	lpprintlabel m_fpprintlabel = nullptr;

	lpformfeed m_fpformfeed = nullptr;

	lpnobackfeed m_fpnobackfeed = nullptr;

	lpwindowsfont m_fpwindowsfont = nullptr;

	bool m_opened = false;
};
