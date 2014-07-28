#include "TrackingSlider.h"

void TrackingSlider::setEnabledStylesheet()
{
	QFile file;
	if(orientation() == Qt::Vertical)
	{
		file.setFileName(":/qss/TrackingSliderVerticalEnabled.qss");
	}
	else
	{
		file.setFileName(":/qss/TrackingSliderHorizontalEnabled.qss");
	}
	file.open(QFile::ReadOnly);
	setStyleSheet(file.readAll());
	ensurePolished();
}

void TrackingSlider::setSoloStylesheet()
{
	QFile file;
	if(orientation() == Qt::Vertical)
	{
		file.setFileName(":/qss/TrackingSliderVerticalSolo.qss");
	}
	else
	{
		file.setFileName(":/qss/TrackingSliderHorizontalSolo.qss");
	}
	file.open(QFile::ReadOnly);
	setStyleSheet(file.readAll());
	ensurePolished();
}

void TrackingSlider::setDisabledStylesheet()
{
	QFile file;
	if(orientation() == Qt::Vertical)
	{
		file.setFileName(":/qss/TrackingSliderVerticalDisabled.qss");
	}
	else
	{
		file.setFileName(":/qss/TrackingSliderHorizontalDisabled.qss");
	}

	file.open(QFile::ReadOnly);
	setStyleSheet(file.readAll());
	ensurePolished();
}

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
