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
	manager->execute();
}

void PlayThread::stop()
{
	manager->input()->reset();
	manager->stop();
}

void PlayThread::load(SongData s)
{
	int track_count = s.tracks.size();
	volumes.resize(track_count, std::make_shared<Amplify<double>>(conf));
	pans.resize(track_count, std::make_shared<Pan<double>>(conf));

	std::vector<Input_p> chains;
	for(int i = 0; i < track_count; i++)
	{
		chains.emplace_back(new SfxInputProxy<double>(new StereoAdapter<double>(new LoopInputProxy<double>(new FFMPEGFileInput<double>(s.tracks[i].file, conf))),
													  new Sequence<double>(conf, volumes[i], pans[i])));
	}

	auto input = Input_p(new SfxInputProxy<double>(new SummationProxy<double>(new InputMultiplexer<double>(conf, chains)), masterVolume));


	auto zeO = new PortaudioOutput<double>(conf);
	auto output = std::shared_ptr<PortaudioOutput<double>>(zeO);

	manager = std::make_shared<StreamingManager<double>>(std::move(input), std::move(output), conf);
}
