#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QThread>
#include <QString>
#include <QStringList>
#include <QDebug>

class QSerialPort;
/**
 * @brief The SerialManager class
 *
 * Interface avec le port série, pour recevoir les messages de l'Arduino
 */
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
		// Envoyé lorsqu'une boite est activée
		void boxActivated(int, int);

	public slots:
		void readyReadSlot();

	protected:
		virtual void run();
};

#endif // SERIALMANAGER_H
