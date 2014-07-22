#ifndef CHANNELLISTWIDGET_H
#define CHANNELLISTWIDGET_H

#include <QWidget>
#include <SongData.h>

namespace Ui {
	class ChannelListWidget;
}

class ChannelWidget;

/**
 * @brief The ChannelListWidget class
 *
 * La liste des pistes
 */
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
		// Appelé lorsqu'une boite est tapée
		void switchBox(int);

		// Supprime toutes les pistes de l'interface
		void clear();

		// Remet volumes et pans à leur valeur par défaut
		void reset();

		// Charge un nouveau jeu de pistes
		void load(const SongData& s);

		// Appelés lorsqu'un paramètre change dans une des pistes
		void on_volumeChanged(int);
		void on_panChanged(int);
		void on_muteChanged(bool);
		void on_soloChanged(bool);
		void on_enablementChanged(bool); // Bouton contrôlé par les boîtes

	private:
		Ui::ChannelListWidget *ui;
};

#endif // CHANNELLISTWIDGET_H
