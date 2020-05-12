#include "FileLogger.h"

const std::map<QString, FileLogger::FilesFormats> FileLogger::LOG_FILES_FORMATS_MAP = {
	{ QObject::tr("Comma separated values (*.csv)"), FileLogger::CSV },
	{ QObject::tr("JSON file (*.json)"), FileLogger::JSON },
	{ QObject::tr("Excel file (*.xlsx)"), FileLogger::XLSX }
};

QString FileLogger::getLogFilesFormatsFilter() {
	QString filter = "";
	bool first = true;
	for (auto & fileFormat : LOG_FILES_FORMATS_MAP) {
		filter += (first ? "" : ";;") + fileFormat.first;
		first = false;
	}
	return filter;
}

FileLogger::FilesFormats FileLogger::getLogFileFormatId(const QString & name) {
	return LOG_FILES_FORMATS_MAP.at(name);
}

FileLogger::FileLogger(QObject *parent, const QString & filepath, FilesFormats fileFormat)
	: QObject(parent)
{
}

FileLogger::~FileLogger()
{
}
