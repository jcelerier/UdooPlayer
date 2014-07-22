#include "ChannelListWidget.h"
#include "ui_ChannelListWidget.h"
#include "ChannelWidget.h"

#define CHANNEL_INDEX channels.indexOf(qobject_cast<ChannelWidget*>(QObject::sender()))
using namespace std;
ChannelListWidget::ChannelListWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChannelListWidget)
{
	ui->setupUi(this);

	/*
	ui->widget->setButtonColor("#FF0000");
	ui->widget_2->setButtonColor("#00FF00");
	ui->widget_3->setButtonColor("#0000FF");
	ui->widget_4->setButtonColor("#FF00FF");
	ui->widget_5->setButtonColor("#FFFF00");
	ui->widget_6->setButtonColor("#00FFFF");
	ui->widget_7->setButtonColor("#FFFFFF");
	ui->widget_8->setButtonColor("#FE9A2E");
	*/
}

ChannelListWidget::~ChannelListWidget()
{
	delete ui;
}

void ChannelListWidget::switchBox(int i)
{
	channels[i]->enable(!channels[i]->is_enabled());
}

void ChannelListWidget::clear()
{
	for(int i = 0; i < channels.size(); i++)
	{
		ui->horizontalLayout->removeWidget(channels[i]);
		delete channels[i];
	}

	channels.resize(0);
}

void ChannelListWidget::reset()
{
	for(auto& chan : channels)
	{
		chan->reset();
	}
}

void ChannelListWidget::load(const SongData& s)
{
	for(auto& track : s.tracks)
	{
		channels << new ChannelWidget(this);
		ui->horizontalLayout->addWidget(channels.last());

		connect(channels.last(), SIGNAL(volumeChanged(int)), this, SLOT(on_volumeChanged(int)));
		connect(channels.last(), SIGNAL(panChanged(int)), this, SLOT(on_panChanged(int)));
		connect(channels.last(), SIGNAL(on_mute(bool)), this, SLOT(on_muteChanged(bool)));
		connect(channels.last(), SIGNAL(on_solo(bool)), this, SLOT(on_soloChanged(bool)));
		connect(channels.last(), SIGNAL(on_enable(bool)), this, SLOT(on_enablementChanged(bool)));

		channels.last()->load(track);
	}
}

void ChannelListWidget::on_volumeChanged(int vol)
{
	emit volumeChanged(CHANNEL_INDEX, vol);
}

void ChannelListWidget::on_panChanged(int vol)
{
	emit panChanged(CHANNEL_INDEX, vol);
}

void ChannelListWidget::on_muteChanged(bool mute)
{
	if(!mute && channels[CHANNEL_INDEX]->is_enabled())
	{
		emit muteChanged(CHANNEL_INDEX, false);
	}
	else
	{
		emit muteChanged(CHANNEL_INDEX, true);
	}
}

void ChannelListWidget::on_enablementChanged(bool enabled)
{
	if(enabled && !channels[CHANNEL_INDEX]->is_mute())
	{
		emit muteChanged(CHANNEL_INDEX, false);
	}
	else
	{
		emit muteChanged(CHANNEL_INDEX, true);
	}
}

/**
 * @brief ChannelListWidget::on_soloChanged
 * @param isSoloed
 *
 * Une piste passe en solo : toutes les autre deviennent mute et non-solo, et elle devient unmute.
 * On lui enlève le solo : on entend tout.
 *
 */
void ChannelListWidget::on_soloChanged(bool isSoloed)
{
	int id = CHANNEL_INDEX;

	if(isSoloed)
	{
		for(int i = 0; i < channels.size(); i++)
		{
			if(id != i)
			{
				if(!channels[i]->is_solo())
				{
					channels[i]->mute(true);
					channels[i]->solo(false);
				}
			}
		}
		channels[id]->mute(false);
	}
	else
	{
		if(!std::any_of(begin(channels),
					   end(channels),
					   [] (ChannelWidget* chan) { return chan->is_solo(); }))
			for(int i = 0; i < channels.size(); i++)
			{
				channels[i]->mute(false);
			}
		else
			channels[id]->mute(true);
	}
}
