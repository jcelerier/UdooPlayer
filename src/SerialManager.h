#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H
#include <QThread>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <memory>

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
		SerialManager(QObject* parent = 0):
			QThread(parent)
		{
		}

	signals:
		// Envoyé lorsqu'une boite est activée
		void boxActivated(int, int);

	public slots:
		void readyReadSlot();
		void stop()
		{
			finished = true;
		}

	protected:
		virtual void run();

	private:
		bool finished{false};
		std::shared_ptr<QSerialPort> port;
};

#endif // SERIALMANAGER_H
