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
#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <QWidget>
#include "ui_ImageContainer.h"
#include "HttpImageDownloader.h"

/**
	CImageHolder is designed for the purpose of holding image wheather they are local image or searched image from http://wwww.google.com.CImageHolder class differentiate between image type i.e. local image or web based image based on the image path set using setImagePath() function. 

	CImageHolder provide API to place image on the constructed QLabel widget like setPixmap().


	CImageHolder also reponds to the event like zooom in and zoom out. On zoom in event it scales the set image to the size of the widget. and on the zoom out event it sets the previous scaled image on the widget so that image loading happens only once for the zoom in event. For zoom in and zoom out event in case of google searched images CImageHolder class uses CHttpImageDownloader class oject to download those images from the internet. Once those images are downloaded from the internet, They are scaled to fit into scaled widget size.

	@see CHttpImageDownloader

	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CImageHolder : public QWidget,protected Ui::ImageContainerFrame
{
Q_OBJECT
public:
    CImageHolder(QWidget *parent = 0);

    virtual ~CImageHolder();

    /**
	This function set pixmap to the QLabel widget. This pixmap is supposed to be thumbnail size of the original image. While zoom out event occurs this function is called and the thumbnail view of the image is set.
     * 
     * @param imageItem 
     */
    void setPixmap(const QPixmap &imageItem);

    /**
     *		
     * 
     * @return Currently set pixmap of the QLabel widget
     */
    QPixmap pixmap() const;

    /**
     * This function is set the original image to the QLabel. It is called when zoom in event occurs, this way image smooth transmission is done from thumbnail view to original pixmap view. 
	@see setImagePath
     */
    void setOriginalPixmap();

    /**
     * This function sets the absolute path of the image or URL of the particular image. Image path is required when zoom in event has occured and smooth image transmission is required from thumbnail view to original image.
	
	Differentiation between local image path and URL is done at runtime when image needs to be changed. 
 
     * @param path URL or absolute path to original image

	@see setOriginalPixmap
     */
    void setImagePath(const QString& path);

public slots:

    /**
     *	This slot is called from CHttpImageDownloader object when image data is downloaded from the web.However it is not guranteed that downloaded data is actual image or not. This is resolved at the time setting up downloaded image on the QLabel. If the downlaoaded image is not able to create QImage object out of it then appropriate text message is set.
	
     * @param  imageData downloaded image data from web
	@see imageDownloadProgress()
     */
    void imageDownloaded(QByteArray imageData);


    /**
     * This slot is called for monitoring download progress of image. 

     * @param  progress download progress in percent
	@see imageDownloaded()
     */
    void imageDownloadProgress(int progress);		

private:
    QString m_ImagePath;
    CHttpImageDownloader *m_pImageLoader;	
	
};

#endif
