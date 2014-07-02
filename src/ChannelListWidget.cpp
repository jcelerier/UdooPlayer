#include "ChannelListWidget.h"
#include "ui_ChannelListWidget.h"



ChannelListWidget::ChannelListWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChannelListWidget)
{
	ui->setupUi(this);

	ui->widget->setButtonColor("#FF0000");
	ui->widget_2->setButtonColor("#00FF00");
	ui->widget_3->setButtonColor("#0000FF");
	ui->widget_4->setButtonColor("#FF00FF");
	ui->widget_5->setButtonColor("#FFFF00");
	ui->widget_6->setButtonColor("#00FFFF");
	ui->widget_7->setButtonColor("#FFFFFF");
	ui->widget_8->setButtonColor("#FE9A2E");

	connect(ui->widget, SIGNAL(volumeChanged(int)), this, SIGNAL(volume1Changed(int)));
	connect(ui->widget_2, SIGNAL(volumeChanged(int)), this, SIGNAL(volume2Changed(int)));
}

ChannelListWidget::~ChannelListWidget()
{
	delete ui;
}
