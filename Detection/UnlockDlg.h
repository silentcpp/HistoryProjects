#pragma once
#pragma execution_character_set("utf-8")
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include "JsonTool.h"
#include "GeneratedFiles/ui_UnlockDlg.h"

class UnlockDlg : public QDialog
{
	Q_OBJECT
private:
	Ui::UnlockDlg ui;

	JsonTool* m_jsonTool = nullptr;
public:
	UnlockDlg(QDialog*parent = Q_NULLPTR);

	~UnlockDlg();
protected:
	/*重写虚方法实现移动*/
	bool m_isPress = false;
	
	QPoint m_point;
	
	virtual void mousePressEvent(QMouseEvent* event);
	
	virtual void mouseReleaseEvent(QMouseEvent* event);
	
	virtual void mouseMoveEvent(QMouseEvent* event);
private slots:
	void returnPressedSlot();
};
