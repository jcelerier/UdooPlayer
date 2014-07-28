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
			this,		SLOT(slot_mute(bool)));

	connect(ui->solo,	SIGNAL(toggled(bool)),
			this,		SIGNAL(on_solo(bool)));

	ui->volume->setDefaultValue(80);
	ui->pan->setDefaultValue(0);
	enable(false);
	slot_enable(false); // Les signaux / slots ne sont pas encore dispos.
}

ChannelWidget::~ChannelWidget()
{
	delete ui;
}

void ChannelWidget::setButtonColor(const QString hex)
{
	ui->button->setStyleSheet("background-color: " + hex);
}

void ChannelWidget::load(const TrackData& track)
{
	QString buttonName{track.name.c_str()};
	if(buttonName.length() >= 8)
		buttonName.insert(buttonName.length() / 2, "-\n");
	else if(buttonName.length() < 6)
		ui->button->setFont(QFont("Sans", 13));

	ui->button->setText(buttonName);
	ui->pan->setValue(track.pan);
	ui->volume->setValue(track.volume);

	enable(false);
	slot_enable(false);
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

bool ChannelWidget::is_enabled() const
{
	return ui->button->isChecked();
}

void ChannelWidget::slot_enable(bool enabled)
{
	if(!is_solo())
	{
		if(enabled)
		{
			ui->volume->setEnabledStylesheet();
		}
		else
		{
			ui->volume->setDisabledStylesheet();
		}


		emit on_enable(enabled);
	}
}
void ChannelWidget::slot_solo(bool soloed)
{
	if(soloed)
	{
		ui->volume->setSoloStylesheet();
	}
	else
	{
		if(is_enabled())
		{
			ui->volume->setEnabledStylesheet();
		}
		else
		{
			ui->volume->setDisabledStylesheet();
		}
	}
}

void ChannelWidget::slot_mute(bool muted)
{
	if(is_solo())
		ui->mute->setChecked(false);
	else
		emit on_mute(muted);
}

void ChannelWidget::setVolume(int vol)
{
	if(vol != ui->volume->value())
	{
		ui->volume->setValue(vol);
	}
}


bool ChannelWidget::is_solo() const
{
	return ui->solo->isChecked();
}

bool ChannelWidget::is_mute() const
{
	return ui->mute->isChecked();
}

void ChannelWidget::reset()
{
	ui->volume->setValue(ui->volume->getDefaultValue());
	ui->pan->setValue(ui->pan->getDefaultValue());
	solo(false);
	mute(false);
	enable(false);
}

