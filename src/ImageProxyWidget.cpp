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

	QPen pen;  // creates a default pen

	pen.setStyle(Qt::SolidLine);
	pen.setWidth(3);
	pen.setBrush(Qt::white);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	
	pPainter->setPen(pen);

	pPainter->drawRoundedRect(this->boundingRect().x(), this->boundingRect().y(), this->boundingRect().width(), this->boundingRect().height(), 0, 0);


	if(relectionOn)
	{
		double pi = 3.14159;
		double a    = (pi/180.0) * 180.0;
		double sina = sin(2.0*a);
		double cosa = cos(2.0*a);
		int reflexLgh =0;

		QColor colorBg = Qt::black;
		QColor colorTx = Qt::white;
		QColor reflexColorBg = Qt::green;;
		QColor reflexColorBord ;
		QColor reflexColorFst;
		QColor reflexColorSnd;
		QColor reflexColorTx;

		int alphaFst =20;
		int alphaSnd =120 ;
		int alphaTxt =100 ;
		int sizeTx = 0;

		QTransform reflex(cosa, sina, sina, cosa, 0, 0);
		pPainter->setTransform(reflex);
		pPainter->shear(0, 0.5);
		
		
		QLinearGradient linGrad2(0, -15-reflexLgh, 0, -5-(reflexLgh/2));
		reflexColorFst = colorBg;
		reflexColorSnd = colorBg;
		reflexColorBord = colorBg;
		reflexColorFst.setAlpha(alphaFst);
		reflexColorSnd.setAlpha(alphaSnd);
		reflexColorBord.setAlpha(10);
		reflexColorTx = colorTx;
		reflexColorTx.setAlpha(alphaTxt);
		
		linGrad2.setColorAt(0, reflexColorFst);
		linGrad2.setColorAt(1, reflexColorSnd);
		linGrad2.setSpread(QGradient::PadSpread);
		pPainter->setBrush(linGrad2);
		pPainter->setPen(QPen(reflexColorBord));
		pPainter->drawRect(this->x(), this->y(), this->boundingRect().width()+80, this->boundingRect().height()+15+reflexLgh);

		QRectF R2 (this->x(), this->y(), this->boundingRect().width()+80, this->boundingRect().height()+15+reflexLgh);
		pPainter->setPen(QPen(reflexColorTx));
		pPainter->drawText(R2, Qt::AlignCenter, "Vishwajeet");
	}


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

