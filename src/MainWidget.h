#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayThread.h"
#include <SaveManager.h>

namespace Ui {
	class MainWidget;
}

class SaveManager;
class MainWidget : public QWidget
{
		Q_OBJECT
	friend class SaveManager;
	public:
		explicit MainWidget(QWidget *parent = 0);
		~MainWidget();

	public slots:
		void play();
		void load();

		void stop();
	private:
		Ui::MainWidget *ui;
		PlayThread playThread;
		SaveManager savemanager;
};

#endif // MAINWIDGET_H
