#include "ChoiceDlg.h"

bool ChoiceDlg::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_exit)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton)
			{
				this->close();
				return true;
			}
		}
	}
	else if (event->type() == QEvent::KeyPress)
	{
		if (reinterpret_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			this->close();
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

void ChoiceDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPress = true;
		m_point = event->globalPos();
	}
}

void ChoiceDlg::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		m_isPress = false;
	}
}

void ChoiceDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPress)
	{
		int x = event->globalX() - m_point.x();
		int y = event->globalY() - m_point.y();
		m_point = event->globalPos();
		move(this->x() + x, this->y() + y);
	}
}

ChoiceDlg::ChoiceDlg(QWidget* parent)
	: QDialog(parent)
{
	this->ui.setupUi(this);
	installEventFilter(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowTitle("ChoiceDlg");
	ui.title->setStyleSheet(ui.title->styleSheet() + ";color:black;");
	initExitLabel();
	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &ChoiceDlg::returnPressedSlot);
	connect(ui.lineEdit, &QLineEdit::textChanged, this, &ChoiceDlg::textChangedSlot);

#ifdef QT_DEBUG
	this->ui.lineEdit->setText(SUPER_PASSWORD);
#endif
}

ChoiceDlg::~ChoiceDlg()
{
	if (m_exit)
	{
		delete m_exit;
		m_exit = nullptr;
	}
}

void ChoiceDlg::initExitLabel()
{
	m_exit = new(std::nothrow) QLabel(this);
	if (m_exit)
	{
		m_exit->setText("X");
		QFont font;
		font.setBold(true);
		font.setPixelSize(15);
		m_exit->setFont(font);
		m_exit->setAlignment(Qt::AlignCenter);
		m_exit->setFixedSize(QSize(20, 20));
		m_exit->setStyleSheet("color:rgb(0,0,0)");
		m_exit->move(this->size().width() - m_exit->size().width(), 0);
		m_exit->installEventFilter(this);
	}
}

void ChoiceDlg::typeNameCorrect(const QString& typeName)
{
	emit typeNameCorrectSignal(typeName);
}

void ChoiceDlg::textChangedSlot(const QString& text)
{
	if (text.mid(0, 5) == "i am ")
	{
		ui.title->setText("正在进行认证操作,已加密输入");
		ui.title->setStyleSheet(ui.title->styleSheet() + ";color:red;");
		ui.lineEdit->setEchoMode(QLineEdit::Password);
	}
	else
	{
		ui.title->setText("请扫描选择机种");
		ui.title->setStyleSheet(ui.title->styleSheet() + ";color:black;");
		ui.lineEdit->setEchoMode(QLineEdit::Normal);
	}
}

void ChoiceDlg::returnPressedSlot()
{
	do 
	{
		if (JsonTool::getInstance()->getParsedFileConfig(ui.lineEdit->text()))
		{
			typeNameCorrect(ui.lineEdit->text());
			this->done(0xFF);
		}
		else
		{
			QMessageBox::warning(this, "警告", JsonTool::getInstance()->getLastError());
		}
		ui.lineEdit->clear();
	} while (false);
	return;
}