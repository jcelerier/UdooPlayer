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
	enable(true);
	on_enable(true); // Les signaux / slots ne sont pas encore dispos.
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
}

void ChannelWidget::mute(bool muted)
{
	ui->mute->setChecked(muted);
}

void ChannelWidget::solo(bool enabled)
{
	ui->solo->setChecked(enabled);
}

void ChannelWidget::enable(bool enabled)
{
	ui->button->setChecked(enabled);
}

bool ChannelWidget::is_enabled()
{
	return ui->button->isChecked();
}

void ChannelWidget::on_enable(bool enabled)
{
	if(enabled)
	{
		ui->volume->setEnabledStylesheet();
	}
	else
	{
		ui->volume->setDisabledStylesheet();
	}

	mute(!enabled);
}
