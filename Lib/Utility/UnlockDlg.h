#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>

#include "Window.h"

#ifdef QT_DEBUG
#include "Debug/uic/ui_UnlockDlg.h"
#else
#include "Release/uic/ui_UnlockDlg.h"
#endif

namespace Utility {

	class UnlockDlg : public QDialog
	{
		Q_OBJECT
	public:
		explicit UnlockDlg(QDialog* parent = nullptr);

		UnlockDlg(const QString& password, QDialog* parent = nullptr);

		~UnlockDlg();

		static void setInfo(const QString& password);

		static void getInfo(QString& password);

		static bool isAuth();
	protected:
		OVERRIDE_MOUSE_EVENT;

		void initInstance();

	public slots:
		void returnPressedSlot();

	private:
		Ui::UnlockDlg ui;

		static QString m_password;

		static bool m_isAuth;
	};
}
