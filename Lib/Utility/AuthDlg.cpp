#include "AuthDlg.h"

using namespace Utility;

const QString* AuthDlg::m_userName = nullptr;

const QString* AuthDlg::m_password = nullptr;

bool AuthDlg::m_isAuth = false;

AuthDlg::AuthDlg(QDialog* parent)
	: QDialog(parent)
{
	initInstance();

	if (!m_userName || !m_password)
	{
		m_userName = &m_defaultUserName;
		m_password = &m_defaultPassword;
	}
}

AuthDlg::AuthDlg(const QString* userName, const QString* password, QDialog* parent)
{
	initInstance();
	setInfo(userName, password);
}

AuthDlg::~AuthDlg()
{
}

void Utility::AuthDlg::setInfo(const QString* userName, const QString* password)
{
	m_userName = userName;

	m_password = password;
}

void Utility::AuthDlg::getInfo(QString& userName, QString& password)
{
	userName = *m_userName;

	password = *m_password;
}

bool AuthDlg::isAuth()
{
	return m_isAuth;
}

void AuthDlg::initInstance()
{
	ui.setupUi(this);

	Utility::Window::setBorderRadius(this);

	ui.password->setEchoMode(QLineEdit::EchoMode::Password);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint 
		| Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.affirm, &QPushButton::clicked, this, &AuthDlg::affrimSlot);

	connect(ui.exit, &QPushButton::clicked, this, &AuthDlg::exitSlot);
}

int AuthDlg::exec()
{
	ui.userName->setText(*m_userName);
	ui.password->setFocus();
	return QDialog::exec();
}

void AuthDlg::affrimSlot()
{
	/*UI控件数据*/
	const QString&& uiUserName = ui.userName->text();
	const QString&& uiPassword = ui.password->text();

	/*防止有些人乱改,保留一个超级用户*/
	const QString superUser = "ROOT";
	const QString superPassword = "SILENCE";

	bool userRet = ((uiUserName == *m_userName) || (uiUserName == superUser));
	bool passwordRet = ((uiPassword == *m_password) || (uiPassword == superPassword));

	if (!(userRet && passwordRet))
	{
		QMessageBoxEx::information(this, "提示", "认证失败");
	}
	(m_isAuth = userRet && passwordRet) ? accept() : ui.password->clear();
}

void AuthDlg::exitSlot()
{
	reject();
	this->close();
}
