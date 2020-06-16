#include <Detection/MainDlg.h>
#include <QtWidgets/QApplication>
#include "FunctionThread.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	NEW_MAIN_DLG(FunctionThread);
	return app.exec();
}
