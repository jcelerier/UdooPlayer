#include "PlayThread.h"
#include <manager/StreamingManager.h>

#include <io/FFMPEGFileInput.h>
#include <io/LoopInputProxy.h>
#include <io/InputMultiplexer2.h>
#include <io/SfxInputProxy.h>
#include <io/StereoAdapter.h>
#include <io/SummationProxy.h>
#include <stream_io/PortaudioOutput.h>

#include <benchmark/Pan.h>
#include <benchmark/Sequence.h>

PlayThread::PlayThread(QObject *parent) :
	QThread(parent)
{
}

void PlayThread::run()
{
	manager->input()->reset();
	bufferCount = 0;
	isPlaying = true;

	manager->execute();
}

void PlayThread::stop()
{
	manager->stop();

	manager->input()->reset();
	bufferCount = 0;
	isPlaying = false;
}

void PlayThread::load(const SongData& s)
{
	//// Remise à 0
	bufferCount = 0;
	int track_count = s.tracks.size();
	volumes.clear();
	pans.clear();
	mutes.clear();
	manager.reset();

	volumes.resize(track_count);
	pans.resize(track_count);
	mutes.resize(track_count);

	//// Chargement
	std::vector<Input_p> chains(track_count);

	#pragma omp parallel for
	for(int i = 0; i < track_count; i++)
	{
		volumes[i] = std::make_shared<Amplify<double>>(conf);
		pans[i] = std::make_shared<Pan<double>>(conf);
		mutes[i] = std::make_shared<Mute<double>>(conf);

		auto file = new FFMPEGFileInput<double>(s.tracks[i].file, conf);
		maxBufferCount = file->v(0).size() / conf.bufferSize;
		emit setTotalTime(file->v(0).size() / double(conf.samplingRate));
		chains[i] = Input_p(new SfxInputProxy<double>(new StereoAdapter<double>(new LoopInputProxy<double>(file)),
													  new Sequence<double>(conf, volumes[i], pans[i], mutes[i])));
	}

	// Piste master
	auto input = Input_p(new SfxInputProxy<double>(new SummationProxy<double>(new InputMultiplexer<double>(conf, chains)), masterVolume));

	// Manager
	manager = std::make_shared<StreamingManager<double>>(std::move(input),
														 std::move(std::make_shared<PortaudioOutput<double>>(conf)),
														 std::bind(&PlayThread::timeHandle, this),
														 conf);
}
