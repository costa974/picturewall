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
#ifndef MAINPICTUREWALLAREA_H
#define MAINPICTUREWALLAREA_H

#include <QGraphicsView>
#include <QtGui>


/**

	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
struct ScaledImageInfo
{
    QImage m_ScaledImage;
    QString m_ScaledImagePath;
};

/**
 	CMainPictureWallArea class is responsible for setting images on the graphics view, rendering of images, setting reflection of those images, emits events on the respective image and handling mouse events.

	CMainPictureWallArea class provides showImageOnWall() methods to create and push image object on graphics view container. This methods except bytearray data for the image or result location of QFutureWatcher class which is envoked from multiple images path which needs to processed in different thread. Once these image result is obtain.CMainPictureWallArea class places those image objects on the graphics view and set the new bounding rect for the view. This process is continu for all the images that needs to be placed inside the graphics view container.It is checked for bottom raw which has a reflection of the widget when images are places on to graphics view. if the bottom raw is third raw then one more row element is added which is reflection of the image.

	CMainPictureWallArea class provides functionality on mouse events on graphics view. When mouse wheel takes palce zoom in and zoom out of the contained images is provided inside changeZoomLevelByFactor() function. Horizontal scrolling on view on mouse pressed event is also taken care mousePressEvent() method.


	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CMainPictureWallArea : public QGraphicsView
{
    Q_OBJECT
public:
    CMainPictureWallArea(QWidget *parent = 0);

    virtual ~CMainPictureWallArea();

    /**
	EZoomFocus provides direction of the zoom on complete view 
	IN - zoom in
	OUT - zoom out
	
    */
    enum EZoomFocus
    {
        IN,
        OUT
    };

public slots:

    /**
     * This slot loads all the image path from the passed directoryPath. Loaded image path is sent to QFutureWatcher for loading all the images in concurrent.
	if diretory path does not contain any images then this function does nothing

     * @param directoryPath directory path to image folder
     */
    void loadImagesFromDirectoryRecursivelySlot(QString directoryPath);

    /**
     * This slots is called when the mouse wheel are scrolled for zoom in and zoom out event i.e. scalling of an graphics view. Depending upon the direction of zoom, scalling of entire view is done by +0.25 for zoom in and -0.25 for zoom out
     * @param zoom direction of the zoom
     */
    void changeZoomLevelByFactor(EZoomFocus zoom);

    /**
     * This slot is called when new record needs to be displayed inside the view. This slot accept URL to thumbnail view and original image URL. Thumbnail image is downloaded from the web server and send to private memeber function showImageOnWall() to attach on the view.

     * @param  result This is key value based result is expeted, key for thumbnail view URL is "tbUrl" amd key for original image viewer is "url"
     */
    void showGoogleImageResult(QHash<QString,QString> result);

    /**
     * This slot clear all the image item from the view. This slot delete each item from the view
     */
    void cleanAllResults();


private slots:
    /**
     * This slot is called internally when QFutureWatcher is finished image processing, scalling and result is obtained. passed integer parameter represent location of the result in QFutureWatcher object
     * @param num 
     */
    void showImageOnWall(int num);

    /**
     * This slot is called internally when images has downloaded from web server. Images downlaoded from web server for this funtion are thumbnail view of the main images. 
     * @param image Downloaded image data 
     * @param  URL of the main image data
     */
    void showImageOnWall(QByteArray image,QString);


protected:
    /**
     * This overloaded function provides scalling of view on mouse wheel even
     * @param  
     */
    virtual void wheelEvent ( QWheelEvent *  );


    /**
     * 
     * @param  
     */
    virtual void mousePressEvent ( QMouseEvent * );
    /**
     * 
     * @param  
     */
    virtual void mouseReleaseEvent ( QMouseEvent * );
    /**
     * This overloaded function provides horizontal scrolling of the view depending upon the mouse movement and mouse press event. 
     * @param  
     */
    virtual void mouseMoveEvent ( QMouseEvent * );


private:
    /**
     * This function sets the text message on the view at available position
     * @param text 
     */
    void setMessage(const QString &text);


private:
    QFutureWatcher<ScaledImageInfo> *m_pImageScaling;
    int m_Row;
    int m_Column;
    QGraphicsScene m_GraphicsScene;
    qreal m_ZoomFactor;
    int m_MouseDeltaValueForPressedEvent;
    bool m_MouseButtonPressed;
};

#endif


