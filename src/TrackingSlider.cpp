#include "TrackingSlider.h"

void TrackingSlider::mousePressEvent(QMouseEvent* event)
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

void TrackingSlider::paintEvent(QPaintEvent* ev)
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
