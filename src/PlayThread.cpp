#include "PlayThread.h"

PlayThread::PlayThread(QObject *parent) :
	QThread(parent)
{
}


#include <io/FileInput.h>
#include <io/FileOutput.h>
#include <io/LoopInputProxy.h>

#include <manager/BenchmarkManager.h>
#include <manager/StreamingManager.h>
#include <benchmark/Dummy.h>

#include <io/InputMultiplexer2.h>
#include <io/SfxInputProxy.h>
#include <io/StereoAdapter.h>

#include <benchmark/Pan.h>
#include <benchmark/Sequence.h>

#include <io/audio/QtAudioOutput.h>
#include <io/SummationProxy.h>

#include <stream_io/PortaudioOutput.h>


void PlayThread::run()
{

	Parameters<double> conf;


	auto stereo_loop_file1 = new StereoAdapter<double>(new LoopInputProxy<double>(new FileInput<double>("/home/doom/travail/watermarking/output/beat1.wav", conf)));
	auto stereo_loop_file2 = new StereoAdapter<double>(new LoopInputProxy<double>(new FileInput<double>("/home/doom/travail/watermarking/output/beat2.wav", conf)));

	vol1 =  new Amplify<double>(conf);
	vol2 =  new Amplify<double>(conf);

	auto pan1 = new Pan<double>(conf);
	auto pan2 = new Pan<double>(conf);
	pan1->setPan(-0.4);
	pan2->setPan(0.8);
	auto fxchannel1 = Benchmark_p(new Sequence<double>(conf,
													   vol1,
													   pan1));

	auto fxchannel2 = Benchmark_p(new Sequence<double>(conf,
													   vol2,
													   pan2));

	auto input = Input_p(new SummationProxy<double>(
							 new InputMultiplexer<double>(conf,
														  new SfxInputProxy<double>(stereo_loop_file1,
																					fxchannel1),
														  new SfxInputProxy<double>(stereo_loop_file2,
																					fxchannel2))));


	auto zeO = new PortaudioOutput<double>(conf);
	auto output = std::shared_ptr<PortaudioOutput<double>>(zeO);

	StreamingManager<double> manager(std::move(input), std::move(output), conf);

	manager.execute();
}
