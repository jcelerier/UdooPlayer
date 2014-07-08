#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>


#include <benchmark/Amplify.h>
#include <benchmark/Pan.h>
#include <benchmark/Mute.h>

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
		void spentTime(double);
		void setTotalTime(double);

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

		void setMute(int channel, bool doMute)
		{
			doMute? mutes[channel]->mute() : mutes[channel]->unmute();
		}

		void timeHandle()
		{
			if(++bufferCount > maxBufferCount) bufferCount = 0;
			emit spentTime(bufferCount * conf.bufferSize / double(conf.samplingRate));
		}

		void load(SongData s);
		void stop();

	private:
		Parameters<double> conf;
		std::shared_ptr<Amplify<double>> masterVolume{new Amplify<double>(conf)};
		std::vector<std::shared_ptr<Amplify<double>>> volumes;
		std::vector<std::shared_ptr<Pan<double>>> pans;
		std::vector<std::shared_ptr<Mute<double>>> mutes;

		std::shared_ptr<StreamingManager<double>> manager;

		int bufferCount{};
		int maxBufferCount{};
};

#endif // PLAYTHREAD_H
