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
#ifndef PICTUREWALLMAINWINDOW_H
#define PICTUREWALLMAINWINDOW_H

#include <QWidget>
#include "ui_PictureWallMainWindow.h"
#include "GoogleSearcher.h"


/**
 	CPictureWallMainWindow class is a main GUI container class. CPictureWallMainWindow initializes Graphics widget where pictures are displayed and GUI control over those displayed images.
	
	CPictureWallMainWindow class provides two options to select images from. 1. browse through local images i.e. images which are store on local media. User has to select directory path in which recurcively search will take place and all images will be taken out. 
	2. search images on web using google.com, Once the search query is entered, recurcive search is done on google.com server using google AJAX api
	
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CPictureWallMainWindow : public QWidget,public Ui::PictureWallMainWindowDesignerUI
{
Q_OBJECT
public:
    CPictureWallMainWindow(QWidget *parent = 0);

    virtual ~CPictureWallMainWindow();
public slots:
     /**
      * This slot is called when local directory path needs to change. This slot invokes interactive file dialog to select directory path, Once the directory is selected, respective images are populated within graphics area. 
      */
     void changeDirectorySlot();
	
	
     /**
      * This slot is emitted when the Return or Enter key is pressed on input text line edit in GUI. This slot invokes CGoogleSearcher class object to search on google searver with new query. 
      */
     void startNewGoogleSearch();
	
     /**
      * This slot is invoked when google search radio button is toggled.This slot will hide file dialog button and path of the direcotry and make line edit visible to enter search query 
	This slot also clean up previous search images from graphics window
      * @param checked if true hide file dialog and show line edit to enter search
	@see selectLocalImageViewerSelected
      */
     void selectGoogleSearchOption(bool checked );
     /**
      * This slot is invoked when local directory search radio button is toggled.This slot will hide google search line edit and make  file dialog button visible 
      * @param checked if true hide google search line edit and make file dialog visible
	@see selectGoogleSearchOption

      */
     void selectLocalImageViewerSelected(bool checked ); 	

signals:
     /**
      * This signal is emitted when directory path changes
      * @param directoryPath 
      */
     void directoryChangedSignal(QString directoryPath);
     /**
      * This signal is emitted when google radio button is toggled
      */
     void googleSearchOptionSelected();
     /**
      * This signal is emitted when local radio button is toggled
      */
     void localImageViewerSelected();
     /**
      * This signal is emitted when new search record is recieve from CGoogleSearcher class
      * @param  
      */
     void googleSearchResult(QHash<QString,QString>);	

private:
     CGoogleSearcher *m_pGoogleSearcherInstance;

};

#endif
