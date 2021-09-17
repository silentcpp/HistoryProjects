#include "UnlockDlg.h"

using namespace Utility;

QString UnlockDlg::m_password = "1.";

bool UnlockDlg::m_isAuth = false;

UnlockDlg::UnlockDlg(QDialog*parent)
	: QDialog(parent)
{
	initInstance();
}

UnlockDlg::UnlockDlg(const QString& password, QDialog* parent)
{
	setInfo(password);

	initInstance();
}

UnlockDlg::~UnlockDlg()
{
}

void UnlockDlg::setInfo(const QString& password)
{
	m_password = password;
}

void Utility::UnlockDlg::getInfo(QString& password)
{
	password = m_password;
}

bool Utility::UnlockDlg::isAuth()
{
	return m_isAuth;
}

void UnlockDlg::initInstance()
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	connect(ui.passwordEdit, &QLineEdit::returnPressed,this,&UnlockDlg::returnPressedSlot);
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 20, 20);
	this->setMask(bmp);
}

void UnlockDlg::returnPressedSlot()
{
	if (ui.passwordEdit->text() != m_password)
	{
		QMessageBoxEx::warning(this, "提示", "输入密码错误,请重新输入");
	}
	else
	{
		m_isAuth = true;
		this->close();
	}
	ui.passwordEdit->clear();
}