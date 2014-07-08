#include "ChannelWidget.h"
#include "ui_ChannelWidget.h"
#include <QDebug>

ChannelWidget::ChannelWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChannelWidget)
{
	ui->setupUi(this);

	connect(ui->volume, SIGNAL(valueChanged(int)),
			this,		SIGNAL(volumeChanged(int)));

	connect(ui->pan,	SIGNAL(valueChanged(int)),
			this,		SIGNAL(panChanged(int)));

	connect(ui->mute,	SIGNAL(toggled(bool)),
			this,		SIGNAL(on_mute(bool)));

	connect(ui->solo,	SIGNAL(clicked(bool)),
			this,		SIGNAL(on_solo(bool)));

	ui->volume->setDefaultValue(80);
	ui->pan->setDefaultValue(0);
}

ChannelWidget::~ChannelWidget()
{
	delete ui;
}

void ChannelWidget::setButtonColor(QString hex)
{
	ui->button->setStyleSheet("background-color: " + hex);
}

void ChannelWidget::load(TrackData track)
{
	ui->button->setText(track.name.c_str());
	ui->pan->setValue(track.pan);
	ui->volume->setValue(track.volume);
	qDebug() << track.volume;
}

void ChannelWidget::mute(bool muted)
{
	ui->mute->setChecked(muted);
}

void ChannelWidget::solo(bool enabled)
{
	ui->solo->setChecked(enabled);
}
