#include "MainWidget.h"
#include "ui_MainWidget.h"

#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	connect(ui->channelList, SIGNAL(volumeChanged(int, int)),
			&playThread,	 SLOT(setVolume(int,int)));
	connect(ui->channelList, SIGNAL(panChanged(int, int)),
			&playThread,	 SLOT(setPan(int,int)));
	connect(ui->channelList, SIGNAL(muteChanged(int,bool)),
			&playThread,	 SLOT(setMute(int,bool)));

	connect(ui->masterVolume, SIGNAL(sliderMoved(int)),
			&playThread,	  SLOT(setMasterVolume(int)));

	connect(&playThread,	&PlayThread::spentTime,
			this,			&MainWidget::updateTime);
	connect(&playThread,	&PlayThread::setTotalTime,
			this,			&MainWidget::updateTotalTime);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::play()
{
	if(!loaded) load();
	playThread.start();
}

void MainWidget::stop()
{
	if(!loaded) return;
	playThread.stop();
	prev_t = -1;
}

void MainWidget::updateTime(double t) // en secondes
{
	int time{t * getTempo() / 60.0};
	if(time != prev_t)
	{
		ui->temps->setText(QString("%1 / %2").arg(time)
											 .arg(int(m_totalTime)));
		prev_t = time;
	}
}

void MainWidget::updateTotalTime(double t) // en secondes
{
	// Ici on calcule le nombre de temps dans la boucle.
	// Formule : secondes * tempo/60 = nb. temps ds boucle.

	m_totalTime = t * getTempo() / 60.0;
	prev_t = -1;
}

void MainWidget::load()
{
	stop();
	QString file = QFileDialog::getOpenFileName(this,
												"Charger",
												QString(),
												"Musique (*.song)");
	if(!file.isEmpty())
	{
		SongData song = savemanager.load(file);
		setTempo(song.tempo);

		playThread.load(song);

		ui->channelList->clear();
		ui->channelList->load(song);
	}

	loaded = true;
}
