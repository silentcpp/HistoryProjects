#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>

class BaseDevice
{
public:
	BaseDevice();

	virtual ~BaseDevice();

	BaseDevice(const BaseDevice&) = delete;

	BaseDevice& operator=(const BaseDevice&) = delete;

	/*
	* @open,打开
	* @param1,端口
	* @param2,比特率
	* @param3,超时
	* @return,bool
	*/
	virtual	bool open(int port, int bitrate = 400, int timeout = 150) = 0;

	/*
	* @close,关闭
	* @return,bool
	*/
	virtual bool close() = 0;

	/*
	* @readData,读取数据
	* @param1,读取数据的缓存区
	* @param2,读取数据的大小
	* @param3,从地址
	* @return,int
	*/
	virtual int readData(uchar* data, ushort size, ushort slave) = 0;

	/*
	* @writeData,写入数据
	* @param1,写入数据的缓存区
	* @param2,写入数据的大小
	* @param3,从地址
	* @return,int
	*/
	virtual int writeData(const uchar* data, ushort size, ushort slave) = 0;

	/*
	* @isOpened,是否打开
	* @return,bool
	*/
	bool isOpened() const;

	/*
	* @getPort,获取端口
	* @return,int
	*/
	int getPort() const;

	/*
	* @getLastError,获取最终错误
	* @return,const QString&
	*/
	const QString& getLastError();

protected:
	/*
	* @setLastError,设置最终错误
	* @param1,错误信息
	* @return,void
	*/
	void setLastError(const QString& error);
protected:
	bool m_open = false;

	int m_port = -1;

private:
	QString m_lastError = "No Error";
};

