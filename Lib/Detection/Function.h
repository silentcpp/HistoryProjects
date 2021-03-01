#pragma once

//兼容旧的MsgNode结构体
//如果在你的项目中报错,未定义_MsgNode.xxxx
//需要在你的项目中#define USE_NEW_MSG_NODE
#ifndef USE_NEW_MSG_NODE
#define USE_NEW_MSG_NODE
#endif //!USE_NEW_MSG_NODE

#include "MainDlg.h"

/************************************************************************/
/* 功能                                                                 */
/************************************************************************/

namespace Fnc {
	//广汽
	class GAC : public Dt::Avm {
		Q_OBJECT
	public:
		explicit GAC(QObject* parent = nullptr) {};

		~GAC() {};

		/*兼容旧程序*/
		bool writeSn();

		bool checkSn();

		bool checkOldSn();

		bool writeSet(const uchar& value);
	protected:
		virtual void run() = 0;
	private:
		bool generateSn(uchar* data, int* const size = nullptr);
	};

	//北汽
	class BAIC : public Dt::Dvr {
		Q_OBJECT
	public:
		explicit BAIC(QObject* parent = nullptr);

		~BAIC();

		bool setOtherAction();

		bool checkSn();

		bool checkRecord();

	protected:
		virtual void run() = 0;
	private:

	};

	//车和家
	class CHJAutoMotive : public Dt::Dvr {
		Q_OBJECT
	public:
		explicit CHJAutoMotive(QObject* parent = nullptr);

		~CHJAutoMotive();

		bool setOtherAction();

		bool checkSn();

		bool checkMaxCurrent();

		bool checkRecord(const ulong& timeout = 10000U);

		bool writeDate();

		static void getCurrentThread(void* args);
	protected:
		virtual void run() = 0;

		bool getWifiInfo(bool rawData = false, bool showLog = true);
	private:
		bool m_startThread = false;

		bool m_startGetCur = false;

		QVector<float> m_vector;
	};
}
