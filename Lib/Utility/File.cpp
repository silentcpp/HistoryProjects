#include "File.h"
#include <Windows.h>

static char g_encodeing[32] = { "utf-8" };

#define RUN_BREAK(success,error) \
if ((success))\
{\
	setLastError(error);\
	break;\
}

void Utility::File::setEncoding(const char* encoding)
{
	if (!encoding)
		return;

	strcpy_s(g_encodeing, sizeof(g_encodeing), encoding);
}

bool Utility::File::read(const QString& name, char*& data, int& size)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly), file.errorString());
		QByteArray bytes = file.readAll();
		size = bytes.size();
		RUN_BREAK(!(data = new(std::nothrow) char[size]), "缓存区分配内存失败");
		memset(data, 0, size);
		memcpy(data, bytes.data(), size);
		file.close();
	} while (false);
	return result;
}

bool Utility::File::read(const QString& name, QByteArray& bytes)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly), file.errorString());
		bytes = file.readAll();
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::read(const QString& name, QStringList& textList)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		while (!stream.atEnd())
		{
			textList.push_back(stream.readLine());
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::read(const QString& name, QString& data)
{
	bool result = false;
	do 
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		data = stream.readAll();
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::write(const QString& name, const char* data, const int& size)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly), file.errorString());
		RUN_BREAK(file.write(data, size) != size, "文件写入数据校验失败");
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::write(const QString& name, const QByteArray& bytes)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly), file.errorString());
		RUN_BREAK(file.write(bytes) != bytes.size(), "文件写入数据校验失败");
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::write(const QString& name, const QStringList& textList)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		for (auto& x : textList)
		{
			stream << x;
		}
		stream.flush();
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::write(const QString& name, const QString& data)
{
	bool result = false;
	do 
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		stream << data;
		stream.flush();
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::append(const QString& name, const char* data, const int& size)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::Append), file.errorString());
		RUN_BREAK(file.write(data, size) != size, "文件写入数据校验失败");
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::append(const QString& name, const QByteArray& bytes)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::Append), file.errorString());
		RUN_BREAK(file.write(bytes) != bytes.size(), "文件写入数据校验失败");
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::append(const QString& name, const QStringList& textList)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::Append | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		for (auto& x : textList)
		{
			stream << x;
		}
		stream.flush();
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::append(const QString& name, const QString& data)
{
	bool result = false;
	do 
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::Append | QFile::Text), file.errorString());
		QTextStream stream(&file);
		stream.setCodec(g_encodeing);
		stream << data;
		stream.flush();
		file.close();
		result = true;
	} while (false);
	return result;
}

int Utility::File::compare(const QString& f1, const QString& f2)
{
	int result = -1;
	do
	{
		QFile file1(f1), file2(f2);
		RUN_BREAK(file1.open(QFile::ReadOnly), QString("打开文件%1失败,%2")
			.arg(f1, file1.errorString()));

		RUN_BREAK(file2.open(QFile::ReadOnly), QString("打开文件%1失败,%2")
			.arg(f2, file2.errorString()));

		QByteArray b1 = file1.readAll();

		QByteArray b2 = file2.readAll();

		file1.close();

		file2.close();

		result = (b1 == b2) ? 0 : 1;
	} while (false);
	return result;
}

bool Utility::File::exist(const QString& name)
{
	return QFileInfo(name).exists();
}

qint64 Utility::File::getSize(const QString& name)
{
	return QFileInfo(name).size();
}

QString Utility::File::getCreateTime(const QString& name)
{
	return QFileInfo(name).created().toString("yyyy-MM-dd hh:mm:ss");
}

QString Utility::File::getModifyTime(const QString& name)
{
	return QFileInfo(name).lastModified().toString("yyyy-MM-dd hh:mm:ss");
}

QString Utility::File::getAccessTime(const QString& name)
{
	return QFileInfo(name).lastRead().toString("yyyy-MM-dd hh:mm:ss");
}

QString Utility::File::getName(const QString& path)
{
	return QFileInfo(path).fileName();
}

QString Utility::File::getBaseName(const QString& path)
{
	return QFileInfo(path).baseName();
}

QString Utility::File::getSuffix(const QString& file)
{
	return QFileInfo(file).suffix();
}

QString Utility::File::getPath(const QString& file)
{
	return QFileInfo(file).path();
}

bool Utility::File::isFile(const QString& name)
{
	return QFileInfo(name).isFile();
}

bool Utility::File::isDir(const QString& name)
{
	return QFileInfo(name).isDir();
}

bool Utility::File::remove(const QString& name)
{
	return QFile::remove(name);
}

bool Utility::File::rename(const QString& oldName, const QString& newName)
{
	bool result = false;
	do 
	{
		RUN_BREAK(oldName.isEmpty(), "旧文件名为空");
		RUN_BREAK(newName.isEmpty(), "新文件名为空");

		RUN_BREAK(!isFile(oldName), QString("文件%1不存在").arg(oldName));

		QString temp = newName;
		if (isDir(temp))
		{
			if (temp.right(1) != "\\")
				temp.append("\\");
			temp = temp + getName(oldName);
		}

		RUN_BREAK(!MoveFileW(oldName.toStdWString().c_str(),
			newName.toStdWString().c_str()),
			QString("重命名文件%1失败,\n错误代码:%2")
			.arg(oldName).arg(::GetLastError()));

		result = true;
	} while (false);
	return result;
}

bool Utility::File::copy(const QString& file1, const QString& file2, bool existCopy)
{
	bool result = false;
	do 
	{
		RUN_BREAK(!isFile(file1), QString("文件%1不存在").arg(file1));

		QString temp = file2;
		if (isDir(temp))
		{
			if (temp.right(1) != "\\")
				temp.append("\\");
			temp += getName(file1);
		}

		RUN_BREAK(!CopyFileW(file1.toStdWString().c_str(),
			temp.toStdWString().c_str(), !(BOOL)existCopy),
			QString("拷贝文件%1失败,\n错误代码:%lu").arg(temp).
			arg(::GetLastError()));

		result = true;
	} while (false);
	return result;
}

bool Utility::File::move(const QString& file1, const QString& file2)
{
	if (!rename(file1, file2))
	{
		setLastError(QString("移动文件%1失败,\n错误代码:%2")
			.arg(file1).arg(::GetLastError()));
		return false;
	}
	return true;
}

bool Utility::File::setHidden(const QString& name, bool hidden)
{
	bool result = true;
	DWORD attribute = GetFileAttributesW(name.toStdWString().c_str());
	if (hidden)
	{
		if (!(attribute & FILE_ATTRIBUTE_HIDDEN))
		{
			attribute |= FILE_ATTRIBUTE_HIDDEN;
			if (!SetFileAttributesW(name.toStdWString().c_str(), attribute))
			{
				setLastError(QString("修改文件属性失败,错误代码:%lu").arg(::GetLastError()));
				result = false;
			}
		}
	}
	else
	{
		if (attribute & FILE_ATTRIBUTE_HIDDEN)
		{
			attribute &= ~FILE_ATTRIBUTE_HIDDEN;
			if (!SetFileAttributesW(name.toStdWString().c_str(), attribute))
			{
				setLastError(QString("修改文件属性失败,错误代码:%lu").arg(::GetLastError()));
				result = false;
			}
		}
	}
	return result;
}

bool Utility::File::readJson(const QString& name, QJsonObject& rootObj)
{
	bool result = false;
	do
	{
		QFile file(name);
		RUN_BREAK(!file.open(QFile::ReadOnly), file.errorString());
		QByteArray bytes = file.readAll();
		file.close();

		QJsonParseError jsonError;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(bytes, &jsonError));
		RUN_BREAK(jsonError.error != QJsonParseError::NoError, jsonError.errorString());
		rootObj = jsonDoc.object();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::writeJson(const QString& name, const QJsonObject& rootObj)
{
	bool result = false;
	do
	{
		QJsonDocument doc(rootObj);
		QByteArray bytes = doc.toJson();
		QFile file(name);
		RUN_BREAK(!file.open(QFile::WriteOnly), file.errorString());
		if (bytes.length() != file.write(bytes))
		{
			setLastError(QString("写入%1数据校验失败").arg(name));
			file.close();
			break;
		}
		file.close();
		result = true;
	} while (false);
	return result;
}

bool Utility::File::repairJson1LevelNode(
	const QString& fileName,
	const QStringList& nodeList,
	const QList<QStringList>& keyList,
	const QList<QStringList>& valueList)
{
	bool result = false, save = false;
	do
	{
		auto getValue = [&](int index, const QString& childKey)->QString
		{
			for (int i = 0; i < keyList[index].size(); ++i)
			{
				if (keyList[index].at(i) == childKey)
				{
					return valueList[index].at(i);
				}
			}
			return QString("null");
		};

		QJsonObject rootObj;
		RUN_BREAK(!readJson(fileName, rootObj),
			QString("自检读取%1文件失败,").arg(fileName) + getLastError());

		for (int i = 0; i < nodeList.count(); ++i)
		{
			QStringList objectKeyList, loseKeyList, loseValueList;
			if (rootObj.contains(nodeList[i]))
			{
				loseKeyList = keyList[i];
				QJsonObject jsonObject = rootObj.value(nodeList[i]).toObject();
				objectKeyList = jsonObject.keys();
				QStringList oldObjectKeyList = objectKeyList;
				if (removeList(keyList[i], objectKeyList))
				{
					QStringList removeObjList;
					for (int j = 0; j < oldObjectKeyList.size(); j++)
					{
						if (!objectKeyList.contains(oldObjectKeyList[j]))
						{
							removeObjList.push_back(oldObjectKeyList[j]);
						}
					}

					for (auto& x : removeObjList)
					{
						jsonObject.remove(x);
					}
				}

				if (!compareList(keyList[i], objectKeyList))
				{
					for (int j = 0; j < keyList[i].size(); j++)
					{
						for (int k = 0; k < objectKeyList.size(); k++)
						{
							if (keyList[i].at(j) == objectKeyList[k])
							{
								loseKeyList.removeOne(objectKeyList[k]);
							}
						}
					}

					for (int j = 0; j < loseKeyList.size(); j++)
					{
						loseValueList.append(getValue(i, loseKeyList[j]));
					}

					for (int j = 0; j < loseKeyList.size(); j++)
					{
						jsonObject.insert(loseKeyList[j], loseValueList[j]);
					}
				}

				if (jsonObject != rootObj.value(nodeList[i]).toObject())
				{
					save = true;
					rootObj.insert(nodeList[i], jsonObject);
				}
			}
			else
			{
				QJsonObject newObj;
				for (int key = 0; key < keyList[i].size(); key++)
				{
					newObj.insert(keyList[i].at(key), valueList[i].at(key));
				}
				rootObj.insert(nodeList[i], newObj);
				save = true;
			}
		}

		if (save)
		{
			RUN_BREAK(!writeJson(fileName, rootObj),
				QString("自检写入%1失败,").arg(fileName) + getLastError());
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::File::repairJson2LevelNode(
	const QString& fileName,
	const QStringList& nodeList,
	const QList<QStringList>& keyList,
	const QList<QStringList>& valueList)
{
	bool result = false, save = false;
	do
	{
		auto getValue = [&](int index, const QString& childKey)->QString
		{
			for (int i = 0; i < keyList[index].size(); ++i)
			{
				if (keyList[index].at(i) == childKey)
				{
					return valueList[index].at(i);
				}
			}
			return QString("null");
		};

		QJsonObject rootObj;
		RUN_BREAK(!readJson(fileName, rootObj),
			QString("自检读取%1文件失败,").arg(fileName) + getLastError());

		for (int i = 0; i < nodeList.count(); ++i)
		{
			QStringList dynamicKeyList, objectKeyList, loseKeyList, loseValueList;
			if (rootObj.contains(nodeList[i]))
			{
				loseKeyList = keyList[i];
				QJsonObject jsonObject = rootObj.value(nodeList[i]).toObject();
				dynamicKeyList = jsonObject.keys();
				for (int key = 0; key < dynamicKeyList.size(); ++key)
				{
					QStringList oldObjectKeyList = objectKeyList = jsonObject
						.value(dynamicKeyList[key]).toObject().keys();

					if (removeList(keyList[i], objectKeyList))
					{
						QStringList removeObjList;
						for (int j = 0; j < oldObjectKeyList.size(); j++)
						{
							if (!objectKeyList.contains(oldObjectKeyList[j]))
							{
								removeObjList.push_back(oldObjectKeyList[j]);
							}
						}

						QJsonObject removeObject = jsonObject.
							value(dynamicKeyList[key]).toObject();
						for (auto& x : removeObjList)
						{
							removeObject.remove(x);
						}
						jsonObject.insert(dynamicKeyList[key], removeObject);
					}

					if (!compareList(keyList[i], objectKeyList))
					{
						for (int j = 0; j < keyList[i].size(); j++)
						{
							for (int k = 0; k < objectKeyList.size(); k++)
							{
								if (keyList[i].at(j) == objectKeyList[k])
								{
									loseKeyList.removeOne(objectKeyList[k]);
								}
							}
						}

						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseValueList.append(getValue(i, loseKeyList[j]));
						}

						QJsonObject loseObject = jsonObject.value(dynamicKeyList[key]).toObject();
						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseObject.insert(loseKeyList[j], loseValueList[j]);
						}
						jsonObject.insert(dynamicKeyList[key], loseObject);
					}

					if (jsonObject.value(dynamicKeyList[key]).toObject()
						!= rootObj.value(nodeList[i]).toObject()
						.value(dynamicKeyList[key]).toObject())
					{
						save = true;
						rootObj.insert(nodeList[i], jsonObject);
					}
				}
			}
		}

		if (save)
		{
			RUN_BREAK(!writeJson(fileName, rootObj),
				QString("自检写入%1失败,").arg(fileName) + getLastError());
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::File::repairJson2LevelNode(
	const QString& fileName,
	const QStringList& nodeList,
	const QList<QStringList>& parentKeyList,
	const QList<QStringList>& childKeyList,
	const QList<QStringList>& childValueList)
{
	bool result = false, save = false;
	do
	{
		auto getValue = [&](int index, const QString& childKey)->QString
		{
			for (int i = 0; i < childKeyList[index].size(); ++i)
			{
				if (childKeyList[index].at(i) == childKey)
				{
					return childValueList[index].at(i);
				}
			}
			return QString("null");
		};

		QJsonObject rootObj;
		RUN_BREAK(!readJson(fileName, rootObj),
			QString("自检读取%1文件失败,").arg(fileName) + getLastError());

		for (int i = 0; i < nodeList.count(); ++i)
		{
			QStringList fixedKeyList, objectKeyList, loseKeyList, loseValueList;
			if (rootObj.contains(nodeList[i]))
			{
				QJsonObject jsonObject = rootObj.value(nodeList[i]).toObject();
				loseKeyList = childKeyList[i];
				fixedKeyList = parentKeyList[i];
				for (int key = 0; key < fixedKeyList.size(); ++key)
				{
					QStringList oldObjectKeyList = objectKeyList = jsonObject
						.value(fixedKeyList[key]).toObject().keys();

					if (removeList(childKeyList[i], objectKeyList))
					{
						QStringList removeObjList;
						for (int j = 0; j < oldObjectKeyList.size(); j++)
						{
							if (!objectKeyList.contains(oldObjectKeyList[j]))
							{
								removeObjList.push_back(oldObjectKeyList[j]);
							}
						}

						QJsonObject removeObject = jsonObject.
							value(fixedKeyList[key]).toObject();
						for (auto& x : removeObjList)
						{
							removeObject.remove(x);
						}
						jsonObject.insert(fixedKeyList[key], removeObject);
					}

					if (!compareList(childKeyList[i], objectKeyList))
					{
						for (int j = 0; j < childKeyList[i].size(); j++)
						{
							for (int k = 0; k < objectKeyList.size(); k++)
							{
								if (childKeyList[i].at(j) == objectKeyList[k])
								{
									loseKeyList.removeOne(objectKeyList[k]);
								}
							}
						}

						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseValueList.append(getValue(i, loseKeyList[j]));
						}

						QJsonObject loseObject = jsonObject.value(fixedKeyList[key]).toObject();
						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseObject.insert(loseKeyList[j], loseValueList[j]);
						}
						jsonObject.insert(fixedKeyList[key], loseObject);
					}

					if (jsonObject.value(fixedKeyList[key]).toObject() 
						!= rootObj.value(nodeList[i]).toObject()
						.value(fixedKeyList[key]).toObject())
					{
						save = true;
						rootObj.insert(nodeList[i], jsonObject);
					}
				}
			}
			else
			{
				QJsonObject newChildObject;
				for (int ck = 0; ck < childKeyList[i].size(); ck++)
				{
					newChildObject.insert(childKeyList[i].at(ck), childValueList[i].at(ck));
				}
				QJsonObject newParentObject;
				for (int pk = 0; pk < parentKeyList[i].size(); pk++)
				{
					newParentObject.insert(parentKeyList[i].at(pk), newChildObject);
				}
				rootObj.insert(nodeList[i], newParentObject);
			}
		}

		if (save)
		{
			RUN_BREAK(!writeJson(fileName, rootObj),
				QString("自检写入%1失败,").arg(fileName) + getLastError());
		}
		result = true;
	} while (false);
	return result;
}

bool Utility::File::repairJson2LevelNode(
	const QString& fileName,
	const QStringList& nodeList,
	const QList<QStringList>& parentKeyList,
	const QList<const QStringList*>& childKeyList,
	const QList<const QStringList*>& childValueList
)
{
	bool result = false, save = false;
	do
	{
		auto getValue = [&](int index, int child, const QString& childKey)->QString
		{
			for (int i = 0; i < childKeyList[index][child].size(); ++i)
			{
				if (childKeyList[index][child].at(i) == childKey)
				{
					return childValueList[index][child].at(i);
				}
			}
			return QString("null");
		};

		QJsonObject rootObj;
		RUN_BREAK(!readJson(fileName, rootObj),
			QString("自检读取%1文件失败,").arg(fileName) + getLastError());

		for (int i = 0; i < nodeList.count(); ++i)
		{
			QStringList fixedKeyList, objectKeyList, loseKeyList, loseValueList;
			if (rootObj.contains(nodeList[i]))
			{
				QJsonObject jsonObject = rootObj.value(nodeList[i]).toObject();
				fixedKeyList = parentKeyList[i];
				for (int key = 0; key < fixedKeyList.size(); ++key)
				{
					loseKeyList = childKeyList[i][key];
					QStringList oldObjectKeyList = objectKeyList = jsonObject
						.value(fixedKeyList[key]).toObject().keys();

					if (removeList(childKeyList[i][key], objectKeyList))
					{
						QStringList removeObjList;
						for (int j = 0; j < oldObjectKeyList.size(); j++)
						{
							if (!objectKeyList.contains(oldObjectKeyList[j]))
							{
								removeObjList.push_back(oldObjectKeyList[j]);
							}
						}

						QJsonObject removeObject = jsonObject.
							value(fixedKeyList[key]).toObject();
						for (auto& x : removeObjList)
						{
							removeObject.remove(x);
						}
						jsonObject.insert(fixedKeyList[key], removeObject);
					}

					if (!compareList(childKeyList[i][key], objectKeyList))
					{
						for (int j = 0; j < (*childKeyList[i])[key].size(); j++)
						{
							for (int k = 0; k < objectKeyList.size(); k++)
							{
								if ((*childKeyList[i])[key].at(j) == objectKeyList[k])
								{
									loseKeyList.removeOne(objectKeyList[k]);
								}
							}
						}

						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseValueList.append(getValue(i, key, loseKeyList[j]));
						}

						QJsonObject loseObject = jsonObject.value(fixedKeyList[key]).toObject();
						for (int j = 0; j < loseKeyList.size(); j++)
						{
							loseObject.insert(loseKeyList[j], loseValueList[j]);
						}
						jsonObject.insert(fixedKeyList[key], loseObject);
					}

					if (jsonObject.value(fixedKeyList[key]).toObject()
						!= rootObj.value(nodeList[i]).toObject()
						.value(fixedKeyList[key]).toObject())
					{
						save = true;
						rootObj.insert(nodeList[i], jsonObject);
					}
				}
			}
			else
			{
				QJsonObject parentNewObject,childNewObject;
				for (int pk = 0; pk < parentKeyList[i].size(); ++pk)
				{
					for (int ck = 0; ck < childKeyList[i][pk].size(); ++ck)
					{
						childNewObject.insert(childKeyList[i][pk][ck],
							childValueList[i][pk][ck]);
					}
					parentNewObject.insert(parentKeyList[i][pk], childNewObject);
					while (!childNewObject.isEmpty())
						childNewObject.erase(childNewObject.begin());
				}
				rootObj.insert(nodeList[i], parentNewObject);
				save = true;
			}
		}

		if (save)
		{
			RUN_BREAK(!writeJson(fileName, rootObj),
				QString("自检写入%1失败,").arg(fileName) + getLastError());
		}
		result = true;
	} while (false);
	return result;
}
