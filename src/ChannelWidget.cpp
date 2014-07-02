#include "ChannelWidget.h"
#include "ui_ChannelWidget.h"

ChannelWidget::ChannelWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChannelWidget)
{
	ui->setupUi(this);
	connect(ui->verticalSlider, SIGNAL(sliderMoved(int)), this, SIGNAL(volumeChanged(int)));
}

ChannelWidget::~ChannelWidget()
{
	delete ui;
}

void ChannelWidget::setButtonColor(QString hex)
{
	ui->pushButton->setStyleSheet("background-color: " + hex);
}
