#ifndef TRACKINGSLIDER_H
#define TRACKINGSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QPainter>

/**
 * @brief The TrackingSlider class
 *
 * Slider vertical personnalisé
 */
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

		virtual void setEnabledStylesheet()
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

		virtual void setDisabledStylesheet()
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

	public slots:
		void setDefaultValue(int arg)
		{
			m_defaultValue = arg;
		}

	protected:
		// Réimplémenté pour suivre le doigt
		void mousePressEvent ( QMouseEvent * event );

		// Réimplémenté pour afficher la petite barre à 0dB et le -oo
		void paintEvent(QPaintEvent* ev);

	private:
		int m_defaultValue;
};


// Slider horizontal encore plus personnalisé
class PanSlider : public TrackingSlider
{
		Q_OBJECT

	public:
		using TrackingSlider::TrackingSlider;

	protected:
		// Réimplémenté pour afficher la petite barre au milieu et L, C, R
		void paintEvent(QPaintEvent* ev)
		{
			int h = this->size().height();
			int w = this->size().width();

			QPainter painter(this);

			painter.setRenderHint(QPainter::Antialiasing);


			painter.drawLine(w/2, 15, w/2, h);

			painter.setFont(QFont("Sans", 9));

			painter.drawText(2, 10, "L");
			painter.drawText(w/2 - 4, 10, "C");
			painter.drawText(w - 8, 10, "R");
			QSlider::paintEvent(ev);
		}
};

#endif // TRACKINGSLIDER_H
