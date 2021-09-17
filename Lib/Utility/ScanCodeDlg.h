#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <functional>

#include "Window.h"


#ifdef QT_DEBUG
#include "Debug/uic/ui_ScanCodeDlg.h"
#else
#include "Release/uic/ui_ScanCodeDlg.h"
#endif

enum WorkstationType
{
	WT_HARDWARE_TEST,   
	WT_AGING_TEST,      
	WT_VERIFY_TEST, 
};

enum QueryResult
{
	QR_OK,
	QR_NG,
	QR_PRE_NG,     
	QR_PRE_NONE,   
	QR_CUR_NG,     
	QR_CUR_OK, 
};

class ScanCodeDlg : public QDialog
{
	Q_OBJECT
public:
	ScanCodeDlg(QWidget* parent = Q_NULLPTR);

	~ScanCodeDlg();

	void setWindowName(const QString& name);

	void setTitle(const QString& title);

	void setInputEcho(const QString& title);

	void setErrorEcho(const QString& error);

	const QStringList& getCodeList();

	QString getCode() const;

	void clearCodeList();

	void setInputFormat(const QString& format, int length);

	int exec();

	int exec(int times);

	void setInputRightProc(const std::function<bool(const QString& code)>& proc);

	void maskEscExit(bool on);

	void setRemoveRepeat(bool on);
protected:

	OVERRIDE_MOUSE_EVENT;

	virtual bool eventFilter(QObject* obj, QEvent* event);

	bool inputRight(const QString& code);
	
	void initMinimizeIcon();
private slots:
	void returnPressedSlot();
private:
	Ui::ScanCodeDlg ui;

	QLabel m_minIcon;

	QStringList m_codeList;

	QString m_inputEcho = "请扫第%d个条码";

	QString m_errorEcho = "格式错误,请重新扫描";

	QString m_inputFormat;

	QString m_windowName = "TvsA56ScanCode.INVO.R&D";

	int m_inputLength = 0;

	std::function<bool(const QString&)> m_proc = nullptr;

	bool m_maskEscExit = true;

	bool m_removeRepeat = true;
};
