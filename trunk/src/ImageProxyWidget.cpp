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
#include <QPen>

#include <math.h>

CImageProxyWidget::CImageProxyWidget( QGraphicsItem * parent, Qt::WindowFlags wFlags)
 : QGraphicsProxyWidget(parent,wFlags)
{
	setReflection(false);
}


CImageProxyWidget::~CImageProxyWidget()
{
}


void CImageProxyWidget::paint ( QPainter *pPainter, const QStyleOptionGraphicsItem *pStyleOptionGraphicsItem, QWidget *pWidget )
{
	if(!this->reflection())
	{
		QPen pen;  // creates a default pen
	
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(6);
		pen.setBrush(Qt::white);
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);
		
		pPainter->setPen(pen);
	
		pPainter->drawRoundedRect(this->boundingRect().x(), this->boundingRect().y(), this->boundingRect().width(), this->boundingRect().height(), 0, 0);
	}

	   const QBrush color(QColor(0, 0, 255,0),Qt::Dense4Pattern);
   
	QGraphicsProxyWidget::paint(pPainter,pStyleOptionGraphicsItem,pWidget);
}

void CImageProxyWidget::setReflection(const bool &reflectionFlag)
{
	relectionOn = reflectionFlag;
}

bool CImageProxyWidget::reflection()
{
	return relectionOn;
}

void CImageProxyWidget::paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{



	    QGraphicsProxyWidget::paintWindowFrame(painter, option, widget);
}


void CImageProxyWidget::mousePressEvent ( QGraphicsSceneMouseEvent *event )
{
	CustomLabel *c = (CustomLabel *)this->widget();

	c->setImagePath("I Am CLICKED");

	QGraphicsProxyWidget::mousePressEvent(event);
}
