#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QtSerialPort/QtSerialPort>
#include <QThread>

class SerialManager : public QThread
{
	public:
		QSerialPort* port;//{QString("ttymxc3")};
		SerialManager()
		{
			//port.setBaudRate(115200);
		}

	protected:
		virtual void run()
		{
			port = new QSerialPort("ttymxc3");
			port->setBaudRate(115200);
			port->open(QIODevice::ReadOnly);
			if(port->isOpen()) qDebug() << "Port ouvert";
			QByteArray line;

			forever
			{
				if(port->canReadLine())
				{
					qDebug() << "On a un truc à lire";
					parse(QString(port->readLine(64)));
				}
			}
		}

	private:
		void parse(QString line)
		{
			auto tokens = line.split(" ");
			qDebug() << tokens[2];
		}

};

#endif // SERIALMANAGER_H
