#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	connect(ui->widget, SIGNAL(volume1Changed(int)), &playThread, SLOT(setVol1(int)));
	connect(ui->widget, SIGNAL(volume2Changed(int)), &playThread, SLOT(setVol2(int)));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::play()
{
	playThread.start();
}
