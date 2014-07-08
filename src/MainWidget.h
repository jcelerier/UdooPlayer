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
		Q_PROPERTY(int tempo READ getTempo WRITE setTempo)

		friend class SaveManager;
	public:
		explicit MainWidget(QWidget *parent = 0);
		~MainWidget();

		int getTempo() const
		{
			return m_tempo;
		}

	public slots:
		void play();
		void load();
		void stop();

		void updateTime(double);

		void updateTotalTime(double t);
		void setTempo(int arg)
		{
			m_tempo = arg;
		}

	private:
		Ui::MainWidget *ui;
		PlayThread playThread;
		SaveManager savemanager;
		int m_tempo{};
		double m_totalTime{};
		int prev_t{-1};

		bool loaded{false};
};

#endif // MAINWIDGET_H
