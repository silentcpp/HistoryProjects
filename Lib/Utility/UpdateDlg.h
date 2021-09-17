#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QProcess>

#include "Window.h"

#ifdef QT_DEBUG
#include "Debug/uic/ui_UpdateDlg.h"
#else
#include "Release/uic/ui_UpdateDlg.h"
#endif

namespace Utility {

	extern QString getCurrentFileName();

	extern const QString& getAppVersion();

	extern QString getCurrentDir();

	/*
	* @UpdateDlg
	*/
	class UpdateDlg : public QDialog
	{
		Q_OBJECT
	public:
		UpdateDlg(QWidget* parent, const QString& updateLog = QString());

		~UpdateDlg();

		void autoRelease();
	protected:

		OVERRIDE_MOUSE_EVENT;

		static bool notifyCallback(bool val, const char* name, void* args);

		static void progressCallback(ulong current, ulong total, ulong status, void* args);

		static void resultCallback(bool result, const char* name, void* args);

		bool setQuestionBox(const QString& title, const QString& text);

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

		QString m_updateLog;
	};
}
