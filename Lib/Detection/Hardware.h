#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "MainDlg.h"

/************************************************************************/
/* 硬件                                                                 */
/************************************************************************/

namespace Hwd {
	//广汽
	class GAC : public Dt::Hardware {
		Q_OBJECT
	public:
		explicit GAC(QObject* parent = nullptr) {};

		~GAC() {};

		bool writeSn();

		bool writeOldSn();

		bool writeDate();
	protected:
		virtual void run() = 0;
	private:
	};

	//北汽
	class BAIC : public Dt::Hardware {
		Q_OBJECT
	public:
		explicit BAIC(QObject* parent = nullptr) {};

		~BAIC() {};
	protected:
		virtual void run() = 0;
	private:

	};

	//车和家
	class CHJAutoMotive : public Dt::Hardware {
		Q_OBJECT
	public:
		explicit CHJAutoMotive(QObject* parent = nullptr) {};

		~CHJAutoMotive() {};
	protected:
		virtual void run() = 0;
	private:
	};

	//五菱
	class SGMW :public Dt::Hardware {
		Q_OBJECT
	public:
		explicit SGMW(QObject* parent = nullptr) {};

		~SGMW() {}

		bool writeSn();

		bool writeDate();
	protected:
		virtual void run() = 0;
	private:
	};
}
