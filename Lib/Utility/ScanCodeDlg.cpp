#include "ScanCodeDlg.h"
#include <Windows.h>

ScanCodeDlg::ScanCodeDlg(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setWindowTitle("TvsA56ScanCode.INVO.R&D");
	installEventFilter(this);
	initMinimizeIcon();
	connect(ui.codeLine, &QLineEdit::returnPressed, this, &ScanCodeDlg::returnPressedSlot);
}

ScanCodeDlg::~ScanCodeDlg()
{
}

void ScanCodeDlg::setWindowName(const QString& name)
{
	m_windowName = name;
}

void ScanCodeDlg::setTitle(const QString& title)
{
	ui.titleLabel->setText(title);
}

void ScanCodeDlg::setInputEcho(const QString& title)
{
	m_inputEcho = title;
}

void ScanCodeDlg::setErrorEcho(const QString& error)
{
	m_errorEcho = error;
}

const QStringList& ScanCodeDlg::getCodeList()
{
	return m_codeList;
}

QString ScanCodeDlg::getCode() const
{
	return m_codeList.at(0);
}

void ScanCodeDlg::clearCodeList()
{
	m_codeList.clear();
}

void ScanCodeDlg::setInputFormat(const QString& format, int length)
{
	m_proc = nullptr;
	m_inputFormat = format;
	m_inputLength = length;
}

int ScanCodeDlg::exec()
{
	m_codeList.clear();
	return QDialog::exec();
}

int ScanCodeDlg::exec(int times)
{
	m_codeList.clear();
	int result = QDialog::Accepted;
	for (int i = 0; i < times; i++)
	{
		ui.titleLabel->setText(QString().sprintf(m_inputEcho.toStdString().c_str(), i + 1));
		if (QDialog::exec() == QDialog::Rejected)
		{
			result = QDialog::Rejected;
			break;
		}
	}
	return result;
}

void ScanCodeDlg::setInputRightProc(const std::function<bool(const QString& code)>& proc)
{
	m_proc = proc;
}

void ScanCodeDlg::maskEscExit(bool on)
{
	m_maskEscExit = on;
}

void ScanCodeDlg::setRemoveRepeat(bool on)
{
	m_removeRepeat = on;
}

void ScanCodeDlg::returnPressedSlot()
{
	QString text = ui.codeLine->text();
	if (m_proc)
	{
		if (!m_proc(text))
		{
			ui.titleLabel->setText(m_errorEcho);
			goto clear;
		}
	}
	else
	{
		if (!inputRight(text))
		{
			ui.titleLabel->setText(m_errorEcho);
			goto clear;
		}
	}

	if (m_removeRepeat && m_codeList.contains(text))
	{
		ui.titleLabel->setText("条码重复,请重新扫描");
		goto clear;
	}
	m_codeList.append(text);
	this->accept();
clear:
	ui.codeLine->clear();
}

void ScanCodeDlg::initMinimizeIcon()
{
	m_minIcon.setParent(ui.titleLabel);
	m_minIcon.setText("-");
	QFont font;
	font.setBold(true);
	font.setPixelSize(20);
	m_minIcon.setFont(font);
	m_minIcon.setAlignment(Qt::AlignCenter);
	m_minIcon.setFixedSize(QSize(25, 25));
	m_minIcon.setStyleSheet("color:rgb(0,0,0);background-color:transparent;");
	m_minIcon.move(this->size().width() - m_minIcon.size().width(), 0);
	m_minIcon.installEventFilter(this);
}

bool ScanCodeDlg::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == &m_minIcon)
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

	if (m_maskEscExit && event->type() == QEvent::KeyPress)
	{
		if (reinterpret_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

bool ScanCodeDlg::inputRight(const QString& code)
{
	bool result = false;
	do
	{
		if (m_inputFormat.isEmpty() || m_inputLength == 0)
		{
			result = true;
			break;
		}

		if (code.length() != m_inputLength ||
			code.mid(0, m_inputFormat.length()) != m_inputFormat)
		{
			break;
		}
		result = true;
	} while (false);
	return result;
}
