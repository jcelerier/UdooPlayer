#ifndef CHANNELLISTWIDGET_H
#define CHANNELLISTWIDGET_H

#include <QWidget>

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
		void volume1Changed(int);
		void volume2Changed(int);

	private:
		Ui::ChannelListWidget *ui;
};

#endif // CHANNELLISTWIDGET_H
