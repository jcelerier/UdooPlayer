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
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::play()
{
	playThread.start();
}

void MainWidget::stop()
{
	playThread.stop();
}

void MainWidget::load()
{
	QString file = QFileDialog::getOpenFileName(this,
												"Charger",
												QString(),
												"Data file (*.ini)");
	if(!file.isEmpty())
	{
		SongData song = savemanager.load(file);

		playThread.load(song);

		ui->channelList->clear();
		ui->channelList->load(song);
	}

}
