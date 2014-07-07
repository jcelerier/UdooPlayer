#ifndef TRACKINGSLIDER_H
#define TRACKINGSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

class TrackingSlider : public QSlider
{
		Q_OBJECT
		Q_PROPERTY(int defaultValue READ getDefaultValue WRITE setDefaultValue)
	public:
		using QSlider::QSlider;

		int getDefaultValue() const
		{
			return m_defaultValue;
		}

	public slots:
		void setDefaultValue(int arg)
		{
			m_defaultValue = arg;
		}

	protected:
		void mousePressEvent ( QMouseEvent * event )
		{
			if (event->button() == Qt::LeftButton)
			{
				if (orientation() == Qt::Vertical)
							setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
						else
							setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;


				event->accept();
			}

			QSlider::mousePressEvent(event);

			if(event->type() == QEvent::MouseButtonDblClick)
			{
				setValue(getDefaultValue());
			}
		}


		void paintEvent(QPaintEvent* ev)
		{
			QSlider::paintEvent(ev);

			int h = this->size().height() * 0.21;
			int w = this->size().width();

			QPainter painter(this);

			painter.setRenderHint(QPainter::Antialiasing);



			painter.drawLine(26, h, w, h);

			painter.setFont(QFont("Sans", 9));
			painter.drawText(0, h + 4, "0dB");
			painter.setFont(QFont("Sans", 14));
			painter.drawText(0, this->size().height() , "-∞");
		}

	private:
		int m_defaultValue;
};


class PanSlider : public TrackingSlider
{
		Q_OBJECT

	public:
		using TrackingSlider::TrackingSlider;


	protected:
		void paintEvent(QPaintEvent* ev)
		{
			QSlider::paintEvent(ev);

			int h = this->size().height();
			int w = this->size().width();

			QPainter painter(this);

			painter.setRenderHint(QPainter::Antialiasing);


			painter.drawLine(w/2, 15, w/2, h);

			painter.setFont(QFont("Sans", 9));

			painter.drawText(2, 10, "L");
			painter.drawText(w/2 - 4, 10, "C");
			painter.drawText(w - 8, 10, "R");
		}
};

#endif // TRACKINGSLIDER_H
