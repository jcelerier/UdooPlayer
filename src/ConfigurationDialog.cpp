#include "ConfigurationDialog.h"
#include "ui_ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent):
	QDialog(parent),
	ui(new Ui::ConfigurationDialog)
{
	ui->setupUi(this);
	ui->sensibility->setEnabledStylesheet();
	ui->sensibility->setDefaultValue(0);
	ui->sensibility->setValue(ui->sensibility->getDefaultValue());
}

ConfigurationDialog::~ConfigurationDialog()
{
	delete ui;
}

void ConfigurationDialog::accept()
{
	QDialog::accept();
	threshold = ui->sensibility->value() * 4 + 100;
	qDebug() << threshold;
}
