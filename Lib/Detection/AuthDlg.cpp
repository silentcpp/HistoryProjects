#include "AuthDlg.h"

AuthDlg::AuthDlg(QDialog* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 20, 20);
	this->setMask(bmp);

	ui.password->setEchoMode(QLineEdit::EchoMode::Password);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.affirm, &QPushButton::clicked, this, &AuthDlg::affrimSlot);
	connect(ui.exit, &QPushButton::clicked, this, &AuthDlg::exitSlot);
}

AuthDlg::~AuthDlg()
{
}

bool AuthDlg::isAuth()
{
	if (JsonTool::getInstance()->getUserPrivileges())
		return true;
	return m_isAuth;
}

void AuthDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void AuthDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void AuthDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

int AuthDlg::exec()
{
	ui.userName->setText(JsonTool::getInstance()->getUserConfigValue("用户名"));
	return QDialog::exec();
}

void AuthDlg::affrimSlot()
{
	/*配置文件数据*/
	const QString&& userName = JsonTool::getInstance()->getUserConfigValue("用户名").toUpper();
	const QString&& password = JsonTool::getInstance()->getUserConfigValue("密码").toUpper();

	/*UI控件数据*/
	const QString&& uiUserName = ui.userName->text().toUpper();
	const QString&& uiPassword = ui.password->text().toUpper();

	/*防止有些人乱改,保留一个超级用户*/
	const QString superUser = "ROOT";
	const QString superPassword = "SILENCE";

	bool userRet = ((uiUserName == userName) || (uiUserName == superUser));
	bool passwordRet = ((uiPassword == password) || (uiPassword == superPassword));

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
