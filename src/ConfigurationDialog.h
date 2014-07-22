#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
	class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit ConfigurationDialog(QWidget *parent = 0);
		~ConfigurationDialog();

		int threshold{100};

	public slots:
		void accept();

	private:
		Ui::ConfigurationDialog *ui;
};

#endif // CONFIGURATIONDIALOG_H
