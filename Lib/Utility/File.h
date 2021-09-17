#pragma once
#pragma execution_character_set("utf-8")

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

namespace Utility {

	extern void setLastError(const QString& error);

	extern const QString& getLastError();

	extern bool compareList(const QStringList& cmp1, const QStringList& cmp2);

	extern bool removeList(const QStringList& list1, QStringList& list2);

	extern QStringList getFileListBySuffixName(const QString& path, const QStringList& suffix);

	namespace File
	{
		/*
		* @setEncoding,设置编码
		* @param1,[gb2312,utf-8...]
		* @return,void
		*/
		void setEncoding(const char* encoding);

		/*
		* @readFile,读取文件[重载1]
		* @param1,文件名
		* @param2,数据缓存
		* @param2,数据大小
		* @return,bool
		*/
		bool read(const QString& name, char*& data, int& size);

		/*
		* @readFile,读取文件[重载2]
		* @param1,文件名
		* @param2,字节数组
		* @return,bool
		*/
		bool read(const QString& name, QByteArray& bytes);

		/*
		* @readFile,读取文件[重载3]
		* @param1,文件名
		* @param2,文本列表
		* @return,bool
		*/
		bool read(const QString& name, QStringList& textList);

		/*
		* @readFile,读取文件[重载4]
		* @param1,文件名
		* @param2,数据
		* @return,bool
		*/
		bool read(const QString& name, QString& data);

		/*
		* @writeFile,写入文件[重载1]
		* @param1,文件名
		* @param2,数据缓存
		* @param3,数据长度
		* @return,bool
		*/
		bool write(const QString& name, const char* data, const int& size);

		/*
		* @writeFile,写入文件[重载2]
		* @param1,文件名
		* @param2,字节数组
		* @return,bool
		*/
		bool write(const QString& name, const QByteArray& bytes);

		/*
		* @writeFile,写入文件[重载3]
		* @param1,文件名
		* @param2,文本列表
		* @return,bool
		*/
		bool write(const QString& name, const QStringList& textList);

		/*
		* @writeFile,写入文件[重载3]
		* @param1,文件名
		* @param2,数据
		* @return,bool
		*/
		bool write(const QString& name, const QString& data);

		/*
		* @appendFile,追加文件[重载1]
		* @param1,文件名
		* @param2,缓存数据
		* @param3,数据大小
		* @return,bool
		*/
		bool append(const QString& name, const char* data, const int& size);

		/*
		* @appendFile,追加文件[重载2]
		* @param1,文件名
		* @param2,字节数组
		* @return,bool
		*/
		bool append(const QString& name, const QByteArray& bytes);

		/*
		* @appendFile,追加文件[重载3]
		* @param1,文件名
		* @param2,文件列表
		* @return,bool
		*/
		bool append(const QString& name, const QStringList& textList);

		/*
		* @appendFile,追加文件[重载3]
		* @param1,文件名
		* @param2,数据
		* @return,bool
		*/
		bool append(const QString& name, const QString& data);

		/*
		* @compareFile,对比文件
		* @param1,文件1
		* @param2,文件2
		* @return,int;打开文件失败-1,相同0,不同1
		*/
		int compare(const QString& f1, const QString& f2);

		/*
		* @exist,存在
		* @param1,文件名
		* @return,bool
		*/
		bool exist(const QString& name);

		/*
		* @getSize,获取大小
		* @param1,文件名
		* @return,long long
		*/
		qint64 getSize(const QString& name);

		/*
		* @getCreateTime,获取创建时间
		* @param1,文件名
		* @return,QString
		*/
		QString getCreateTime(const QString& name);

		/*
		* @getModifyTime,获取修改时间
		* @param1,文件名
		* @return,const QString
		*/
		QString getModifyTime(const QString& name);

		/*
		* @getAccessTime,获取修改时间
		* @param1,文件名
		* @return,const QString
		*/
		QString getAccessTime(const QString& name);

		/*
		* @getName,获取名称
		* @param1,路径名
		* @return,QString
		*/
		QString getName(const QString& path);

		/*
		* @getBaseName,获取基本名称
		* @param1,路径名
		* @return,QString
		*/
		QString getBaseName(const QString& path);

		/*
		* @getSuffix,获取后缀名
		* @param1,文件名
		* @return,QString
		*/
		QString getSuffix(const QString& file);

		/*
		* @getPath,获取路径
		* @param1,文件名
		* @return,QString
		*/
		QString getPath(const QString& file);
		
		/*
		* @isFile,判断是否为文件
		* @param1,文件名
		* @return,bool
		*/
		bool isFile(const QString& name);

		/*
		* @isDir,判断是否为文件夹
		* @param1,文件夹名
		* @return,bool
		*/
		bool isDir(const QString& name);

		/*
		* @remove,移除
		* @param1,文件名
		* @return,bool
		*/
		bool remove(const QString& name);

		/*
		* @rename,重命名
		* @param1,老文件
		* @param2,新文件
		* @return,bool
		*/
		bool rename(const QString& oldName, const QString& newName);

		/*
		* @copy,复制
		* @param1,要拷贝的文件
		* @param2,被拷贝的文件
		* @param3,文件存在是否拷贝
		* @return,bool
		*/
		bool copy(const QString& file1, const QString& file2, bool existCopy = true);

		/*
		* @move,移动
		* @param1,源文件
		* @param2,目标文件
		* @return,bool
		*/
		bool move(const QString& file1, const QString& file2);

		/*
		* @setHidden,设置隐藏
		* @param1,文件名
		* @param2,是否隐藏
		* @return,bool
		*/
		bool setHidden(const QString& name, bool hidden = true);

		/*
		* @readJson,读json文件
		* @param1,文件名
		* @param2,根对象
		* @return,bool
		*/
		bool readJson(const QString& name, QJsonObject& rootObj);

		/*
		* @writeJson,写json文件
		* @param1,文件名
		* @param2,根对象
		* @return,bool
		*/
		bool writeJson(const QString& name, const QJsonObject& rootObj);

		/*
		* @repairJson1LevelNode,修复1级节点Json文件
		* @param1,文件名
		* @param2,节点列表
		* @param3,键列表
		* @param4,值列表
		* @return,bool
		*/
		bool repairJson1LevelNode(
			const QString& fileName,
			const QStringList& nodeList,
			const QList<QStringList>& keyList,
			const QList<QStringList>& valueList
		);

		/*
		* @repairJson2LevelNode,修复2级节点Json文件
		* @notice,这个只可以用来修复动态的2级节点
		* @param1,文件名
		* @param2,节点列表
		* @param3,键列表
		* @param4,值列表
		* @return,bool
		*/
		bool repairJson2LevelNode
		(
			const QString& fileName,
			const QStringList& nodeList,
			const QList<QStringList>& keyList,
			const QList<QStringList>& valueList
		);

		/*
		* @repairJson2LevelNode,修复2级节点Json文件
		* @notice,这个只可以用来修复静态的2级节点
		* @param1,文件名
		* @param2,节点列表
		* @param3,父键列表
		* @param4,子键列表
		* @param5,子值列表
		* @return,bool
		*/
		bool repairJson2LevelNode
		(
			const QString& fileName,
			const QStringList& nodeList,
			const QList<QStringList>& parentKeyList,
			const QList<QStringList>& childKeyList,
			const QList<QStringList>& childValueList
		);

		/*
		* @repairJson2LevelNode,修复2级节点Json文件
		* @notice,这个只可以用来修复静态与子键和子值不一致的2级节点
		* @param1,文件名
		* @param2,节点列表
		* @param3,父键列表
		* @param4,子键列表(数组)
		* @param5,子值列表(数组)
		* @return,bool
		*/
		bool repairJson2LevelNode
		(
			const QString& fileName,
			const QStringList& nodeList,
			const QList<QStringList>& parentKeyList,
			const QList<const QStringList*>& childKeyList,
			const QList<const QStringList*>& childValueList
		);
	};

}
