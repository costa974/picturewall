/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include "CustomProxy.h"

#include <QtGui>
#include "CustomLabel.h"

CustomProxy::CustomProxy(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsProxyWidget(parent, wFlags), popupShown(false)
{
    timeLine = new QTimeLine(1000, this);
    connect(timeLine, SIGNAL(valueChanged(qreal)),
            this, SLOT(updateStep(qreal)));
    connect(timeLine, SIGNAL(stateChanged(QTimeLine::State)),
            this, SLOT(stateChanged(QTimeLine::State)));
   connect(timeLine, SIGNAL(finished ()),
            this, SLOT(animationFinished()));	
	

	fullScreen = false;
}

QRectF CustomProxy::boundingRect() const
{
    return QGraphicsProxyWidget::boundingRect().adjusted(0, 0, 10, 10);
}


void CustomProxy::paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{

/*
    const QBrush color(QColor(0, 0, 255,0),Qt::Dense4Pattern);
   
    QRectF r = windowFrameRect();
    QRectF right(r.right(), r.top() + 10, 10, r.height() - 10);
    QRectF bottom(r.left() + 10, r.bottom(), r.width(), 10);
    bool intersectsRight = right.intersects(option->exposedRect);
    bool intersectsBottom = bottom.intersects(option->exposedRect);
    if (intersectsRight && intersectsBottom) {
        QPainterPath path;
        path.addRect(right);
        path.addRect(bottom);
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawPath(path);
	
    } else if (intersectsBottom) {
        painter->fillRect(bottom, color);
	
    } else if (intersectsRight) {
	
        painter->fillRect(right, color);
    }
*/
   // QGraphicsProxyWidget::paintWindowFrame(painter, option, widget);
    
}


void CustomProxy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{

/*
    const QColor color(255, 255, 255, 255);
   
   QRectF r = windowFrameRect();
    QRectF right(r.right(), r.top() + 10, 10, r.height() - 10);
    QRectF bottom(r.left() + 10, r.bottom(), r.width(), 10);
    bool intersectsRight = right.intersects(option->exposedRect);
    bool intersectsBottom = bottom.intersects(option->exposedRect);
    if (intersectsRight && intersectsBottom) {
        QPainterPath path;
        path.addRect(right);
        path.addRect(bottom);
        painter->setPen(Qt::NoPen);
        painter->setBrush(color);
        painter->drawPath(path);
	
    } else if (intersectsBottom) {
        painter->fillRect(bottom, color);
	
    } else if (intersectsRight) {
	
        painter->fillRect(right, color);
    }

*/

 
    QGraphicsProxyWidget::paint(painter, option, widget);
 //QGraphicsProxyWidget::paintWindowFrame(painter, option, widget);
   
}

void CustomProxy::mousePressEvent ( QGraphicsSceneMouseEvent *event )
{
	qDebug("FULL SCREEN");
	QGraphicsProxyWidget::mousePressEvent(event);
    scene()->setActiveWindow(this);
	if(fullScreen)
	{
		widget()->resize(80,80);
		fullScreen= false;
	}else
	{
		widget()->showMaximized ();
		fullScreen= true;
	}
}

void CustomProxy::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverEnterEvent(event);
    scene()->setActiveWindow(this);
    if (timeLine->currentValue() != 1)
        zoomIn();
}

void CustomProxy::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsProxyWidget::hoverLeaveEvent(event);
    if (!popupShown && (timeLine->direction() != QTimeLine::Backward || timeLine->currentValue() != 0))
        zoomOut();
}

bool CustomProxy::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    if (watched->isWindow() && (event->type() == QEvent::UngrabMouse || event->type() == QEvent::GrabMouse)) {
        popupShown = watched->isVisible();
        if (!popupShown && !isUnderMouse())
            zoomOut();
    }
    return QGraphicsProxyWidget::sceneEventFilter(watched, event);
}

QVariant CustomProxy::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemChildAddedChange || change == ItemChildRemovedChange) {
        QGraphicsItem *item = qVariantValue<QGraphicsItem *>(value);
        if (change == ItemChildAddedChange)
            item->installSceneEventFilter(this);
      //  else
       //     item->removeSceneEventFilter(this);
    }
    return QGraphicsProxyWidget::itemChange(change, value);
}

void CustomProxy::updateStep(qreal step)
{
    QRectF r = boundingRect();

	/*    setTransform(QTransform()
                 .translate(r.width() / 2, r.height() / 2)
                 .rotate(step * 30, Qt::XAxis)
                 .rotate(step * 10, Qt::YAxis)
                 .rotate(step * 5, Qt::ZAxis)
                 .scale(1 + 1.5 * step * 3, 1 + 1.5 * step * 3)
                 .translate(-r.width() / 2, -r.height() / 2));
*/

    //qDebug("emitter itemChaned %f\n",step);

		
	/*setTransform(QTransform()
                 .translate(r.width() / 2, r.height() / 2)
                 /*.rotate(step * 30, Qt::XAxis)
                 .rotate(step * 10, Qt::YAxis)
                 .rotate(step * 5, Qt::ZAxis)*/
     /*           .scale(1 + 4.5 * step , 1 + 4.5 * step )
                .translate(-r.width() / 2, -r.height() / 2));
	*/

	if(timeLine->direction() == QTimeLine::Backward)
	{
		if(this->scene()->views().at(0)->verticalScrollBar() != NULL)
		{
			this->scene()->views().at(0)->verticalScrollBar()->setValue(this->scene()->views().at(0)->verticalScrollBar()->value()+5);
		}
		this->setGeometry(QRectF(this->x() + 20,this->y()+ 20,this->geometry().width()-40,this->geometry().height()-40));
		//emit imageZoomedOut();
	}else
	{
		//emit imageZoomedIn();
		this->setGeometry(QRectF(this->x()- 20,this->y()- 20,this->geometry().width()+40,this->geometry().height()+40));
	}

	this->scene()->views().at(0)->ensureVisible(this,0,0);

	//this->setGeometry(QRectF(this->x(),this->y(),this->geometry().width()+1 + 1.5 * step ,this->geometry().height()+1 + 1.5 * step ));

}

void CustomProxy::stateChanged(QTimeLine::State state)
{
    if (state == QTimeLine::Running) {
	if (timeLine->direction() == QTimeLine::Forward)
	 setCacheMode(DeviceCoordinateCache);
         //   setCacheMode(NoCache);
    } else if (state == QTimeLine::NotRunning) {
	if (timeLine->direction() == QTimeLine::Backward)
            setCacheMode(DeviceCoordinateCache);
    }
}

void CustomProxy::zoomIn()
{
	
    if (timeLine->direction() != QTimeLine::Forward)
        timeLine->setDirection(QTimeLine::Forward);
    if (timeLine->state() == QTimeLine::NotRunning) 
        timeLine->start();

}

void CustomProxy::zoomOut()
{

    if (timeLine->direction() != QTimeLine::Backward)
        timeLine->setDirection(QTimeLine::Backward);
    if (timeLine->state() == QTimeLine::NotRunning) 
        timeLine->start();

}

void CustomProxy::animationFinished()
{
	if(timeLine->direction() == QTimeLine::Backward)
	{
		if(this->scene()->views().at(0)->verticalScrollBar() != NULL)
		{
			this->scene()->views().at(0)->verticalScrollBar()->setValue(this->scene()->views().at(0)->verticalScrollBar()->maximum());
		}
		emit imageZoomedOut();
	}

	if(timeLine->direction() == QTimeLine::Forward)
	{
		this->scene()->views().at(0)->ensureVisible(this,0,0);
		emit imageZoomedIn();
	}

}
