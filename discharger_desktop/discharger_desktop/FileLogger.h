#pragma once

#include <QObject>

class FileLogger : public QObject
{
	Q_OBJECT

public:
	enum FilesFormats {
		NONE, CSV, JSON, XLSX
	};
	const static std::map<QString, FilesFormats> LOG_FILES_FORMATS_MAP;
	static QString getLogFilesFormatsFilter();
	static FilesFormats getLogFileFormatId(const QString & name);

	FileLogger(QObject *parent, const QString & filepath, FilesFormats fileFormat);
	~FileLogger();

	void save() {}
	bool createFile() { return 1; };
};
