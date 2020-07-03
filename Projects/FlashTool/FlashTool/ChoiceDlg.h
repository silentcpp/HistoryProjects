#pragma once

#include <QDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include "ui_ChoiceDlg.h"
#include "JsonTool.h"

class ChoiceDlg : public QDialog
{
	Q_OBJECT
private:
	Ui::ChoiceDlg ui;
	QLabel* m_exit = nullptr;
protected:
	/*重写虚方法实现移动*/
	bool m_isPress = false;
	QPoint m_point;
	virtual bool eventFilter(QObject* obj, QEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
public:
	ChoiceDlg(QWidget* parent = Q_NULLPTR);
	~ChoiceDlg();
	void initExitLabel();
	void typeNameCorrect(const QString& typeName);
signals:
	void typeNameCorrectSignal(const QString& typeName);
public slots:
	void returnPressedSlot();

	void textChangedSlot(const QString& text);
};
