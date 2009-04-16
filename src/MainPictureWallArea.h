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
class CMainPictureWallArea : public QGraphicsView
{
Q_OBJECT
public:
    CMainPictureWallArea(QWidget *parent = 0);

    ~CMainPictureWallArea();

  enum EZoomLevel
  {
        ZoomLevel10 = 10,
	ZoomLevel30 = 30,
	ZoomLevel50 = 50,
	ZoomLevel60 = 60,
	ZoomLevel80 = 80,
	ZoomLevel100 = 100,
  };

private:

	enum EZoomFocus
	{
		IN,
		OUT
	};


public slots:

      void loadImagesFromDirectoryRecursivelySlot(QString directoryPath);
      void showImageOnWallAtPosition(int num);
      void changeZoomLevelByFactor(int factor,EZoomFocus zoom);

	// Scrolling animation slots 
      void updateScrollingAnimationStep(qreal steps);
      void scrollingAnimationStateChanged(QTimeLine::State);
      void scrollingAnimationFinsihed();		

protected:
	virtual void wheelEvent ( QWheelEvent *  ); 
	virtual void mousePressEvent ( QMouseEvent * );
	virtual void mouseReleaseEvent ( QMouseEvent * );
	virtual void mouseMoveEvent ( QMouseEvent * );

private:

	void zoom(EZoomFocus zoom);

private:
	QFutureWatcher<QImage> *m_pImageScaling; 
	int m_Row;
	int m_Column;
	QGraphicsScene m_GraphicsScene;
	EZoomLevel m_CurrentZoomLevel;

	QTimeLine *m_pScrollingAnimation;
	int m_MouseDeltaValueForPressedEvent;
	bool m_MouseButtonPressed;
	

};

#endif
