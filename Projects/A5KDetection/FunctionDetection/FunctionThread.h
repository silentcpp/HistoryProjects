#pragma once
#include <Detection/Detection.h>
#pragma comment(lib,"Detection.lib")
#pragma execution_character_set("utf-8")

/*½ô¼±³ö»õ*/
#define URGENT_DELIVERY 0

/*¸´²â*/
#define REPEAT_TEST 1

enum TestSequence
{
	TS_PRE_TEST,
	TS_CHECK_SC,
	TS_CHECK_RS,
	TS_WRITE_SN,
	TS_CHECK_VER,
	TS_CHECK_VIDEO,
	TS_CHECK_UART2,
	TS_CHECK_SD_CARD,
	TS_CHECK_FRVIEW,
	TS_CHECK_DVR_FNC,
	TS_CHECK_DVR_PB,
	TS_FORMAT_SD,
	TS_CHECK_CUR,
	TS_CLEAR_DTC,
	TS_SAVE_LOG,
};

class FunctionThread : public Dt::Avm
{
	Q_OBJECT
public:
	inline FunctionThread(QObject* parent = nullptr) {}

	inline ~FunctionThread() {}

	bool writeSN();

	bool checkDVRFunction();

	bool checkDVRPlayback();

	bool formatSDCard();
protected:
	virtual void run() override;
};
