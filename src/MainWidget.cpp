#include "MainWidget.h"
#include "ui_MainWidget.h"

#include <QFileDialog>
#include <QMessageBox>
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

	connect(ui->masterVolume, SIGNAL(valueChanged(int)),
			&playThread,	  SLOT(setMasterVolume(int)));

	connect(&playThread,	&PlayThread::spentTime,
			this,			&MainWidget::updateBeat);
	connect(&playThread,	&PlayThread::setTotalTime,
			this,			&MainWidget::updateBeatCount);

	connect(&serialmanager,		&SerialManager::boxActivated,
			ui->channelList,	&ChannelListWidget::switchBox);

	ui->masterVolume->setDefaultValue(80);
	serialmanager.start();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::play()
{
	if(!m_loaded)
	{
		if(load()) return;
	}

	playThread.start();
	m_playing = true;
}

void MainWidget::stop()
{
	if(!m_loaded || !m_playing) return;
	playThread.stop();
	m_previousBeat = 0;
	m_playing = false;
}

void MainWidget::updateBeat(double t) // en secondes
{
	int time{t * getTempo() / 60.0 + 1};
	if(time != m_previousBeat && time <= m_beatCount)
	{
		ui->temps->setText(QString("%1 / %2").arg(time)
						   .arg(int(m_beatCount)));
		m_previousBeat = time;
	}
}

void MainWidget::updateBeatCount(double t) // en secondes
{
	// Ici on calcule le nombre de temps dans la boucle.
	// Formule : secondes * tempo/60 = nb. temps ds boucle.

	m_beatCount = t * getTempo() / 60.0;
	m_previousBeat = -1;
}

int MainWidget::load()
{
	try
	{
		stop();
		QString file = QFileDialog::getOpenFileName(this,
													"Charger",
													"/home/ubuntu/songs", // Hardcodé
													"Musique (*.song)");
		if(!file.isEmpty())
		{
			SongData song = savemanager.load(file);
			setTempo(song.tempo);

			playThread.load(song);

			ui->channelList->clear();
			ui->channelList->load(song);
			ui->masterVolume->setValue(80);
			ui->morceau->setText(QString::fromStdString(song.name));
		}

		m_loaded = true;
	}
	catch(std::exception& e)
	{
		QMessageBox::warning(this, tr("Erreur au chargement"), e.what());
		return 1;
	}

	return 0;
}
