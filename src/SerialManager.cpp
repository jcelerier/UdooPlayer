#include "SerialManager.h"

#include <QtSerialPort/QtSerialPort>
void SerialManager::run()
{
	port = new QSerialPort("ttymxc3");
	port->setBaudRate(115200);
	port->open(QIODevice::ReadOnly);
	if(port->isOpen())
	{
		qDebug() << "Port ouvert";
		QByteArray line;

		forever
		{
			//if(port->canReadLine())
			{
				qDebug() << "On a un truc à lire";
				parse(QString(port->readLine(64)));
			}
		}
	}
}
