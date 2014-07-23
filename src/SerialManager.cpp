#include "SerialManager.h"

#include <QtSerialPort/QtSerialPort>
void SerialManager::readyReadSlot()
{
	while(!port->atEnd())
	{
		qDebug() << port->canReadLine();
	}
}

void SerialManager::run()
{
	// Ouverture du bon port
	port = std::make_shared<QSerialPort>("ttymxc3");

	// Configuration
	port->open(QIODevice::ReadOnly);
	port->setBaudRate(115200);
	port->setDataBits(QSerialPort::Data8);
	port->setParity(QSerialPort::NoParity);
	port->setStopBits(QSerialPort::OneStop);
	port->setFlowControl(QSerialPort::HardwareControl);

	if(port->isOpen())
	{
		char txt[128];
		int numRead;

		forever
		{
			port->waitForReadyRead(100);
			if(port->canReadLine())
			{
				numRead = port->readLine(txt, 128);
				auto msg = QString(txt).simplified().split(' ');
				if(numRead > 0) emit boxActivated(msg[0].toInt(), msg[1].toInt());
			}

			if(finished) break;
		}
	}
}
