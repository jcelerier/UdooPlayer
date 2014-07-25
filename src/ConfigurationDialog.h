#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSettings>

namespace Ui {
	class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit ConfigurationDialog(QWidget *parent = 0);
		~ConfigurationDialog();

		void setThreshold();
		int threshold{100};

	public slots:
		void accept();

	private:
		Ui::ConfigurationDialog *ui;
		QSettings settings{"Rock et Chansons", "Boites Musicales"};
};

#endif // CONFIGURATIONDIALOG_H
