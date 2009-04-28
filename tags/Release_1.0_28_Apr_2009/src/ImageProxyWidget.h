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
	CImageProxyWidget class is responsible for all the animation inside graphics window. CImageProxyWidget class is container class for CustomLabel class. CImageProxyWidget provides overloaded functions for certain mouse events like mouse pressed event on item. CImageProxyWidget class provides functionality to zoom in and zoom out of an image on mouse pressed event.



	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CImageProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    CImageProxyWidget( QGraphicsItem * parent = 0, Qt::WindowFlags wFlags = 0);

    virtual ~CImageProxyWidget();


    /**
     *
     * @return bounding rect of an set widget
     */
    QRectF boundingRect() const;

    /**
     * This function set the default geometry of an item. that is thumbnail view geometry of and item.This geometry is used when item is zoomed out and needs to be placed in the same position from where it has statrted animating.

     * @param geometry default thumbnail geometry of an item
     */
    void setDefaultItemGeometry(const QRectF &geometry);

protected:
    /**
     * This function is responsible for image widget displayed inside graphics view without frame. If this function is disabled then image widget will be displayed with default frame around it. As this functoion just blocks parent paintWindowFrame call and avoid painting of the same frame. As widget set on this proxyWidget is QDialog, this function is getting call. When widget that has Qt::FramelessWindowHint option set then paint() method will be called for every paint event. But setting up Qt::FramelessWindowHint option on widget leads to overlapping of 1 widget to other on zoom in and zoom out event.


     * @param painter
     * @param option
     * @param widget
     */
    void paintWindowFrame(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    /**
     * This overloaded function gets called whenever mouse leaves the widget area. This function takes care of zoomed in images to put back to its original place when mouse leaves from the widget area.

     * @param event
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    /**
     * This overloaded function gets called whenever mouse press event occurs on the widget. This function is resonsible for starting zoom in effect on the pressed widget.
     * @param event
     */
    void mousePressEvent ( QGraphicsSceneMouseEvent *event );
    /**
     * This overloaded function gets called whenever there is widget close events occurs. This class is responsible for ignoring such a event on widget.
     * @param event
     */
    void closeEvent ( QCloseEvent * event );

private slots:
    /**
     * This slot is called on regular intervals by QTimeLine class object. This slot provides a zoom in and zoom out animation on the pressed widget
     * @param step is the current frame number that needs to be displayed.
     */
    void updateStep(int step);
    /**
     * This slot is called whenever there is state chenges in zoom in and zoom out animation. State of the animation is weather it is running,paused or not running. When the state of the animation is changed then this function does cache on the contents of the widget.
     * @param  state of the animation
     */
    void stateChanged(QTimeLine::State);
    /**
     * This slot is called for zoom in animation on the widget. This slot will start animation in forward direction.
    @see zoomOut
     */
    void zoomIn();
    /**
     * This slot is called for zoom out animation on the widget. This slot will start animation in backword direction.

    @see zoomIn
     */
    void zoomOut();
    /**
     * This slot emits imageZoomedIn() and imageZoomedOut() signals depending upon the animation type i.e. zoomIn() ot zoomOut()
     */
    void animationFinished();

signals:
    /**
     * This singal is emiited when zoom in event occurs on the widget

    @see imageZoomedOut()
     */
    void imageZoomedIn();
    /**
     * This singal is emiited when zoom out event occurs on the widget
    @see imageZoomedIn()
     */
    void imageZoomedOut();

private:
    QTimeLine *m_pTimeLineForImageZoomAnimation;
    bool popupShown;
    QRectF m_ItemGeometry;

};

#endif
