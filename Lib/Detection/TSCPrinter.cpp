#include "TSCPrinter.h"
#include <Windows.h>

TSCPrinter::TSCPrinter()
{

}

TSCPrinter::~TSCPrinter()
{
	close();
	if (m_hModule)
	{
		FreeLibrary((HMODULE)m_hModule);
		m_hModule = NULL;
	}
}

bool TSCPrinter::init()
{
	bool bRet = false;
	do
	{
		m_hModule = LoadLibraryW(L"BCP.dll");
		if (!m_hModule)
		{
			break;
		}

		m_fpopenport = (lpopenport)GetProcAddress((HMODULE)m_hModule, "openport");
		if (!m_fpopenport)
		{
			break;
		}

		m_fpcloseport = (lpcloseport)GetProcAddress((HMODULE)m_hModule, "closeport");
		if (!m_fpcloseport)
		{
			break;
		}

		m_fpsendcommand = (lpsendcommand)GetProcAddress((HMODULE)m_hModule, "sendcommand");
		if (!m_fpsendcommand)
		{
			break;
		}

		m_fpsetup = (lpsetup)GetProcAddress((HMODULE)m_hModule, "setup");
		if (!m_fpsetup)
		{
			break;
		}

		m_fpdownloadpcx = (lpdownloadpcx)GetProcAddress((HMODULE)m_hModule, "downloadpcx");
		if (!m_fpdownloadpcx)
		{
			break;
		}

		m_fpbarcode = (lpbarcode)GetProcAddress((HMODULE)m_hModule, "barcode");
		if (!m_fpbarcode)
		{
			break;
		}

		m_fpprinterfont = (lpprinterfont)GetProcAddress((HMODULE)m_hModule, "printerfont");
		if (!m_fpprinterfont)
		{
			break;
		}

		m_fpclearbuffer = (lpclearbuffer)GetProcAddress((HMODULE)m_hModule, "clearbuffer");
		if (!m_fpclearbuffer)
		{
			break;
		}

		m_fpprintlabel = (lpprintlabel)GetProcAddress((HMODULE)m_hModule, "printlabel");
		if (!m_fpprintlabel)
		{
			break;
		}

		m_fpformfeed = (lpformfeed)GetProcAddress((HMODULE)m_hModule, "formfeed");
		if (!m_fpformfeed)
		{
			break;
		}

		m_fpnobackfeed = (lpnobackfeed)GetProcAddress((HMODULE)m_hModule, "nobackfeed");
		if (!m_fpnobackfeed)
		{
			break;
		}

		//m_fpisready = (lpisready)GetProcAddress((HMODULE)m_hModule, "isready");
		//if (!m_fpisready)
		//{
		//    break;
		//}

		m_fpwindowsfont = (lpwindowsfont)GetProcAddress((HMODULE)m_hModule, "windowsfont");
		if (!m_fpwindowsfont)
		{
			break;
		}

		//m_fpabout = (lpabout)GetProcAddress((HMODULE)m_hModule, "about");
		//if (!m_fpabout)
		//{
		//    break;
		//}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::open(char* szWidth, char* szHeight, char* szGap, char* szGapOffset,
	char* szCmdDirection, char* szCmdReference)
{
	bool bRet = false;
	do
	{
		if (!close())
		{
			break;
		}

		if (!m_fpopenport || !m_fpopenport("Bar Code Printer T-4503E"))//"TSC TTP-342 Pro"))
		{
			break;
		}

		// ldy, setup
		if (!m_fpsetup || !m_fpsetup(szWidth, szHeight, "1", "15", "0", szGap, szGapOffset))
		{
			break;
		}

		if (!m_fpclearbuffer || !m_fpclearbuffer())
		{
			break;
		}

		//         if (!m_fpformfeed || !m_fpformfeed())
		//         {
		//             break;
		//         }

		//         if (!m_fpnobackfeed || !m_fpnobackfeed())
		//         {
		//             break;
		//         }

		if (!sendCommand(szCmdDirection))
		{
			break;
		}

		if (!sendCommand(szCmdReference))
		{
			break;
		}

		m_opened = true;
		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::close()
{
	bool bRet = false;
	do
	{
		if (m_opened)
		{
			if (!m_fpcloseport || !m_fpcloseport())
			{
				break;
			}
		}

		m_opened = false;
		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::clearBuffer()
{
	bool bRet = false;
	do
	{
		if (!m_fpclearbuffer || !m_fpclearbuffer())
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::downloadPcx(char* pszPCXName)
{
	bool bRet = false;
	do
	{
		if (!m_fpdownloadpcx || !m_fpdownloadpcx(pszPCXName, pszPCXName))
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::sendCommand(char* pszCommand)
{
	bool bRet = false;
	do
	{
		if (!m_fpsendcommand || !m_fpsendcommand(pszCommand))
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::printLabel(char* pszSet, char* pszCopy)
{
	bool bRet = false;
	do
	{
		if (!m_fpprintlabel || !m_fpprintlabel(pszSet, pszCopy))
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::formFeed()
{
	bool bRet = false;
	do
	{
		if (!m_fpformfeed || !m_fpformfeed())
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::nobackFeed()
{
	bool bRet = false;
	do
	{
		if (!m_fpnobackfeed || !m_fpnobackfeed())
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::windowsFont(int ix, int iy, int iHeight, int iAngle,
	int iSharp, int iLine, char* szFontname, char* szCode)
{
	bool bRet = false;
	do
	{
		if (!m_fpwindowsfont || !m_fpwindowsfont(ix, iy, iHeight, iAngle, iSharp, iLine, szFontname, szCode))
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool TSCPrinter::barcode(char* x, char* y, char* codetype, char* height,
	char* bshowtext, char* angle, char* narrow, char* wide, char* code)
{
	bool bRet = false;
	do
	{
		if (!m_fpbarcode || !m_fpbarcode(x, y, codetype, height, bshowtext, angle, narrow, wide, code))
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}
