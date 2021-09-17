#include "Window.h"

using namespace Utility;

const QStringList Window::getThemeList()
{
	return QStyleFactory::keys();
}

void Window::setTheme(const QString& theme)
{
	qApp->setStyle(QStyleFactory::create(theme));
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(53, 53, 53));
	palette.setColor(QPalette::WindowText, Qt::white);
	palette.setColor(QPalette::Base, QColor(15, 15, 15));
	palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, Qt::white);
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::Button, QColor(53, 53, 53));
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::BrightText, Qt::red);
	palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
	palette.setColor(QPalette::HighlightedText, Qt::black);
	qApp->setPalette(palette);
}

void Window::setBorderRadius(QWidget* widget, const QSize& add, qreal radius)
{
	QBitmap bmp(widget->size() + add);
	bmp.fill();
	QPainter p(&bmp);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::black);
	p.drawRoundedRect(bmp.rect(), radius, radius);
	widget->setMask(bmp);
}

void Window::resize(QWidget* widget, float scale, bool addOrSub, float size)
{
	if (!widget || scale <= 0.00000000001)
		return;

	auto width = QApplication::desktop()->screenGeometry().width() / scale;
	auto height = QApplication::desktop()->screenGeometry().height() / scale;

	if (addOrSub)
		widget->resize(width + size, height + size);
	else
		widget->resize(width - size, height - size);
	return;
}

QRect Utility::Window::getScreenSize(int screen)
{
	return QApplication::desktop()->screen(screen)->rect();
}
