#pragma once

#include <QObject>
#include <QThread>

class UpdateApp : public QThread
{
	Q_OBJECT
public:
	UpdateApp(QObject* parent = nullptr);

	~UpdateApp();
protected:
	virtual void run();
};
