#include "TrackingSlider.h"
#include <QStyle>
#include <QStyleOptionSlider>

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
#include<QDebug>

// http://qt-project.org/faq/answer/how_can_i_draw_custom_subcontrols_for_a_complex_control
// http://stackoverflow.com/questions/17101378/coloring-qslider-for-particular-range
// https://libav.org/download.html
void TrackingSlider::paintEvent(QPaintEvent* ev)
{
	int h = this->size().height();
	int w = this->size().width();


	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	if (orientation() == Qt::Vertical)
	{
		int hpos = QStyle::sliderPositionFromValue(minimum(), maximum(), 79, h, true) + 800 / h;
		painter.drawLine(26, hpos, w, hpos);

		//painter.setFont(QFont("Sans", 9));
		//painter.drawText(w - 12, hpos + 4, "0dB");
		//painter.setFont(QFont("Sans", 14));
		//painter.drawText(0, this->size().height() , "-∞");
	}
	else
	{
		int wpos = QStyle::sliderPositionFromValue(minimum(), maximum(), 79, w) - 1000 / w;
		painter.drawLine(wpos, 20, wpos, 75);

		//painter.setFont(QFont("Sans", 9));
		//painter.drawText(wpos - 14, 10, "0dB");
		//painter.setFont(QFont("Sans", 14));
		//painter.drawText(0, this->size().height() , "-∞");
	}
	//style()->drawComplexControl(QStyle::CC_Slider, &option, &painter, this);

	QSlider::paintEvent(ev);
}
