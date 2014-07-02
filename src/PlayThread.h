#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>


#include <benchmark/Amplify.h>
#include <QDebug>
class PlayThread : public QThread
{
		Q_OBJECT
	public:
		explicit PlayThread(QObject *parent = 0);

	signals:

	public slots:
		void run();
		void setVol1(int vol)
		{
			vol1->setGain(vol / 100.0);
		}

		void setVol2(int vol)
		{
			vol2->setGain(vol / 100.0);
		}


	private:
		Amplify<double>* vol1;
		Amplify<double>* vol2;

};

#endif // PLAYTHREAD_H
