#pragma once

#include <QSerialPort>
#include <QThread>

class SerialPortThread : public QThread
{
	Q_OBJECT

public:
	SerialPortThread(QObject *parent);
	~SerialPortThread();

	void setDestructorMsgIfPortOpen(const QString & msg);
	void setPortName(const QString & comName);
	void setBaudRate(qint32 baudRate);
	void setDataBits(QSerialPort::DataBits dataBits);
	void setParity(QSerialPort::Parity parity);
	void setStopBits(QSerialPort::StopBits stopBits);
	void setFlowControl(QSerialPort::FlowControl flowControl);
	void setOpenModeFlag(QIODevice::OpenModeFlag openModeFlag);
	bool open();
	bool isOpen();

public slots:
	void println(const QString & data);
	//void println(const std::string & data);
	void print(const QString & data);
	void print(const std::string & data);
	void close();

private:
	void run() override;

	QSerialPort serial;
	QByteArray buffer;

	QString onDeleteMsg;

	QString com = "";
	qint32 baudRate = 0;
	QSerialPort::DataBits dataBits = QSerialPort::DataBits::Data8;
	QSerialPort::Parity parity = QSerialPort::Parity::NoParity;
	QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop;
	QSerialPort::FlowControl flowControl = QSerialPort::FlowControl::NoFlowControl;
	QIODevice::OpenModeFlag openModeFlag = QIODevice::OpenModeFlag::ReadWrite;

	bool closing = false;

private slots:
	void onReadyRead();

signals:
	void errorOccured(const QString & error);
	void gotNewLine(const QString & newLine);
};