#pragma once

#include <QMessageBox>

namespace Utility {

	class QMessageBoxEx : public QMessageBox
	{
		Q_OBJECT
	private:
		inline static StandardButton newMessageBox(Icon icon, const QString& title, const QString& text, StandardButtons buttons, QWidget* parent)
		{
			QMessageBox msgBox(icon, title, text, buttons, parent);
			msgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowSystemMenuHint);
			return static_cast<StandardButton>(msgBox.exec());
		}

		inline QMessageBoxEx(QWidget* parent = nullptr) {};

		inline ~QMessageBoxEx() {}
	public:

		inline static StandardButton information(QWidget* parent, const QString& title, const QString& text, bool onTop = true)
		{
			return onTop ? newMessageBox(QMessageBox::Information, title, text, Ok, parent) : QMessageBox::information(parent, title, text);
		}

		inline static StandardButton warning(QWidget* parent, const QString& title, const QString& text, bool onTop = true)
		{
			return onTop ? newMessageBox(QMessageBox::Warning, title, text, Ok, parent) : QMessageBox::warning(parent, title, text);
		}

		inline static StandardButton question(QWidget* parent, const QString& title, const QString& text, bool onTop = true)
		{
			return onTop ? newMessageBox(QMessageBox::Question, title, text, Yes | No, parent) : QMessageBox::question(parent, title, text);
		}

		inline static StandardButton critical(QWidget* parent, const QString& title, const QString& text, bool onTop = true)
		{
			return onTop ? newMessageBox(QMessageBox::Critical, title, text, Ok, parent) : QMessageBox::critical(parent, title, text);
		}
	};
}
