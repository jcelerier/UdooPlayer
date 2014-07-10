#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>
#include <SongData.h>

namespace Ui {
	class ChannelWidget;
}

class ChannelListWidget;
class ChannelWidget : public QWidget
{
		Q_OBJECT
		friend class ChannelListWidget;
	public:
		explicit ChannelWidget(QWidget *parent = 0);
		~ChannelWidget();

		// Change la couleur du PushButton
		void setButtonColor(QString);

		// Charge une piste
		void load(TrackData track);

		// Active / désactive mute
		void mute(bool);

		// Active / désactive solo
		void solo(bool);

	signals:
		void volumeChanged(int);
		void panChanged(int);

		void on_mute(bool);
		void on_solo(bool);

	private:
		Ui::ChannelWidget *ui;
};

#endif // CHANNELWIDGET_H
