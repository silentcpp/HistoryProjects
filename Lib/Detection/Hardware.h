#pragma once

//兼容旧的MsgNode结构体
//如果在你的项目中报错,未定义_MsgNode.xxxx
//需要在你的项目中#define USE_NEW_MSG_NODE
#ifndef USE_NEW_MSG_NODE
#define USE_NEW_MSG_NODE
#endif //!USE_NEW_MSG_NODE

#include "MainDlg.h"
#include "Detection.h"

/************************************************************************/
/* 硬件                                                                 */
/************************************************************************/

namespace Hwd {
	//广汽
	class GAC : public Dt::Hardware {
		Q_OBJECT
	public:
		GAC(QObject* parent = nullptr) {};

		~GAC() {};

		bool writeSn();
	protected:
		virtual void run() = 0;
	private:
	};

	//北汽
	class BAIC : public Dt::Hardware {
		Q_OBJECT
	public:
		BAIC(QObject* parent = nullptr) {};

		~BAIC() {};
	protected:
		virtual void run() = 0;
	private:

	};

	//车和家
	class CHJAutoMotive : public Dt::Hardware {
		Q_OBJECT
	public:
		CHJAutoMotive(QObject* parent = nullptr) {};

		~CHJAutoMotive() {};
	protected:
		virtual void run() = 0;
	private:
	};
}
