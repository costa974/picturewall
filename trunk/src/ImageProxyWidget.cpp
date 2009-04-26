/***************************************************************************
 *   Copyright (C) 2009 by vishwajeet   *
 *   vishwajeet.dusane@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "ImageProxyWidget.h"
#include "CustomLabel.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>

#include <math.h>

CImageProxyWidget::CImageProxyWidget( QGraphicsItem * parent, Qt::WindowFlags wFlags)
 : QGraphicsProxyWidget(parent,wFlags),popupShown(false)
{
    m_pTimeLineForImageZoomAnimation = new QTimeLine(500, this);
    connect(m_pTimeLineForImageZoomAnimation, SIGNAL(frameChanged(int)),
            this, SLOT(updateStep(int)));
    connect(m_pTimeLineForImageZoomAnimation, SIGNAL(stateChanged(QTimeLine::State)),
            this, SLOT(stateChanged(QTimeLine::State)));
   connect(m_pTimeLineForImageZoomAnimation, SIGNAL(finished ()),
            this, SLOT(animationFinished()));	
	
   m_pTimeLineForImageZoomAnimation->setFrameRange(13,90);


	
}

CImageProxyWidget::~CImageProxyWidget()
{
	delete m_pTimeLineForImageZoomAnimation;

}


QRectF CImageProxyWidget::boundingRect() const
{
    return QGraphicsProxyWidget::boundingRect().adjusted(0, 0, 0, 0);

}


void CImageProxyWidget::paintWindowFrame(QPainter *, const QStyleOptionGraphicsItem *,
                                   QWidget *)
{

}

void CImageProxyWidget::closeEvent ( QCloseEvent * event )
{
	event->ignore();
}

void CImageProxyWidget::mousePressEvent ( QGraphicsSceneMouseEvent *event )
{
  if(event->button() != Qt::LeftButton)	
  {	
	return;	
  }
    scene()->setActiveWindow(this);
    if(!popupShown)	
    {
	if (m_pTimeLineForImageZoomAnimation->currentValue() != 1)
		zoomIn();
    }else
    {
	zoomOut();
    }		
}

void CImageProxyWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverEnterEvent(event);
}

void CImageProxyWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverLeaveEvent(event);

    if (popupShown && (m_pTimeLineForImageZoomAnimation->direction() != QTimeLine::Backward || m_pTimeLineForImageZoomAnimation->currentValue() != 0))
        zoomOut();
}


void CImageProxyWidget::setDefaultItemGeometry(const QRectF &geometry)
{
		m_ItemGeometry = geometry;
}


void CImageProxyWidget::updateStep(int step)
{
    QRectF r = boundingRect();

	qreal newWidth = this->scene()->views().at(0)->geometry().width() * step / 100; 
	qreal newHeight = this->scene()->views().at(0)->geometry().height() * step / 100;

	if(m_pTimeLineForImageZoomAnimation->direction() == QTimeLine::Backward)
	{
		if(this->scene()->views().at(0)->verticalScrollBar() != NULL)
		{
			this->scene()->views().at(0)->verticalScrollBar()->setValue(this->scene()->views().at(0)->verticalScrollBar()->value()+5);
		}

		this->setGeometry(QRectF(this->geometry().x() + 30.5,this->geometry().y()+ 10.5,newWidth,newHeight));
		emit imageZoomedOut();
	}else
	{
		this->setGeometry(QRectF(this->geometry().x() - 30.5,this->geometry().y()- 10.5,newWidth,newHeight));
	}

	this->scene()->setSceneRect(this->scene()->itemsBoundingRect());
	this->scene()->views().at(0)->ensureVisible(this,0,0);
}

void CImageProxyWidget::stateChanged(QTimeLine::State state)
{
    if (state == QTimeLine::Running) {
	if (m_pTimeLineForImageZoomAnimation->direction() == QTimeLine::Forward)
	 setCacheMode(DeviceCoordinateCache);
    } else if (state == QTimeLine::NotRunning) {
	if (m_pTimeLineForImageZoomAnimation->direction() == QTimeLine::Backward)
            setCacheMode(DeviceCoordinateCache);
    }
}

void CImageProxyWidget::zoomIn()
{

popupShown =true;		
    if (m_pTimeLineForImageZoomAnimation->direction() != QTimeLine::Forward)
        m_pTimeLineForImageZoomAnimation->setDirection(QTimeLine::Forward);
    if (m_pTimeLineForImageZoomAnimation->state() == QTimeLine::NotRunning) 
        m_pTimeLineForImageZoomAnimation->start();

}

void CImageProxyWidget::zoomOut()
{
popupShown =false;
    if (m_pTimeLineForImageZoomAnimation->direction() != QTimeLine::Backward)
        m_pTimeLineForImageZoomAnimation->setDirection(QTimeLine::Backward);
    if (m_pTimeLineForImageZoomAnimation->state() == QTimeLine::NotRunning) 
        m_pTimeLineForImageZoomAnimation->start();

}

void CImageProxyWidget::animationFinished()
{
	if(m_pTimeLineForImageZoomAnimation->direction() == QTimeLine::Backward)
	{
		if(this->scene()->views().at(0)->verticalScrollBar() != NULL)
		{
			this->scene()->views().at(0)->verticalScrollBar()->setValue(this->scene()->views().at(0)->verticalScrollBar()->maximum());
		}
		emit imageZoomedOut();
			this->setGeometry(m_ItemGeometry);
	}

	if(m_pTimeLineForImageZoomAnimation->direction() == QTimeLine::Forward)
	{
		this->scene()->setSceneRect(this->scene()->itemsBoundingRect());
		this->scene()->views().at(0)->ensureVisible(this,0,0);
		emit imageZoomedIn();
	}

}
