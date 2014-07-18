#ifndef CHANNELLISTWIDGET_H
#define CHANNELLISTWIDGET_H

#include <QWidget>
#include <SongData.h>

namespace Ui {
	class ChannelListWidget;
}

class ChannelWidget;

class ChannelListWidget : public QWidget
{
		Q_OBJECT

	public:
		QVector<ChannelWidget*> channels;
		explicit ChannelListWidget(QWidget *parent = 0);
		~ChannelListWidget();

	signals:
		void volumeChanged(int, int);
		void panChanged(int, int);
		void muteChanged(int, bool);

	public slots:
		void switchBox(int );

		// Supprime toutes les pistes de l'interface
		void clear();

		// Charge un nouveau jeu de pistes
		void load(SongData s);

		void on_volumeChanged(int);
		void on_panChanged(int);
		void on_muteChanged(bool);
		void on_soloChanged(bool);

	private:
		Ui::ChannelListWidget *ui;
};

#endif // CHANNELLISTWIDGET_H
