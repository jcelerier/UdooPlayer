#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QThread>
#include <QString>
#include <QStringList>
#include <QDebug>

class QSerialPort;
class SerialManager : public QThread
{
	public:
		QSerialPort* port;
		SerialManager()
		{
		}

	public slots:
		void readyReadSlot();

	protected:
		virtual void run();

	private:
		void parse(QString line)
		{
			auto tokens = line.split(" ");
			qDebug() << tokens[2];
		}

};

#endif // SERIALMANAGER_H
