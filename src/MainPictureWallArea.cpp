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
#include "ImageHolder.h"

#include "CustomLabel.h"
#include "CustomProxy.h"


// Global Variable
const int ImageWidth = 187;
const int ImageHeight = 106;
// Global Functions
ScaledImageInfo MyScale(const QString &imageFileName )
{
	ScaledImageInfo result;
	QImage image ( imageFileName );
	result.m_ScaledImage = image.scaled ( QSize ( ImageWidth, ImageHeight), Qt::KeepAspectRatio, Qt::SmoothTransformation );
	result.m_ScaledImagePath = imageFileName;

	return result;
}


static QImage *mirrorImage (const QImage *image) {
	QImage *tmpImage = new QImage(image->mirrored(false, true));

	QPoint p1, p2;
	p2.setY(tmpImage->height());
	
	QLinearGradient gradient(p1, p2);
	gradient.setColorAt(0, Qt::transparent);
	gradient.setColorAt(1, QColor(0, 0, 0, 255));

	QPainter p(tmpImage);
	//p.setCompositionMode(QPainter::CompositionMode_Lighten);
	p.fillRect(0, 0, tmpImage->width(), tmpImage->height(), gradient);

	gradient.setColorAt(0,QColor(0, 0, 0, 255));
	gradient.setColorAt(1, Qt::transparent);
	p.fillRect(0,0, tmpImage->width(), tmpImage->height(), gradient);

	p.end();

	return(tmpImage);
}



CMainPictureWallArea::CMainPictureWallArea(QWidget *parent)
 : QGraphicsView(parent),m_Row(0),m_Column(0)
{

	m_pImageScaling = new QFutureWatcher<ScaledImageInfo> ( this );

	m_CurrentZoomLevel=ZoomLevel100;

	m_MouseButtonPressed = false;

	this->setScene ( &m_GraphicsScene );

	this->setRenderHints ( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);

	this->setCacheMode ( QGraphicsView::CacheNone );
	this->setViewportUpdateMode ( QGraphicsView::FullViewportUpdate );

	m_pScrollingAnimation = new QTimeLine ( 500,this );
	m_pScrollingAnimation->setFrameRange(0,10);
	m_pScrollingAnimation->setCurveShape(QTimeLine::LinearCurve);
	m_pScrollingAnimation->setLoopCount ( 1 );
	//timeLine->setCurveShape(QTimeLine::EaseInCurve); horizontalLayout->setMargin(0);
	
	connect ( m_pScrollingAnimation, SIGNAL ( frameChanged ( int ) ),
	          this, SLOT ( updateScrollingAnimationStep ( int ) ) );
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

	m_pImageScaling->cancel();
	m_pImageScaling->waitForFinished ();
	m_GraphicsScene.clear();
	if(this->horizontalScrollBar() != NULL)
	{
		this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->minimum());
	}

	m_GraphicsScene.setSceneRect(QRectF(0,0,0,0));
	
	//this->setScene(&m_GraphicsScene);
	
	m_Row =0;
	m_Column=0;
	
	
	fileList = dir.entryList ( filter, QDir::Files );

	for(int i=0;i<fileList.count();++i)
	{
		fileList[i] = dir.path()+QString("/")+fileList.at(i);		
	}


	if(fileList.isEmpty())
	{
		QGraphicsTextItem *textMessage = new QGraphicsTextItem("No Images Found");
		textMessage->setFont(QFont("Times", 20));
		textMessage->setDefaultTextColor(QColor(255,255,255,255));

		textMessage->setPos(m_Column * textMessage->boundingRect().width() * 1.05, m_Row * textMessage->boundingRect().height() * 1.3 );
		m_GraphicsScene.addItem ( textMessage );
	
		m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );
		
		return;
	}

	m_pImageScaling->setFuture(QtConcurrent::mapped(fileList,MyScale));
}

void CMainPictureWallArea::showImageOnWallAtPosition(int num)
{

 //TODO same code is reapeated for reflcetion, make 1 function and call in it


	CustomProxy *pCImageProxyWidgetInstance = new CustomProxy(0, Qt::Window );
	//CImageProxyWidget *pCImageProxyWidgetInstance = new CImageProxyWidget(0, Qt::Window );

	CustomLabel *imageItem = new CustomLabel();

	ScaledImageInfo result = m_pImageScaling->resultAt ( num );

	imageItem->setPixmap(QPixmap::fromImage(result.m_ScaledImage));
	imageItem->setImagePath(result.m_ScaledImagePath);

	if(m_Row >= 3)
	{
		m_Row =0;
		m_Column ++;
				
	}

	QRectF rect = pCImageProxyWidgetInstance->boundingRect();
	rect.setWidth(ImageWidth+20);
	rect.setHeight(ImageHeight+20);

	pCImageProxyWidgetInstance->setWidget(imageItem);
	pCImageProxyWidgetInstance->setPos(m_Column * rect.width() * 1.05, m_Row * rect.height() * 1.3 );
	pCImageProxyWidgetInstance->setCacheMode ( QGraphicsItem::NoCache );
	pCImageProxyWidgetInstance->setDefaultItemGeometry(pCImageProxyWidgetInstance->geometry());
	m_GraphicsScene.addItem ( pCImageProxyWidgetInstance );
	
	m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );

	QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedIn()),imageItem,SLOT(imageZoomedIn()));
	QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedOut()),imageItem,SLOT(imageZoomedOut()));

	m_Row ++;

	if(m_Row == 3)
	{
		
		QLabel *imageReflcetionItem = new QLabel();
		//CImageProxyWidget *pCImageProxyWidgetReflectionInstance = new CImageProxyWidget();
		QGraphicsProxyWidget *pCImageProxyWidgetReflectionInstance = new QGraphicsProxyWidget(0, Qt::Window );
	
		QImage *img = new QImage(result.m_ScaledImage);
	
		img = mirrorImage(img);

		imageReflcetionItem->setPixmap(QPixmap::fromImage(*img));
	

		QRectF rect = pCImageProxyWidgetReflectionInstance->boundingRect();
		rect.setWidth(ImageWidth+20);
		rect.setHeight(ImageHeight+20);
	
		pCImageProxyWidgetReflectionInstance->setWidget(imageReflcetionItem);
		pCImageProxyWidgetReflectionInstance->setPos(m_Column * rect.width() * 1.05, (m_Row) * rect.height() * 1.3 );
		pCImageProxyWidgetReflectionInstance->setCacheMode ( QGraphicsItem::ItemCoordinateCache);
		
		m_GraphicsScene.addItem ( pCImageProxyWidgetReflectionInstance );
		
		//m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect());
		//pCImageProxyWidgetReflectionInstance->setReflection(true);
	}


}



void CMainPictureWallArea::changeZoomLevelByFactor(int factor,EZoomFocus zoom)
{

	qreal zoomFactor = 1;

	if(zoom == IN)
	{
		zoomFactor = 1;
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

void CMainPictureWallArea::updateScrollingAnimationStep(int steps)
{

	this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + steps);
/*
	QRectF r = contentsRect ();
	qreal roatioinAngle = steps * 30;	

		this->setTransform ( QTransform() 
	                     .translate ( r.width() / 2, r.height() / 2 )
	                     .rotate( roatioinAngle, Qt::YAxis)
	                     .translate ( -r.width() / 2, -r.height() / 2 ));
*/
}

void CMainPictureWallArea::scrollingAnimationStateChanged(QTimeLine::State)
{
	
}

void CMainPictureWallArea::scrollingAnimationFinsihed()
{
/*
		if ( m_pScrollingAnimation->direction() == QTimeLine::Forward )
		{
			//qDebug("Animation not running so start it in forward direction");
			m_pScrollingAnimation->setDirection ( QTimeLine::Backward );
			m_pScrollingAnimation->start();
		}
*/

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
	QGraphicsView::mousePressEvent (e);
}

void CMainPictureWallArea::mouseReleaseEvent ( QMouseEvent *e )
{
	if(e->button() == Qt::LeftButton)
	{
		m_MouseButtonPressed = false;
	}

	QGraphicsView::mouseReleaseEvent(e);
}

void CMainPictureWallArea::mouseMoveEvent ( QMouseEvent *e )
{
	int direction;
	int dosumentLength =  this->horizontalScrollBar()->maximum() - this->horizontalScrollBar()->minimum() + this->horizontalScrollBar()->pageStep();
	if(m_MouseButtonPressed)
	{
		direction = m_MouseDeltaValueForPressedEvent -e->x();
		qDebug("direction = %d , %d",direction,this->horizontalScrollBar()->pageStep());
		
		this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + direction);

 		if(direction > 0)
		{
			
			//m_pScrollingAnimation->setFrameRange(0,direction + 60);	
			
			//m_pScrollingAnimation->start();
			//this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + 10);
			
			/*
			if(m_pScrollingAnimation->state() == QTimeLine::NotRunning )
			{
				m_pScrollingAnimation->setDirection ( QTimeLine::Forward );
				m_pScrollingAnimation->start();
			}
			*/
		}else
		{
			//m_pScrollingAnimation->setFrameRange(0,-direction- 60);	
			//m_pScrollingAnimation->start();
	
			//this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - 10);
		}

		m_MouseDeltaValueForPressedEvent=e->x();
	}

	QGraphicsView::mouseMoveEvent(e);
}






