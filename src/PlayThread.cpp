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
	conf.bufferSize = 128;
}

void PlayThread::run()
{
	manager->execute();
}

void PlayThread::stop()
{
	manager->input()->reset();
	manager->stop();
	bufferCount = 0;
}

void PlayThread::load(SongData s)
{
	bufferCount = 0;
	int track_count = s.tracks.size();
	volumes.clear();
	pans.clear();
	mutes.clear();

	for(int i = 0; i < track_count; i++)
	{
		volumes.push_back(std::make_shared<Amplify<double>>(conf));
		pans.push_back(std::make_shared<Pan<double>>(conf));
		mutes.push_back(std::make_shared<Mute<double>>(conf));
	}

	std::vector<Input_p> chains;
	for(int i = 0; i < track_count; i++)
	{
		auto file = new FFMPEGFileInput<double>(s.tracks[i].file, conf);
		maxBufferCount = file->v(0).size() / conf.bufferSize;
		emit setTotalTime(file->v(0).size() / 44100.0);
		chains.emplace_back(new SfxInputProxy<double>(new StereoAdapter<double>(new LoopInputProxy<double>(file)),
													  new Sequence<double>(conf, volumes[i], pans[i], mutes[i])));
	}

	auto input = Input_p(new SfxInputProxy<double>(new SummationProxy<double>(new InputMultiplexer<double>(conf, chains)), masterVolume));


	auto zeO = new PortaudioOutput<double>(conf);
	auto output = std::shared_ptr<PortaudioOutput<double>>(zeO);

	manager = std::make_shared<StreamingManager<double>>(std::move(input),
														 std::move(output),
														 std::bind(&PlayThread::timeHandle, this),
														 conf);
}
