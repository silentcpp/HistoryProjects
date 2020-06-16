#include "UnlockDlg.h"

UnlockDlg::UnlockDlg(QDialog*parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	ui.setupUi(this);
	connect(ui.passwordEdit, &QLineEdit::returnPressed,this,&UnlockDlg::returnPressedSlot);
	QBitmap bmp(this->size());
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), 20, 20);
	this->setMask(bmp);
}

UnlockDlg::~UnlockDlg()
{
}

void UnlockDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void UnlockDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void UnlockDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

void UnlockDlg::returnPressedSlot()
{
	if (ui.passwordEdit->text() != JsonTool::getInstance()->getUserConfigValue("密码"))
	{
		QMessageBox::warning(this, "提示", "输入密码错误,请重新输入");
	}
	else
	{
		this->close();
	}
	ui.passwordEdit->clear();
}