#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include "JsonTool.h"
#include "QMessageBoxEx.h"
#include "GeneratedFiles/ui_AuthDlg.h"

class AuthDlg : public QDialog
{
	Q_OBJECT

public:
	AuthDlg(QDialog* parent = Q_NULLPTR);

	~AuthDlg();

	bool isAuth();

protected:
	/*重写虚方法实现移动*/
	bool m_isPress = false;

	QPoint m_point;

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);

private:
	Ui::AuthDlg ui;

	bool m_isAuth = false;
public slots:
	virtual int exec();

	void affrimSlot();

	void exitSlot();

};
