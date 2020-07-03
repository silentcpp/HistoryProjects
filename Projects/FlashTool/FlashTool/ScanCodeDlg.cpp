#include "ScanCodeDlg.h"

extern bool g_threadWait;
extern QStringList g_codeList;
QStringList g_repeatCodeList;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	wchar_t windowName[256] = { 0 };
	memset(windowName, 0x00, sizeof(windowName));
	GetWindowTextW(hwnd, windowName, sizeof(windowName));
	if (!wcsncmp(windowName, L"高清摄像头自动线采集端", wcslen(L"高清摄像头自动线采集端")))
	{
		(*(HWND*)lParam) = hwnd;
	}
	return TRUE;
}

bool ScanCodeDlg::sendCode(const QString& code)
{
	bool result = false;
	do
	{
		HWND hWnd = NULL;
		EnumWindows(EnumWindowsProc, (LPARAM)&hWnd);
		if (!hWnd)
		{
			setLastError("发送到采集端失败,请开启采集软件");
			break;
		}
		COPYDATASTRUCT cds;
		memset(&cds, 0x00, sizeof(cds));
		cds.dwData = WT_VERIFY_TEST;
		cds.cbData = code.length() + 1;
		QByteArray byteArray = code.toLatin1();
		char* byte = byteArray.data();
		cds.lpData = byte;
		HWND sender = (HWND)effectiveWinId();
		::SendMessage(hWnd, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&cds));
		result = true;
	} while (false);
	return result;
}

void ScanCodeDlg::setLastError(const QString& err)
{
#ifdef QT_DEBUG
	qDebug() << err << endl;
#endif
	m_lastError = err;
}

void ScanCodeDlg::setChannel(const int& channel)
{
	m_channel = channel;
	ui.titleLabel->setText(QString("请扫通道%1条码").arg(m_channel));
}

const QString& ScanCodeDlg::getLastError()
{
	return m_lastError;
}

void ScanCodeDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void ScanCodeDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void ScanCodeDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

bool ScanCodeDlg::judgeCode(const QString& code)
{
	bool result = false;
	do
	{
		int codeLength = JsonTool::getInstance()->getParsedFileConfig()->codeLength;
		QString codeRule = JsonTool::getInstance()->getParsedFileConfig()->codeRule;
		int codeRepeat = JsonTool::getInstance()->getParsedDeviceConfig()->codeRepeat.toInt();
		bool succes = true;
		if (codeRepeat)
		{
			g_repeatCodeList.push_back(code);

			for (int i = 0; i < g_repeatCodeList.count();i++)
			{
				for (int j = i + 1; j < g_repeatCodeList.count(); j++)
				{
					if (g_repeatCodeList.value(i) == g_repeatCodeList.value(j))
					{
						succes = false;
						g_repeatCodeList.pop_back();
						break;
					}
				}
				if (!succes)
				{
					break;
				}
			}
		}

		if (!succes)
		{
			setLastError(QString("通道%1条码重复").arg(m_channel));
			break;
		}

		if (!code.length() && codeRule == "NULL")
		{
			result = true;
			break;
		}

		if (code.length() != codeLength || code.mid(0, codeRule.length()) != codeRule)
		{
			setLastError(QString("通道%1条码格式错误").arg(m_channel));
			break;
		}
		result = true;
	} while (false);
	return result;
}

bool ScanCodeDlg::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == &m_minimize)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton)
			{
				this->showMinimized();
				return true;
			}
		}
	}

	/*通过事件过滤器,屏蔽ESC键,来连接对话框退出*/
	if (event->type() == QEvent::KeyPress)
	{
		if (reinterpret_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			//this->close();
			QMessageBox::information(this, "友情提示", "好好工作,不要调皮");
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

bool ScanCodeDlg::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* msg = (MSG*)message;
	if (msg->message == WM_COPYDATA)
	{
		COPYDATASTRUCT* cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
		if (cds->dwData == QR_OK)
		{
			g_codeList.push_back(ui.codeLine->text());
			this->hide();
			g_threadWait = false;
		}
		else
		{
			if (cds->dwData == QR_CUR_NG)
			{
				ui.titleLabel->setText("功能测试NG!");
			}
			else if (cds->dwData == QR_CUR_OK)
			{
				ui.titleLabel->setText("功能测试OK,请不要重复做!");
			}
			else if (cds->dwData == QR_PRE_NG)
			{
				ui.titleLabel->setText("上站NG!");
			}
			else if (cds->dwData == QR_PRE_NONE)
			{
				ui.titleLabel->setText("上站未做!");
			}
			else if (cds->dwData == QR_NG)
			{
				ui.titleLabel->setText("NG,已废弃的故障码!");
			}
			else
			{
				ui.titleLabel->setText("NG,未知的原因");
			}
		}
		return true;
	}
	return QWidget::nativeEvent(eventType, message, result);
}

ScanCodeDlg::ScanCodeDlg(QWidget* parent)
	: QDialog(parent)
{
	this->ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setWindowTitle("HDCameraAUTO.INVO.SC");
	installEventFilter(this);
	ui.titleLabel->setStyleSheet(ui.titleLabel->styleSheet() + ";color:black;");
	connect(ui.codeLine, &QLineEdit::returnPressed, this, &ScanCodeDlg::returnPressedSlot);

	m_minimize.setParent(this);
	m_minimize.setText("-");
	QFont font;
	font.setBold(true);
	font.setPixelSize(20);
	m_minimize.setFont(font);
	m_minimize.setAlignment(Qt::AlignCenter);
	m_minimize.setFixedSize(QSize(25, 25));
	m_minimize.setStyleSheet("color:rgb(0,0,0);background-color:transparent;");
	m_minimize.move(this->size().width() - m_minimize.size().width(), 0);
	m_minimize.installEventFilter(this);
}

ScanCodeDlg::~ScanCodeDlg()
{

}

void ScanCodeDlg::returnPressedSlot()
{
	if (!judgeCode(ui.codeLine->text()))
	{
		ui.titleLabel->setText(m_lastError);
		goto clear;
	}
	
#ifdef QT_DEBUG
	g_codeList.push_back(ui.codeLine->text());
	this->hide();
	g_threadWait = false;
#else
	if (!sendCode(ui.codeLine->text()))
	{
		if (!g_repeatCodeList.isEmpty())
		{
			g_repeatCodeList.pop_back();
		}
		ui.titleLabel->setText(m_lastError);
		goto clear;
	}
#endif
clear:
	ui.codeLine->clear();
}
