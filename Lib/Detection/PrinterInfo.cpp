#include "PrinterInfo.h"

PrinterInfo::PrinterInfo()
{
}

PrinterInfo::PrinterInfo(const QString& file)
{
	setXmlFile(file);
}

void PrinterInfo::setXmlFile(const QString & fileName)
{
	m_fileName = fileName;
}

bool PrinterInfo::initLibrary()
{
	return m_printer.init();
}

bool PrinterInfo::openDevice()
{
	bool result = false;
	do 
	{
		if (!loadConfigFile(m_fileName.toStdString().c_str(), &m_stPS, &m_stPE))
		{
			setLastError("加载配置文件失败");
			break;
		}

		if (!m_printer.open(m_stPS.szLabelWidth, m_stPS.szLabelHeight,
			m_stPS.szGap, m_stPS.szGapOffset,
			m_stPS.szCmdDirection, m_stPS.szCmdReference))
		{
			setLastError("打开设备失败");
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool PrinterInfo::closeDevice()
{
	bool result = false;
	do 
	{
		if (!m_printer.close())
		{
			m_lastError = "关闭设备失败";
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool PrinterInfo::printLabel(const char* code)
{
	bool result = false;
	do 
	{	
		if (!m_printer.open(m_stPS.szLabelWidth, m_stPS.szLabelHeight,
			m_stPS.szGap, m_stPS.szGapOffset,
			m_stPS.szCmdDirection, m_stPS.szCmdReference))
		{
			m_lastError = "打开设备失败";
			break;
		}

		if (!putTxt(m_stPE.stTXT, code))
		{
			m_lastError = "写入文本失败";
			break;
		}

		if (!putPicture(m_stPE.stPic))
		{
			m_lastError = "写入图片失败";
			break;
		}

		//此处条形码
		if (!putQRcode(m_stPE.stQRcode, code))
		{
			m_lastError = "写入QR二维码失败";
			break;
		}

		if (!putDMatrix(m_stPE.stDMatrix, code))
		{
			m_lastError = "写入DM二维码失败";
			break;
		}

		if (!m_printer.printLabel(m_stPS.szPrintSet, m_stPS.szPrintCopy))
		{
			m_lastError = "打印标签失败";
			break;
		}

		m_printer.close();

		result = true;
	} while (false);
	return result;
}

const QString& PrinterInfo::getLastError()
{
	return m_lastError;
}

void PrinterInfo::setLastError(const QString& error)
{
	m_lastError = error;
}

bool PrinterInfo::codeConvert(char* szFromCharset, char* szToCharset, char* szInbuf, int iInSize, char* szOutbuf, int iOutSize)
{
	bool bRet = false;
	do
	{
		iconv_t cd = iconv_open(szToCharset, szFromCharset);
		if (0 == cd)
		{
			break;
		}

		memset(szOutbuf, 0, iOutSize);
		if (-1 == iconv(cd, (const char**)&szInbuf, (unsigned int*)&iInSize, &szOutbuf, (unsigned int*)&iOutSize))
		{
			break;
		}

		iconv_close(cd);
		bRet = true;
		break;
	} while (true);
	return bRet;
}

bool PrinterInfo::parseSetupNote(xmlNodePtr setupNote, PrinterSetup* pstPS)
{
	if (NULL == setupNote || NULL == pstPS)
	{
		return false;
	}

	xmlNodePtr curNode = setupNote->children;
	for (; curNode;)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST"Name"))
		{
			strcpy(pstPS->szName, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"LabelWidth"))
		{
			strcpy(pstPS->szLabelWidth, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"LabelHeight"))
		{
			strcpy(pstPS->szLabelHeight, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"LabelGap"))
		{
			strcpy(pstPS->szGap, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Direction"))
		{
			strcpy(pstPS->szCmdDirection, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Reference"))
		{
			strcpy(pstPS->szCmdReference, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Set"))
		{
			strcpy(pstPS->szPrintSet, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Copy"))
		{
			strcpy(pstPS->szPrintCopy, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Density"))
		{
			strcpy(pstPS->szDensity, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Speed"))
		{
			strcpy(pstPS->szSpeed, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Inductor"))
		{
			strcpy(pstPS->szInductorType, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"GapOffset"))
		{
			strcpy(pstPS->szGapOffset, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Offset"))
		{
			strcpy(pstPS->szCmdOffset, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Feed"))
		{
			strcpy(pstPS->szCmdFeed, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"BackFeed"))
		{
			strcpy(pstPS->szCmdBackFeed, (char*)xmlNodeGetContent(curNode));
		}
		curNode = curNode->next;
	}
	return true;
}

bool PrinterInfo::parseTextNote(xmlNodePtr textNote, TextInfo* pstText)
{
	TextInfo* pstTI = NULL;
	for (int i = 0; i < XML_MAX_COUNT; i++)
	{
		if (!pstText[i].bValid)
		{
			pstTI = &pstText[i];
			pstText[i].bValid = true;
			break;
		}
	}
	if (NULL == pstTI || NULL == pstText || NULL == textNote)
	{
		return false;
	}

	xmlNodePtr curNode = textNote->children;
	for (; curNode;)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST"X"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iX);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Y"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iY);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"H"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iHeight);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"A"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iAngle);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Shape"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iShape);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Underline"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstTI->iUnderline);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Font"))
		{
			//strcpy(pstTI->szFont, (char*)xmlNodeGetContent(curNode));
			codeConvert("utf-8", "gb2312", (char*)xmlNodeGetContent(curNode), strlen((char*)xmlNodeGetContent(curNode)), pstTI->szFont, 32);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Type"))
		{
			if (0 == xmlStrcmp(xmlNodeGetContent(curNode), BAD_CAST"A"))
			{
				pstTI->bAuto = true;
			}
			else
			{
				pstTI->bAuto = false;
			}
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Content"))
		{
			//strcpy(pstTI->szContent, (char*)xmlNodeGetContent(curNode));
			codeConvert("utf-8", "gb2312", (char*)xmlNodeGetContent(curNode), strlen((char*)xmlNodeGetContent(curNode)), pstTI->szContent, 128);
		}
		curNode = curNode->next;
	}
	return true;
}

bool PrinterInfo::parsePicNote(xmlNodePtr picNote, PictureInfo* pstPic)
{
	PictureInfo* pstPI = NULL;
	for (int i = 0; i < XML_MAX_COUNT; i++)
	{
		if (!pstPic[i].bValid)
		{
			pstPI = &pstPic[i];
			pstPic[i].bValid = true;
			break;
		}
	}
	if (NULL == pstPI || NULL == picNote || NULL == pstPic)
	{
		return false;
	}

	xmlNodePtr curNode = picNote->children;
	for (; curNode;)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST"X"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstPI->iX);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Y"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstPI->iY);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Path"))
		{
			strcpy(pstPI->szPath, (char*)xmlNodeGetContent(curNode));
		}
		curNode = curNode->next;
	}
	return true;
}

bool PrinterInfo::parseQRNote(xmlNodePtr qrNote, QRcodeInfo* pstQRcode)
{
	QRcodeInfo* pstQR = NULL;
	for (int i = 0; i < XML_MAX_COUNT; i++)
	{
		if (!pstQRcode[i].bValid)
		{
			pstQR = &pstQRcode[i];
			pstQRcode[i].bValid = true;
			break;
		}
	}
	if (NULL == pstQR || NULL == qrNote || NULL == pstQRcode)
	{
		return false;
	}

	xmlNodePtr curNode = qrNote->children;
	for (; curNode;)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST"X"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstQR->iX);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Y"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstQR->iY);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"ECC"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%c", &pstQR->cEcc);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Width"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstQR->iWidth);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Mode"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%c", &pstQR->cMode);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"A"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstQR->iAngle);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Version"))
		{
			strcpy(pstQR->szVersion, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Mask"))
		{
			strcpy(pstQR->szMask, (char*)xmlNodeGetContent(curNode));
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Type"))
		{
			if (0 == xmlStrcmp(xmlNodeGetContent(curNode), BAD_CAST"A"))
			{
				pstQR->bAuto = true;
			}
			else
			{
				pstQR->bAuto = false;
			}
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Content"))
		{
			strcpy(pstQR->szContent, (char*)xmlNodeGetContent(curNode));
		}
		curNode = curNode->next;
	}
	return true;
}

bool PrinterInfo::parseDMNote(xmlNodePtr dmNote, DataMatrix* pstDMatrix)
{
	DataMatrix* pstDM = NULL;
	for (int i = 0; i < XML_MAX_COUNT; i++)
	{
		if (!pstDMatrix[i].bValid)
		{
			pstDM = &pstDMatrix[i];
			pstDMatrix[i].bValid = true;
			break;
		}
	}
	if (NULL == pstDM || NULL == dmNote || NULL == pstDMatrix)
	{
		return false;
	}

	xmlNodePtr curNode = dmNote->children;
	for (; curNode;)
	{
		if (0 == xmlStrcmp(curNode->name, BAD_CAST"X"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iX);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Y"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iY);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Height"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iHeight);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Width"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iWidth);
		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST"Size"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iSize);
		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST"Row"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iRow);
		}
		else if (!xmlStrcmp(curNode->name, BAD_CAST"Column"))
		{
			sscanf((char*)xmlNodeGetContent(curNode), "%d", &pstDM->iColumn);
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Type"))
		{
			pstDM->bAuto = !xmlStrcmp(xmlNodeGetContent(curNode), BAD_CAST"A");
		}
		else if (0 == xmlStrcmp(curNode->name, BAD_CAST"Content"))
		{
			strcpy(pstDM->szContent, (char*)xmlNodeGetContent(curNode));
		}
		curNode = curNode->next;
	}
	return true;
}

bool PrinterInfo::loadConfigFile(const char* szPath, PrinterSetup* pstPS, PrintEvt* pstPE)
{
	bool bRet = false;
	do
	{
		xmlDocPtr xmlfile;
		xmlfile = xmlReadFile(szPath, "gb2312", XML_PARSE_RECOVER);
		if (NULL == xmlfile)
		{
			setLastError("加载配置文件失败");
			break;
		}
		xmlNodePtr rootNode;
		xmlNodePtr curNode;
		xmlNodePtr childNote;

		rootNode = xmlDocGetRootElement(xmlfile);
		if (xmlStrcmp(rootNode->name, BAD_CAST"PRINTER"))
		{
			xmlFreeDoc(xmlfile);
			break;
		}
		childNote = rootNode->children;
		for (; childNote;)
		{
			if (0 == xmlStrcmp(childNote->name, BAD_CAST"SETUP"))
			{
				if (!parseSetupNote(childNote, pstPS))
				{
					break;
				}
			}
			else if (0 == xmlStrcmp(childNote->name, BAD_CAST"PRINTEVT"))
			{
				xmlNodePtr evtNode;
				evtNode = childNote->children;
				for (; evtNode;)
				{
					if (0 == xmlStrcmp(evtNode->name, BAD_CAST"TEXT"))
					{
						if (!parseTextNote(evtNode, pstPE->stTXT))
						{
							break;
						}
					}
					else if (0 == xmlStrcmp(evtNode->name, BAD_CAST"PICTURE"))
					{
						if (!parsePicNote(evtNode, pstPE->stPic))
						{
							break;
						}
					}
					else if (0 == xmlStrcmp(evtNode->name, BAD_CAST"QRCODE"))
					{
						if (!parseQRNote(evtNode, pstPE->stQRcode))
						{
							break;
						}
					}
					else if (0 == xmlStrcmp(evtNode->name, BAD_CAST"DMATRIX"))
					{
						if (!parseDMNote(evtNode, pstPE->stDMatrix))
						{
							break;
						}
					}
					evtNode = evtNode->next;
				}
				if (evtNode != NULL)
				{
					break;
				}
			}
			childNote = childNote->next;
		}
		xmlFreeDoc(xmlfile);
		bRet = true;
	} while (false);
	return bRet;
}

bool PrinterInfo::putTxt(TextInfo* pstTxt, const char* szAutotxt)
{
	bool bRet = false;
	do
	{
		bool bSuccess = true;
		for (int i = 0; i < XML_MAX_COUNT; i++)
		{
			if (pstTxt[i].bValid)
			{
				if (pstTxt[i].bAuto)
				{	
					strcpy(pstTxt[i].szContent, szAutotxt);
				}

				if (!m_printer.windowsFont(pstTxt[i].iX, pstTxt[i].iY, pstTxt[i].iHeight, pstTxt[i].iAngle,
					pstTxt[i].iShape, pstTxt[i].iUnderline, pstTxt[i].szFont, pstTxt[i].szContent))
				{
					bSuccess = false;
					break;
				}
			}
		}

		if (!bSuccess)
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool PrinterInfo::putPicture(PictureInfo* pstPic)
{
	bool bRet = false;
	do
	{
		bool bSuccess = true;
		for (int i = 0; i < XML_MAX_COUNT; i++)
		{
			if (pstPic[i].bValid)
			{
				CvvImage image;
				if (!image.Load(pstPic[i].szPath, CV_LOAD_IMAGE_GRAYSCALE) || !image.Save(pstPic[i].szPath))
				{
					break;
				}
				image.Destroy();

				CxImage m_cxImage;

				wchar_t path[512] = { 0 };
				char_to_wchar(pstPic[i].szPath, path);
				if (!m_cxImage.Load(path/*, CXIMAGE_FORMAT_BMP*/))
				{
					bSuccess = false;
					//AfxMessageBox("载入效果图失败！");
					break;
				}

				if (!m_cxImage.Save(L"result.PCX", CXIMAGE_FORMAT_PCX))
				{
					bSuccess = false;
					//AfxMessageBox("保存PCX图失败！");
					break;
				}

				if (!m_printer.downloadPcx("result.PCX"))
				{
					bSuccess = false;
					//AfxMessageBox("downloadpcx error!\n");
					break;
				}

				char szCMD[256] = { 0 };
				sprintf(szCMD, "PUTPCX %d,%d,\"result.PCX\"", pstPic[i].iX, pstPic[i].iY);
				if (!m_printer.sendCommand(szCMD))
				{
					bSuccess = false;
					//AfxMessageBox("sendcommand:PUTPCX error!\n");
					break;
				}
			}
		}

		if (!bSuccess)
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

bool PrinterInfo::putQRcode(QRcodeInfo* pstQRcode, const char* szAutotxt)
{
	bool bRet = false;
	do
	{
		bool bSuccess = true;
		for (int i = 0; i < XML_MAX_COUNT; i++)
		{
			if (pstQRcode[i].bValid)
			{
				if (pstQRcode[i].bAuto)
				{
					strcpy(pstQRcode[i].szContent, szAutotxt);
				}
				char szCmd[512] = { 0 };
				sprintf(szCmd, "QRCODE %d,%d,%c,%d,%c,%d,\"%s\"",
					pstQRcode[i].iX,
					pstQRcode[i].iY,
					pstQRcode[i].cEcc,
					pstQRcode[i].iWidth,
					pstQRcode[i].cMode,
					pstQRcode[i].iAngle,
					pstQRcode[i].szContent);
				if (!m_printer.sendCommand(szCmd))
				{
					bSuccess = false;
					break;
				}
			}
		}
		if (!bSuccess)
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool PrinterInfo::putDMatrix(DataMatrix* pstDMatrix, const char* szAutotxt)
{
	bool bRet = false;
	do
	{
		bool bSuccess = true;
		for (int i = 0; i < XML_MAX_COUNT; i++)
		{
			if (pstDMatrix[i].bValid)
			{
				if (pstDMatrix[i].bAuto)
				{
					int len = strlen(pstDMatrix[i].szContent);
					if (pstDMatrix[i].szContent[len - 1] == ',')
						strcpy(&pstDMatrix[i].szContent[len - 1], szAutotxt);
					else
						strcpy(pstDMatrix[i].szContent, szAutotxt);
				}
				char szCmd[512] = { 0 };
				sprintf(szCmd, "DMATRIX %d,%d,%d,%d,x%d,%d,%d,\"%s\"",
					pstDMatrix[i].iX,
					pstDMatrix[i].iY,
					pstDMatrix[i].iWidth,
					pstDMatrix[i].iHeight,
					pstDMatrix[i].iSize,
					pstDMatrix[i].iRow,
					pstDMatrix[i].iColumn,
					pstDMatrix[i].szContent);
				if (!m_printer.sendCommand(szCmd))
				{
					bSuccess = false;
					break;
				}
			}
		}
		if (!bSuccess)
		{
			break;
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool PrinterInfo::char_to_wchar(const char* cptr, wchar_t* wcptr)
{
	int len = MultiByteToWideChar(CP_ACP, 0, cptr, -1, NULL, 0);
	wchar_t* buffer = new wchar_t[len * sizeof(wchar_t)];
	if (!buffer)
		return false;
	memset(buffer, 0, len * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, cptr, -1, buffer, len);
	wcscpy(wcptr, buffer);
	delete[] buffer;
	return true;
}
