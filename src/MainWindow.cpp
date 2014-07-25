#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionReset, SIGNAL(triggered()), ui->centralWidget, SLOT(reset()));
	connect(ui->actionConfiguration, SIGNAL(triggered()), ui->centralWidget, SIGNAL(openConfDialog()));
	//this->showFullScreen();
}

MainWindow::~MainWindow()
{
	delete ui;
}
