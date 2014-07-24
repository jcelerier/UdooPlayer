#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>
#include <SongData.h>

namespace Ui {
	class ChannelWidget;
}

class ChannelListWidget;
/**
 * @brief The ChannelWidget class
 *
 * Une piste
 */
class ChannelWidget : public QWidget
{
		Q_OBJECT
		friend class ChannelListWidget;
	public:
		Ui::ChannelWidget *ui;

		explicit ChannelWidget(QWidget *parent = 0);
		~ChannelWidget();

		// Change la couleur du PushButton
		void setButtonColor(const QString);

		// Charge une piste
		void load(const TrackData& track);

		// Active / désactive mute
		void mute(bool);

		// Active / désactive solo
		void solo(bool);

		// Quand on active / désactive avec les boites
		void enable(bool);

		// Renvoie vrai si la boite est en mode "ON"
		bool is_enabled() const;

		// Renvoie vrai si solo est activé
		bool is_solo() const;

		// Renvoie vrai si mute est activé
		bool is_mute() const;

		// Remet volume et pan par défaut
		void reset();

	signals:
		void volumeChanged(int);
		void panChanged(int);

		void on_mute(bool);
		void on_solo(bool);
		void on_enable(bool);

	public slots:
		// Appelé lorsqu'on tape sur la boite
		void slot_enable(bool);

		void setVolume(int vol);

};

#endif // CHANNELWIDGET_H
