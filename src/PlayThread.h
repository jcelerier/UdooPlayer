#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>


#include <benchmark/Amplify.h>
#include <benchmark/Pan.h>

#include "SongData.h"

#include <QDebug>

template<typename T>
class StreamingManager;

class PlayThread : public QThread
{
		Q_OBJECT
	public:
		explicit PlayThread(QObject *parent = 0);

	signals:

	public slots:
		void run();

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

		void stop();
	private:
		Parameters<double> conf;
		std::shared_ptr<Amplify<double>> masterVolume{new Amplify<double>(conf)};
		std::vector<std::shared_ptr<Amplify<double>>> volumes;
		std::vector<std::shared_ptr<Pan<double>>> pans;

		std::shared_ptr<StreamingManager<double>> manager;
};

#endif // PLAYTHREAD_H
