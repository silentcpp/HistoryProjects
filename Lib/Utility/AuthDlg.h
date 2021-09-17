#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>

#include "Window.h"

#ifdef QT_DEBUG
#include "Debug/uic/ui_AuthDlg.h"
#else
#include "Release/uic/ui_AuthDlg.h"
#endif

namespace Utility {

	class AuthDlg : public QDialog
	{
		Q_OBJECT
	public:
		explicit AuthDlg(QDialog* parent = nullptr);

		explicit AuthDlg(const QString* userName, const QString* password, QDialog* parent = nullptr);

		~AuthDlg();

		static void setInfo(const QString* userName, const QString* password);

		static void getInfo(QString& userName, QString& password);

		static bool isAuth();

	public slots:
		virtual int exec();

		void affrimSlot();

		void exitSlot();
	protected:
		OVERRIDE_MOUSE_EVENT;

		void initInstance();
	private:
		Ui::AuthDlg ui;

		static bool m_isAuth;

		static const QString* m_userName;

		static const QString* m_password;

		QString m_defaultUserName = "TEST";

		QString m_defaultPassword = "1.";
	};
}
