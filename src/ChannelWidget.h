#ifndef CHANNELWIDGET_H
#define CHANNELWIDGET_H

#include <QWidget>

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

	void setButtonColor(QString);

	signals:
		void volumeChanged(int);

	private:
		Ui::ChannelWidget *ui;
};

#endif // CHANNELWIDGET_H
