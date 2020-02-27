#pragma once

#include <QObject>
#include <queue>
#include <serial/serial.h>
#include <QThread>
#include <QDebug>
#include <QTimer>

namespace serialPort {

	typedef serial::bytesize_t datasize_t;
	typedef serial::stopbits_t stopbits_t;
	typedef serial::parity_t parity_t;


	namespace worker {
		class SerialPortWorker : public QObject{
			Q_OBJECT
		private:
			std::queue<std::string> linesToSend;
			QSharedPointer<serial::Serial> _serial;
			QTimer timer;

		private slots:


		public:
			SerialPortWorker() : timer(this) {
				connect(&timer, &QTimer::timeout, this, &SerialPortWorker::handleTimer);
				timer.setInterval(1);
			};

		public slots:			
			void handleTimer() {
				if (!_serial->isOpen()) {
					timer.stop();
					emit serialClosed();
					return;
				}
				if (!linesToSend.empty()) {
					_serial->write(linesToSend.front());
					linesToSend.pop();
				}
				if (_serial->available()) {
					emit receivedNewLine(
						_serial->readline().c_str()
					);
				}
			}
			void open(serial::Serial * serial_) {
				_serial = QSharedPointer<serial::Serial>(serial_);

				if(!_serial->isOpen())
					_serial->open();
				if (_serial->isOpen())
					emit serialOpened();
				timer.start();
			}
			void print(const QString & line) {
				linesToSend.push(line.toStdString());
			}
			void close() {
				timer.stop();
				_serial->close();
				emit serialClosed();
			}
		signals:
			void receivedNewLine(const QString & line);
			void serialClosed();
			void serialOpened();
		};
	}

	class SerialPort : public QObject
	{
		Q_OBJECT

	private:
		QThread serialThread;
		bool _opened = false;
		std::string _port;
		uint32_t _baudrate	{ 9600 };
		datasize_t _datasize{ datasize_t::eightbits };
		stopbits_t _stopbits{ stopbits_t::stopbits_one };
		parity_t _parity	{ parity_t::parity_none };
		/*
		std::function<void(void)> _portOpenedCallback{
			[this] {
				qDebug() << "Port " << _port.c_str() << " opened.";
			}
		};
		std::function<void(void)> _portClosedCallback{
			[this] {
				qDebug() << "Port " << _port.c_str() << " closed.";
			}
		};
		std::function<void(const std::string &)> _portNewLineCallback{
			[](const std::string & line) {
				qDebug() << "Line: " << line.c_str();
			}
		};
		*/
	public:
		SerialPort(QObject *parent);
		~SerialPort();

		void open();
		void close();

		void println(const std::string & line);
		void println(const QString & line);

		void setPort(const std::string & port);
		void setBaudrate(uint32_t baudrate);
		void setDataSize(datasize_t datasize);
		void setStopBits(stopbits_t stopbits);
		void setParity(parity_t parity);

		//void setOnPortOpenedCallback(std::function<void(void)> callback);
		//void setOnPortClosedCallback(std::function<void(void)> callback);
		//void setOnNewLineCallback(std::function<void(const std::string &)> callback);

	private slots:
		void handleNewLine(const QString & line);
		void handleSerialClosed();
		void handleSerialOpened();

	signals:
		void emitOpen(serial::Serial * serial_);
		void emitPrint(const QString & line);
		void emitClose();
		void opened();
		void closed();
		void receivedLine(const QString & line);
		void transmitedLine(const QString & line);
	};
}