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
#include <QTimeLine>
/**
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CImageProxyWidget : public QGraphicsProxyWidget
{
Q_OBJECT
public:
    CImageProxyWidget( QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);

    virtual ~CImageProxyWidget();

	
   QRectF boundingRect() const;

    void setDefaultItemGeometry(const QRectF &geometry);	

protected:
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);                          
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent ( QGraphicsSceneMouseEvent *event );	
    void closeEvent ( QCloseEvent * event ); 

private slots:
    void updateStep(int step);
    void stateChanged(QTimeLine::State);
    void zoomIn();
    void zoomOut();
    void animationFinished();

signals:
    void imageZoomedIn();
    void imageZoomedOut();

private:
    QTimeLine *m_pTimeLineForImageZoomAnimation;
    bool popupShown;
    QRectF m_ItemGeometry;

};

#endif
