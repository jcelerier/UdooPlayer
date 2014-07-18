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
	port = new QSerialPort("ttymxc3");
	port->open(QIODevice::ReadOnly);
	port->setBaudRate(115200);
	port->setDataBits(QSerialPort::Data8);
	port->setParity(QSerialPort::NoParity);
	port->setStopBits(QSerialPort::OneStop);
	port->setFlowControl(QSerialPort::HardwareControl);

	if(port->isOpen())
	{
		qDebug() << "Port ouvert";
		char txt[128];
		int numRead = 0;

		forever
		{
			port->waitForReadyRead(100);
			if(port->canReadLine())
			{
				numRead = port->readLine(txt, 128);
				//qDebug() << txt;
			}
			//continue;

			if(numRead == 0 && ! port->waitForReadyRead(20))
			{
				qDebug() << "Erreur port série";
				break;
			}

			if(numRead > 0) emit boxActivated(QString(txt).simplified().replace(" ", "").toInt());
		}
	}
}
