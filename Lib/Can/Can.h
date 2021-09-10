#pragma once
#pragma execution_character_set("utf-8")

#include "CanFactory.h"
#include "CanSender.h"

namespace Can {

	/*
	* @getVersion,获取版本
	* @return,const char*
	*/
	const char* getVersion();

	/*
	* @getSupportCan,获取支持的CAN卡
	* @return,QStringList
	*/
	QStringList getSupportCan();

	/*
	* @allocCanTransfer,分配CAN传输
	* @param1,CAN卡名称
	* @return,CanTransfer*
	*/
	CanTransfer* allocCanTransfer(const QString& cardName);

	/*
	* @freeCanTransfer,释放CAN传输
	* @param1,已分配的CanTransfer
	* @notice,如果param1,填写nullptr,将释放所有分配的CanTransfer
	* @return,void
	*/
	void freeCanTransfer(CanTransfer* transfer = nullptr);

	/*
	* @getSupportMaxCanTransferCount,获取支持的最大CAN传输数量
	* @return,int
	*/
	int getSupportMaxCanTransferCount();

	/*
	* @getCurrentUsedCanTransferCount,获取当前已使用的CAN传输数量
	* @return,const int
	*/
	int getCurrentUsedCanTransferCount();

	/*
	* @getCanTransferValue,获取CAN传输
	* @param1,索引,范围0~(MAX_CAN_TRANSFER_COUNT-1)
	* @return,CanTransfer*,成功返回已分配的地址,失败nullptr
	*/
	CanTransfer* getCanTransferValue(int index);

	/*
	* @getCanTransferIndex,获取CAN传输索引
	* @param1,已分配的CanTransfer
	* @return,const int,成功返回已分配的地址的索引,失败-1
	*/
	int getCanTransferIndex(const CanTransfer* transfer);

	/*
	* @alloclCanSender,分配CAN发送者
	* @param1,CAN传输
	* @return,CanSender*
	*/
	CanSender* allocCanSender(CanTransfer* transfer);

	/*
	* @freeCanSender,释放CAN发送者
	* @param1,CAN发送者
	* @return,void
	*/
	void freeCanSender(CanSender*& sender);
}

