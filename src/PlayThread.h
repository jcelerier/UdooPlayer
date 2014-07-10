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
		// A appeler quand on veut faire lecture
		void run();

		// Volume principal
		// Entre 0 et 100
		void setMasterVolume(int vol)
		{
			masterVolume->setGain(vol / 100.0);
		}

		// Volume par canal
		// Entre 0 et 100
		void setVolume(int channel, int vol)
		{
			volumes[channel]->setGain(vol / 100.0);
		}

		// Pan
		// Entre -100 et 100
		void setPan(int channel, int pan)
		{
			pans[channel]->setPan(pan / 100.0);
		}

		// Sourdine d'un canal
		void setMute(int channel, bool doMute)
		{
			doMute? mutes[channel]->mute() : mutes[channel]->unmute();
		}

		// Appelé régulièrement pour mettre à jour le beat ou on se trouve
		// dans l'interface
		void timeHandle()
		{
			if(++bufferCount > maxBufferCount) bufferCount = 0;
			emit spentTime(bufferCount * conf.bufferSize / double(conf.samplingRate));
		}

		// Charge un morceau dans le moteur
		void load(SongData s);

		// Arrête la lecture
		void stop();

	private:
		Parameters<double> conf;
		std::shared_ptr<Amplify<double>> masterVolume{new Amplify<double>(conf)};
		std::vector<std::shared_ptr<Amplify<double>>> volumes;
		std::vector<std::shared_ptr<Pan<double>>> pans;
		std::vector<std::shared_ptr<Mute<double>>> mutes;

		std::shared_ptr<StreamingManager<double>> manager;

		// Buffer auquel on se trouve
		int bufferCount{};

		// Nombre de buffers total dans une boucle
		int maxBufferCount{};
};

#endif // PLAYTHREAD_H
