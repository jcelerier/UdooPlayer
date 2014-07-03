#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>


#include <benchmark/Amplify.h>
#include <benchmark/Pan.h>

#include "SongData.h"

#include <QDebug>
class PlayThread : public QThread
{
		Q_OBJECT
	public:
		explicit PlayThread(QObject *parent = 0);

	signals:

	public slots:
		void run();

		void stop()
		{

		}

		void play()
		{

		}

		void setMasterVolume(int vol)
		{
			masterVolume->setGain(vol / 100.0);
		}

		void setVolume(int channel, int vol)
		{
			volumes[channel]->setGain(vol / 100.0);
		}

		void setPan(int channel, int pan)
		{
			pans[channel]->setPan(pan / 100.0);
		}

		void load(SongData s);

	private:
		Amplify<double>* masterVolume;
		std::vector<Amplify<double>*> volumes;
		std::vector<Pan<double>*> pans;
};

#endif // PLAYTHREAD_H
