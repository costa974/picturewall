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
#ifndef IMAGEPROXYWIDGET_H
#define IMAGEPROXYWIDGET_H

#include <QGraphicsProxyWidget>

/**
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CImageProxyWidget : public QGraphicsProxyWidget
{
Q_OBJECT
public:
    CImageProxyWidget( QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);

    ~CImageProxyWidget();

	
	void setReflection(const bool &reflectionFlag);
	bool reflection();

protected:
  virtual void paint ( QPainter *, const QStyleOptionGraphicsItem *, QWidget * );
  virtual void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);              

  virtual void mousePressEvent ( QGraphicsSceneMouseEvent *event );	

private:
	bool relectionOn;

};

#endif
