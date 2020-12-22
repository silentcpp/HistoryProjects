#include "ScanCodeDlg.h"
extern bool g_threadWait;
extern QString g_code;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	wchar_t windowName[256] = { 0 };
	GetWindowTextW(hwnd, windowName, 255);
	if (!wcsncmp(windowName, L"数采客户端.for.RT", wcslen(L"数采客户端.for.RT")))
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

bool ScanCodeDlg::eventFilter(QObject* obj, QEvent* event)
{
	/*通过事件过滤器,屏蔽ESC键,来连接对话框退出*/
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

	if (event->type() == QEvent::KeyPress)
	{
		if (reinterpret_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			//this->close();
			//QMessageBox::information(this, "友情提示", "好好工作,不要调皮");
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

bool ScanCodeDlg::judgeCode(const QString& code)
{
	bool result = false;
	do
	{
#if QT_NO_DEBUG
		if (!m_deviceConfig.codeLength.toInt() && m_deviceConfig.codeJudge == "NULL")
		{
			result = true;
			break;
		}

		if (code.length() != m_deviceConfig.codeLength.toInt() 
			|| code.mid(0, m_deviceConfig.codeJudge.length()) != m_deviceConfig.codeJudge)
		{
			break;
		}
#endif
		result = true;
	} while (false);
	return result;
}

bool ScanCodeDlg::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	MSG* msg = (MSG*)message;
	if (msg->message == WM_COPYDATA)
	{
		COPYDATASTRUCT* cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
		if (cds->dwData == QR_OK)
		{
			g_code = ui.codeLine->text();
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
	,m_deviceConfig(JsonTool::getInstance()->getParsedDeviceConfig())
{
	this->ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setWindowTitle("TvsA56ScanCode.INVO.R&D");
	installEventFilter(this); 
	m_minimize.setParent(ui.titleLabel);
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
	connect(ui.codeLine, &QLineEdit::returnPressed, this, &ScanCodeDlg::returnPressedSlot);
}

ScanCodeDlg::~ScanCodeDlg()
{
}

void ScanCodeDlg::setLineEditText(const QString& text)
{
	ui.codeLine->setText(text);
}

void ScanCodeDlg::returnPressedSlot()
{
	ui.titleLabel->setText("请扫条码");
#ifdef QT_DEBUG
	g_code = ui.codeLine->text();
	this->hide();
	g_threadWait = false;
	return;
#endif
	if (!judgeCode(ui.codeLine->text()))
	{
		ui.titleLabel->setText("条码格式错误");
		goto clear;
	}
	
	if (!sendCode(ui.codeLine->text()))
	{
		ui.titleLabel->setText("发送到采集端失败,请开启采集软件");
		goto clear;
	}
clear:
	ui.codeLine->clear();
}