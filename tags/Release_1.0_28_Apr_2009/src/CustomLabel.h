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
#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QDialog>
#include <QLabel>
#include <QWebView>

#include "ImageHolder.h"

/**
	CustomLabel class is container class which holds the CImageHolder class object.
		

	@see CImageHolder

	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CustomLabel : public QDialog
{
    Q_OBJECT
public:
    /**
     *
     * @param parent
     */
    CustomLabel ( QWidget *parent = 0 );
    /**
     * 
     */
    virtual	~CustomLabel();

public slots:
    /**
     *    This function sets pixmap to CImageHolder object. This function is called when image within CImageHolder object needs to change  
     *    
     * @see CImageHolder
     * 
     * @param  pixmap 
     */
    void setPixmap(const QPixmap& pixmap);

    /**
     * 
     * This function sets the absoulute path of the image, Whever image zoom is called CImageHolder class loads the image from this path and set the scaled image to zoomed CImageHolder widget  
     * @see CImageHolder
     * 
     * @param  imagePath abosolute path of the image which needs to be displayed while image zoom in is called
     */
    void setImagePath(const QString& imagePath);

    /**
     * This slot is called whenever zoom in on respective CImageHolder widget is called. In this application, This slot is called when mouse pressed event occurs on image. 
	@see CImageHolder

     */
    void imageZoomedIn();

    /**
     * This slot is called whenever zoom out on respective CImageHolder widget is called. In this application, This slot is called when mouse pressed event occurs on image and image is already zoomed in state and also when mouse is moved away from the zoomed in image. 

	@see CImageHolder
     */
    void imageZoomedOut();

private:
		
    CImageHolder *m_pImageHolderInstance;
    QPixmap m_VisibleImageState;
};

#endif
