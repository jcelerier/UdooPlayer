#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QThread>
#include <QString>
#include <QStringList>
#include <QDebug>

class QSerialPort;
class SerialManager : public QThread
{
		Q_OBJECT
	public:
		QSerialPort* port;
		SerialManager(QObject* parent = 0):
			QThread(parent)
		{
		}

	signals:
		void boxActivated(int);

	public slots:
		void readyReadSlot();

	protected:
		virtual void run();
};

#endif // SERIALMANAGER_H
