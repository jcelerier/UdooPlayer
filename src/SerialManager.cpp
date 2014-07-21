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
	port = new QSerialPort("ttymxc3");

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
				if(numRead > 0) emit boxActivated(QString(txt).simplified().replace(" ", "").toInt());
			}
		}
	}
}
