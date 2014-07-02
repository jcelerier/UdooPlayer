#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayThread.h"

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit MainWidget(QWidget *parent = 0);
		~MainWidget();

	public slots:
		void play();
	private:
		Ui::MainWidget *ui;
		PlayThread playThread;
};

#endif // MAINWIDGET_H
