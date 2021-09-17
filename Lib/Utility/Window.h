#pragma once
#pragma execution_character_set("utf-8")

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QPalette>
#include <QStyleFactory>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>

#include "QMessageBoxEx.hpp"

/*
* @RUN_MAIN_WINDOW,运行主窗口
* @param1,主窗口
* @return,int
*/
#define RUN_MAIN_WINDOW(MAIN_WIN)\
int main(int argc,char* argv[])\
{\
QApplication a(argc,argv);\
MAIN_WIN* WIN = NO_THROW_NEW MAIN_WIN;\
if (!WIN)\
	return -1;\
WIN->show();\
return a.exec();\
}

/*
* @OVERRIDE_MOUSE_EVENT,重写鼠标事件
*/
#define OVERRIDE_MOUSE_EVENT \
\
bool m_mousePress = false;\
\
QPoint m_mousePoint;\
\
virtual void mousePressEvent(QMouseEvent * event)\
{\
	if (event->button() == Qt::LeftButton)\
	{\
		m_mousePress = true;\
		m_mousePoint = event->globalPos();\
	}\
}\
\
virtual void mouseReleaseEvent(QMouseEvent * event)\
{\
	if (m_mousePress)\
		m_mousePress = false;\
}\
\
virtual void mouseMoveEvent(QMouseEvent * event)\
{\
	if (m_mousePress)\
	{\
		int x = event->globalX() - m_mousePoint.x();\
		int y = event->globalY() - m_mousePoint.y();\
		m_mousePoint = event->globalPos();\
		move(this->x() + x, this->y() + y);\
	}\
}

namespace Utility {
	/*
	* @WindowFactory,窗口工厂
	*/
	class Window {
	public:
		/*
		* @getThemeList,获取主题列表
		* @return,const QStringList
		*/
		static const QStringList getThemeList();

		/*
		* @setTheme,设置主题
		* @param1,主题名称
		* @return,void
		*/
		static void setTheme(const QString& theme = QString("Fusion"));

		/*
		* @setBorderRadius,设置边框为圆角
		* @param1,需要设置的部件
		* @param2,半径大小
		* @return,void
		*/
		static void setBorderRadius(QWidget* widget,const QSize& add = {}, qreal radius = 20);

		/*
		* @resizeWindow,调整窗口大小
		* @param1,部件类
		* @param2,缩放比例
		* @param3,加或减窗口大小,true add,false sub
		* @param4,加或减多少大小
		* @return,void
		*/
		static void resize(QWidget* widget, float scale, bool addOrSub = false, float size = 0.0f);

		/*
		* @getScreenSize,获取屏幕大小
		* @param1,第几个屏幕
		* @return,QRect
		*/
		static QRect getScreenSize(int screent = -1);
	};
}
