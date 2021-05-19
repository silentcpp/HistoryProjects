#pragma once

#include <QDialog>
#include <QMouseEvent>
#include "GeneratedFiles/ui_UpdateDlg.h"

#include <ClientCore/DLLExport.h>
#pragma comment(lib,"ClientCore.lib")

class UpdateDlg : public QDialog
{
	Q_OBJECT

public:
	UpdateDlg(QWidget* args, QWidget* parent = Q_NULLPTR);

	~UpdateDlg();
protected:
	static bool notifyCallback(bool val, const char* name, void* args);

	static void progressCallback(ulong current, ulong total, ulong status, void* args);

	static void resultCallback(bool result, const char* name, void* args);

	bool setQuestionBox(const QString& title, const QString& text);

	/*重写虚方法实现移动*/
	bool m_isPress = false;

	QPoint m_point;

	virtual void mousePressEvent(QMouseEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent* event);

	virtual void mouseMoveEvent(QMouseEvent* event);
signals:
	void setQuestionBoxSignal(const QString& title, const QString& text, bool* result);

	void setProgressSignal(ulong, ulong, ulong);

	void setShowDlgSignal(bool);

	void setTitleSignal(const QString& title);

	void restartSignal(const QString& name);
public slots:
	void setQuestionBoxSlot(const QString& title, const QString& text, bool* result);

	void setProgressSlot(ulong, ulong, ulong);

	void setShowDlgSlot(bool show);

	void setTitleSlot(const QString& title);
private:
	Ui::UpdateDlg ui;
	
	bool m_wait = false;

	QWidget* m_parent = nullptr;

	void* m_client = nullptr;
};
