#ifndef GRAPHICALTIMECOUNT_H
#define GRAPHICALTIMECOUNT_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
class GraphicalTimeCount : public QWidget
{

		Q_OBJECT
	public:
		explicit GraphicalTimeCount(QWidget *parent = 0);

	signals:

	public slots:
		void setMaxBeats(int num)
		{ maxBeats = num; repaint();}
		void setBeats(int num)
		{ beat = num; repaint(); }
		void setNumerator(int num)
		{ numerateur = num; }
		void setDenominator(int num)
		{ denominateur = num; }

	protected:
		void paintEvent(QPaintEvent* ) override
		{
			if(maxBeats > 0)
			{
				QPainter p{this};
				int nbSubdivs = (maxBeats * (denominateur / 4));
				int x_incr = (this->width()) / nbSubdivs;

				p.setPen(QPen(QBrush(Qt::black), 0));
				for(int i = 0; i < beat * (denominateur / 4); ++i)
				{
					p.setBrush(QBrush((!(i % numerateur) ) ?
										  Qt::darkGreen :
										  Qt::green));
					p.drawRect(i * x_incr, 10, x_incr, 19);
				}

				for(int i = 0; i <= nbSubdivs; ++i)
				{
					p.setPen((!(i % numerateur) ) ?
								 QPen(QBrush(Qt::black), 2) :
								 QPen(QBrush(Qt::black), 1));
					p.drawLine(QPoint{i * x_incr, 11}, QPoint{i * x_incr, 29});
				}

				p.drawLine(0, 10, nbSubdivs * x_incr, 10);
				p.drawLine(0, 29, nbSubdivs * x_incr, 29);
			}
		}

	private:
		int maxBeats{};
		int beat{};

		int numerateur{4};
		int denominateur{4};

};

#endif // GRAPHICALTIMECOUNT_H
