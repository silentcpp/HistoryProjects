#pragma once
#pragma execution_character_set("utf-8")
//#pragma warning(disable:4819)
#include <Windows.h>
#include <QDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include "JsonTool.h"
#include "ui_ScanCodeDlg.h"

typedef enum WorkstationType
{
	WT_HARDWARE_TEST,   //硬件测试
	WT_AGING_TEST,      //老化测试
	WT_VERIFY_TEST,     //功能确认
}workstationType_t;

typedef enum QueryResult
{
	QR_OK,
	QR_NG,
	QR_PRE_NG,     //上站NG
	QR_PRE_NONE,   //上站未做
	QR_CUR_NG,     //本站已做过且NG
	QR_CUR_OK,     //本站已做过且OK
}queryResult_t;

class ScanCodeDlg : public QDialog
{
	Q_OBJECT
private:
	Ui::ScanCodeDlg ui;
	int m_channel = -1;
	QString m_lastError = "No Error";
	QLabel m_minimize;
protected:
	/*重写虚方法实现移动*/
	bool m_isPress = false;
	QPoint m_point;
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	/*判断条码*/
	bool judgeCode(const QString& code);
	bool eventFilter(QObject* obj, QEvent* event);
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
	bool sendCode(const QString& code);
	void setLastError(const QString& err);
public:
	ScanCodeDlg(QWidget* parent = Q_NULLPTR);
	~ScanCodeDlg();
	void setChannel(const int& channel);
	const QString& getLastError();
private slots:
	void returnPressedSlot();
};
