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
#include "MainPictureWallArea.h"


#include "ImageProxyWidget.h"


// Global Variable
const int ImageWidth = 200;
const int ImageHeight = 150;
// Global Functions
QImage MyScale(const QString &imageFileName )
{
	QImage image ( imageFileName );
	return image.scaled ( QSize ( ImageWidth, ImageHeight), Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
}


CMainPictureWallArea::CMainPictureWallArea(QWidget *parent)
 : QGraphicsView(parent),m_Row(0),m_Column(0)
{

	m_pImageScaling = new QFutureWatcher<QImage> ( this );

	m_CurrentZoomLevel=ZoomLevel100;

	this->setScene ( &m_GraphicsScene );

	this->setRenderHints ( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);


	m_pScrollingAnimation = new QTimeLine ( 1000,this );
	m_pScrollingAnimation->setFrameRange(0,1);
	m_pScrollingAnimation->setCurveShape(QTimeLine::EaseOutCurve);
	m_pScrollingAnimation->setLoopCount ( 1 );
	//timeLine->setCurveShape(QTimeLine::EaseInCurve); horizontalLayout->setMargin(0);

	connect ( m_pScrollingAnimation, SIGNAL ( valueChanged ( qreal ) ),
	          this, SLOT ( updateScrollingAnimationStep ( qreal ) ) );
	connect ( m_pScrollingAnimation, SIGNAL ( stateChanged ( QTimeLine::State ) ),
	          this, SLOT ( scrollingAnimationStateChanged ( QTimeLine::State ) ) );
	connect ( m_pScrollingAnimation, SIGNAL ( finished() ),
	          this, SLOT ( scrollingAnimationFinsihed() ) );

	connect ( m_pImageScaling, SIGNAL ( resultReadyAt ( int ) ), SLOT ( showImageOnWallAtPosition ( int ) ) );
}


CMainPictureWallArea::~CMainPictureWallArea()
{

}

void CMainPictureWallArea::loadImagesFromDirectoryRecursivelySlot(QString directoryPath)
{
	QDir dir(directoryPath);	
	QStringList filter;
	QStringList fileList;

	filter << "*.jpg" << "*.png" << "*.bmp" << "*.gif" << "*.jpeg" << "*.pbm" << "*.xmp" << "*.xbm";

	m_GraphicsScene.clear();
	m_Row =0;
	m_Column=0;
	

	fileList = dir.entryList ( filter, QDir::Files );

	for(int i=0;i<fileList.count();++i)
	{
		fileList[i] = dir.path()+QString("/")+fileList.at(i);		
	}

	m_pImageScaling->setFuture(QtConcurrent::mapped(fileList,MyScale));
}

void CMainPictureWallArea::showImageOnWallAtPosition(int num)
{

	//CGraphicsPixmapItem *imageItem = new CGraphicsPixmapItem();
	QLabel *imageItem = new QLabel();
	CImageProxyWidget *pCImageProxyWidgetInstance = new CImageProxyWidget();

	imageItem->setPixmap(QPixmap::fromImage(m_pImageScaling->resultAt ( num )));

	if(m_Row >= 3)
	{
		m_Row =0;
		m_Column ++;
				
	}

	if(m_Row == 3)
	{
		pCImageProxyWidgetInstance->setReflection(true);
	}

	QRectF rect = pCImageProxyWidgetInstance->boundingRect();
	rect.setWidth(ImageWidth+20);
	rect.setHeight(ImageHeight+20);

	pCImageProxyWidgetInstance->setWidget(imageItem);
	pCImageProxyWidgetInstance->setPos(m_Column * rect.width() * 1.05, m_Row * rect.height() * 1.05 );
	pCImageProxyWidgetInstance->setCacheMode ( QGraphicsItem::NoCache );

	m_GraphicsScene.addItem ( pCImageProxyWidgetInstance );
	m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );


	m_Row ++;
}



void CMainPictureWallArea::changeZoomLevelByFactor(int factor,EZoomFocus zoom)
{

	qreal zoomFactor = 1;

	if(zoom == IN)
	{
		zoomFactor = 1.5;
	}else
	{
		zoomFactor = 0.5;
	}

		     this->setTransform ( QTransform() 
	             .translate ( this->contentsRect().width() , this->contentsRect().height() )
                     .scale ( zoomFactor , zoomFactor )
                      .translate ( -this->contentsRect().width() , -this->contentsRect().height() ));
	this->zoom(zoom);
}

void CMainPictureWallArea::zoom(EZoomFocus zoom)
{
	if(zoom == IN)
	{
		switch(m_CurrentZoomLevel)
		{
			case ZoomLevel10:
				m_CurrentZoomLevel = ZoomLevel30;
				break;
			case ZoomLevel30:
				m_CurrentZoomLevel = ZoomLevel50;
				break;
			case ZoomLevel50:
				m_CurrentZoomLevel = ZoomLevel60;
				break;
			case ZoomLevel60:
				m_CurrentZoomLevel = ZoomLevel80;
				break;
			case ZoomLevel80:
				m_CurrentZoomLevel = ZoomLevel100;
				break;
		}

	}else
	{
		switch(m_CurrentZoomLevel)
		{
			case ZoomLevel100:
				m_CurrentZoomLevel = ZoomLevel80;
				break;
			case ZoomLevel30:
				m_CurrentZoomLevel = ZoomLevel10;
				break;
			case ZoomLevel50:
				m_CurrentZoomLevel = ZoomLevel30;
				break;
			case ZoomLevel60:
				m_CurrentZoomLevel = ZoomLevel50;
				break;
			case ZoomLevel80:
				m_CurrentZoomLevel = ZoomLevel60;
				break;
		}
	}		
}

void CMainPictureWallArea::updateScrollingAnimationStep(qreal steps)
{
	QRectF r = contentsRect ();
	qreal roatioinAngle = steps * 30;	

		this->setTransform ( QTransform() 
	                     .translate ( r.width() / 2, r.height() / 2 )
	                     .rotate( roatioinAngle, Qt::YAxis)
	                     .translate ( -r.width() / 2, -r.height() / 2 ));
}

void CMainPictureWallArea::scrollingAnimationStateChanged(QTimeLine::State)
{
	
}

void CMainPictureWallArea::scrollingAnimationFinsihed()
{
		if ( m_pScrollingAnimation->direction() == QTimeLine::Forward )
		{
			//qDebug("Animation not running so start it in forward direction");
			m_pScrollingAnimation->setDirection ( QTimeLine::Backward );
			m_pScrollingAnimation->start();
		}
}


void CMainPictureWallArea::wheelEvent ( QWheelEvent * e )
{
     int numDegrees = e->delta() / 8;
     int numSteps = numDegrees / 15;

	qDebug("Degree = %d , steps = %d",numDegrees,numSteps);

	if(numSteps > 0)
	{
		changeZoomLevelByFactor(numSteps,CMainPictureWallArea::IN);
	}else if(numSteps < 0)
	{
		numSteps = -1*numSteps;
		changeZoomLevelByFactor(numSteps,CMainPictureWallArea::OUT);
	}


	QGraphicsView::wheelEvent(e);

}


void CMainPictureWallArea::mousePressEvent ( QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		m_MouseDeltaValueForPressedEvent = e->x();
		m_MouseButtonPressed = true;
	}
}

void CMainPictureWallArea::mouseReleaseEvent ( QMouseEvent *e )
{
	if(e->button() == Qt::LeftButton)
	{
		m_MouseButtonPressed = false;
	}
}

void CMainPictureWallArea::mouseMoveEvent ( QMouseEvent *e )
{
	int direction;
	if(m_MouseButtonPressed)
	{
		direction = m_MouseDeltaValueForPressedEvent -e->x();
 		if(direction > 0)
		{
			this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + 10);
			
			/*
			if(m_pScrollingAnimation->state() == QTimeLine::NotRunning )
			{
				m_pScrollingAnimation->setDirection ( QTimeLine::Forward );
				m_pScrollingAnimation->start();
			}
			*/
		}else
		{
			this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - 10);
		}

		m_MouseDeltaValueForPressedEvent=e->x();
	}
}






