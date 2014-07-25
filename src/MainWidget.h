#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayThread.h"
#include "SaveManager.h"
#include "SerialManager.h"
#include "ConfigurationDialog.h"
#include "osc/oscreceiver.h"
#include <exception>

namespace Ui {
	class MainWidget;
}

class SaveManager;
/**
 * @brief The MainWidget class
 *
 * L'écran principal
 */
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

		void handle__box_enable(osc::ReceivedMessageArgumentStream args);
		void handle__box_volume(osc::ReceivedMessageArgumentStream args);

	signals:
		void openConfDialog();

	public slots:
		// Remet les paramètres à zéro
		void reset();

		// Active / désactive une boite
		void switchBox(int, int);

		// Lance la lecture
		void play();

		// Charge un morceau
		int load();

		// Sauve les modifications
		void save();

		// S'arrête
		void stop();

		// Met à jour le temps actuel affiché (ex. 13 / 32)
		void updateBeat(double);

		// Met à jour le temps total (ex. 32)
		void updateBeatCount(double t);

		// Définit le tempo
		void setTempo(int arg)
		{
			m_tempo = arg;
		}

	private:
		Ui::MainWidget *ui;
		PlayThread playThread;
		SaveManager savemanager;
		SerialManager serialmanager{this};
		ConfigurationDialog confdialog{this};
		OscReceiver oscReceiver{9988};

		SongData song;

		QString currentFile{};

		int m_tempo{};
		double m_beatCount{};

		// Optimisation : on compare avec le temps précédent.
		int m_previousBeat{-1};

		// Indique si un morceau a été chargé.
		bool m_loaded{false};

		// Indique si un morceau est en cours de lecture
		bool m_playing{false};
};

#endif // MAINWIDGET_H
