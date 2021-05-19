#include "QLabelEx.h"

QLabelEx::QLabelEx(QWidget* parent)
	: QLabel(parent)
{
}

QLabelEx::~QLabelEx()
{
}

void QLabelEx::enableDebug(bool debug)
{
	m_debug = debug;
}

void QLabelEx::getCoordinate(QVector<QPoint>* start, QVector<QPoint>* end)
{
	*start = m_startCoord;
	*end = m_endCoord;
}

void QLabelEx::clearCoordinate()
{
	m_startCoord.clear();
	m_endCoord.clear();
}

void QLabelEx::mousePressEvent(QMouseEvent* event)
{
	if (!m_debug)
	{
		return;
	}

	if (event->button() == Qt::LeftButton)
	{
		m_startX = event->pos().x();
		m_startY = event->pos().y();
		QCursor cursor;
		cursor.setShape(Qt::ClosedHandCursor);
		QApplication::setOverrideCursor(cursor);
		m_press = false;
	}
}

void QLabelEx::mouseReleaseEvent(QMouseEvent* event)
{
	if (!m_debug)
	{
		return;
	}

	if (event->button() == Qt::LeftButton)
	{
		m_endX = event->pos().x();
		m_endY = event->pos().y();
		QApplication::restoreOverrideCursor();
		//if (m_endX - m_startX <= 10 || m_endY - m_startY <= 10)
		//{
		//	return;
		//}
		m_startCoord.push_back(QPoint(m_startX, m_startY));
		m_endCoord.push_back(QPoint(m_endX, m_endY));

		update();
	}

	if (event->button() == Qt::RightButton)
	{
		if (m_startCoord.size() && m_endCoord.size())
		{
			m_press = true;
			m_startCoord.pop_back();
			m_endCoord.pop_back();
			update();
		}
	}

}

void QLabelEx::mouseMoveEvent(QMouseEvent* event)
{
	if (!m_debug)
	{
		return;
	}

	if ((event->buttons() & Qt::LeftButton))
	{
		m_endX = event->pos().x();
		m_endY = event->pos().y();
		update();
	}
}

void QLabelEx::paintEvent(QPaintEvent* event)
{
	QLabel::paintEvent(event);

	if (!m_debug)
	{
		return;
	}

	QPainter painter(this);
	painter.setPen(QPen(Qt::red, 1));
	for (int i = 0; i < m_endCoord.size(); i++)
	{
		painter.drawRect(QRect(m_startCoord.at(i).x(), m_startCoord.at(i).y(),
			m_endCoord.at(i).x() - m_startCoord.at(i).x(), m_endCoord.at(i).y() - m_startCoord.at(i).y()));
	}

	if (!m_press)
	{
		painter.drawRect(QRect(m_startX, m_startY, m_endX - m_startX, m_endY - m_startY));
	}
}
