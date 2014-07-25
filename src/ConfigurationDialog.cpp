#include "ConfigurationDialog.h"
#include "ui_ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent):
	QDialog(parent),
	ui(new Ui::ConfigurationDialog)
{
	ui->setupUi(this);
	ui->sensibility->setEnabledStylesheet();
	ui->sensibility->setDefaultValue(0);
	ui->sensibility->setValue(settings.value("Global/Sensibility").toInt());

	setThreshold();
}

ConfigurationDialog::~ConfigurationDialog()
{
	delete ui;
}

void ConfigurationDialog::setThreshold()
{
	threshold = (99 - ui->sensibility->value()) * 4 + 100;
}

void ConfigurationDialog::accept()
{
	QDialog::accept();
	setThreshold();

	settings.setValue("Global/Sensibility", ui->sensibility->value());
	settings.sync();
}
