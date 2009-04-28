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



#include "CustomLabel.h"
#include "ImageProxyWidget.h"

#include "HttpImageDownloader.h"

#include <QWebView>
#include <QUrl>
#include <QFileInfo>

// Global Variable
int mainWidth = 0;
int mainHeight = 0;

int ImageWidth = 0;
int ImageHeight = 0;



// Global Functions

ScaledImageInfo MyScale(const QString &imageFileName )
{
    ImageWidth = (int)(mainWidth * 15 )/ 100;
    ImageHeight = (int)(mainHeight * 15) /100;

    ScaledImageInfo result;
    QImage image ( imageFileName );
    result.m_ScaledImage = image.scaled ( QSize ( ImageWidth, ImageHeight), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    result.m_ScaledImagePath = imageFileName;
    return result;
}


QImage scaleFromImage(const QImage &image)
{
    ImageWidth = (int)(mainWidth * 15 )/ 100;
    ImageHeight = (int)(mainHeight * 15) /100;

    QImage scaledImage = image.scaled ( QSize ( ImageWidth, ImageHeight), Qt::KeepAspectRatio, Qt::SmoothTransformation );
    return scaledImage;
}

static QImage *mirrorImage (const QImage *image)
{
    QImage *tmpImage = new QImage(image->mirrored(false, true));

    QPoint p1, p2;
    p2.setY(tmpImage->height());

    QLinearGradient gradient(p1, p2);
    gradient.setColorAt(0, Qt::transparent);
    gradient.setColorAt(1, QColor(0, 0, 0, 255));

    QPainter p(tmpImage);
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

    m_ZoomFactor = 1;
    m_MouseButtonPressed = false;

    this->setScene ( &m_GraphicsScene );

    this->setRenderHints ( QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);

    this->setCacheMode ( QGraphicsView::CacheNone );
    this->setViewportUpdateMode ( QGraphicsView::FullViewportUpdate );

    setMessage("Please Set Image Directory");



    connect ( m_pImageScaling, SIGNAL ( resultReadyAt ( int ) ), SLOT ( showImageOnWall ( int ) ) );
}


CMainPictureWallArea::~CMainPictureWallArea()
{



    delete m_pImageScaling;
}

void CMainPictureWallArea::cleanAllResults()
{
    m_pImageScaling->cancel();
    m_pImageScaling->waitForFinished ();
    m_GraphicsScene.clear();
    if (this->horizontalScrollBar() != NULL)
    {
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->minimum());
    }

    m_GraphicsScene.setSceneRect(QRectF(0,0,0,0));

    m_Row =0;
    m_Column=0;
}

void CMainPictureWallArea::loadImagesFromDirectoryRecursivelySlot(QString directoryPath)
{
    QDir dir(directoryPath);
    QStringList filter;
    QStringList fileList;

    filter << "*.jpg" << "*.png" << "*.bmp" << "*.gif" << "*.jpeg" << "*.pbm" << "*.xmp" << "*.xbm";

    cleanAllResults();
    mainWidth = this->geometry().width();
    mainHeight = this->geometry().height();


    fileList = dir.entryList ( filter, QDir::Files );

    for (int i=0;i<fileList.count();++i)
    {
        fileList[i] = dir.path()+QString("/")+fileList.at(i);
    }


    if (fileList.isEmpty())
    {
        setMessage("0 Images Found");
        return;
    }

    m_pImageScaling->setFuture(QtConcurrent::mapped(fileList,MyScale));
}


void CMainPictureWallArea::showImageOnWall(int num)
{

    CImageProxyWidget *pCImageProxyWidgetInstance = new CImageProxyWidget(0, Qt::Window );
    CustomLabel *imageItem = new CustomLabel();

    ScaledImageInfo result = m_pImageScaling->resultAt ( num );

    imageItem->setPixmap(QPixmap::fromImage(result.m_ScaledImage));
    imageItem->setImagePath(result.m_ScaledImagePath);

    if (m_Row >= 3)
    {
        m_Row =0;
        m_Column ++;

    }

    QRectF rect = pCImageProxyWidgetInstance->boundingRect();
    rect.setWidth(ImageWidth+10);
    rect.setHeight(ImageHeight+10);

    pCImageProxyWidgetInstance->setWidget(imageItem);
    pCImageProxyWidgetInstance->setPos(m_Column * rect.width() * 1.05, m_Row * rect.height() * 1.3 );
    pCImageProxyWidgetInstance->setCacheMode ( QGraphicsItem::NoCache );
    pCImageProxyWidgetInstance->setDefaultItemGeometry(pCImageProxyWidgetInstance->geometry());
    m_GraphicsScene.addItem ( pCImageProxyWidgetInstance );

    m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );

    QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedIn()),imageItem,SLOT(imageZoomedIn()));
    QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedOut()),imageItem,SLOT(imageZoomedOut()));

    m_Row ++;

    if (m_Row == 3)
    {

        QLabel *imageReflcetionItem = new QLabel();
        QGraphicsProxyWidget *pCImageProxyWidgetReflectionInstance = new QGraphicsProxyWidget(0, Qt::Window );

        QImage *img = new QImage(result.m_ScaledImage);

        img = mirrorImage(img);

        imageReflcetionItem->setPixmap(QPixmap::fromImage(*img));


        QRectF rect = pCImageProxyWidgetReflectionInstance->boundingRect();
        rect.setWidth(ImageWidth+10);
        rect.setHeight(ImageHeight+10);

        pCImageProxyWidgetReflectionInstance->setWidget(imageReflcetionItem);
        pCImageProxyWidgetReflectionInstance->setPos(m_Column * rect.width() * 1.05, (m_Row) * rect.height() * 1.3 );
        pCImageProxyWidgetReflectionInstance->setCacheMode ( QGraphicsItem::ItemCoordinateCache);

        m_GraphicsScene.addItem ( pCImageProxyWidgetReflectionInstance );
    }

}

void  CMainPictureWallArea::showImageOnWall(QByteArray image,QString imageMainUrl)
{
    CImageProxyWidget *pCImageProxyWidgetInstance = new CImageProxyWidget(0, Qt::Window );
    CustomLabel *imageItem = new CustomLabel();

    //ScaledImageInfo result = m_pImageScaling->resultAt ( num );

    imageItem->setPixmap(QPixmap::fromImage(scaleFromImage(QImage::fromData(image))));
    imageItem->setImagePath(imageMainUrl);
    //imageItem->setImagePath(result.m_ScaledImagePath);

    if (m_Row >= 3)
    {
        m_Row =0;
        m_Column ++;

    }

    QRectF rect = pCImageProxyWidgetInstance->boundingRect();
    rect.setWidth(ImageWidth+10);
    rect.setHeight(ImageHeight+10);

    pCImageProxyWidgetInstance->setWidget(imageItem);
    pCImageProxyWidgetInstance->setPos(m_Column * rect.width() * 1.05, m_Row * rect.height() * 1.3 );
    pCImageProxyWidgetInstance->setCacheMode ( QGraphicsItem::NoCache );
    pCImageProxyWidgetInstance->setDefaultItemGeometry(pCImageProxyWidgetInstance->geometry());
    m_GraphicsScene.addItem ( pCImageProxyWidgetInstance );

    m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );

    QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedIn()),imageItem,SLOT(imageZoomedIn()));
    QObject::connect(pCImageProxyWidgetInstance,SIGNAL(imageZoomedOut()),imageItem,SLOT(imageZoomedOut()));

    m_Row ++;

    if (m_Row == 3)
    {

        QLabel *imageReflcetionItem = new QLabel();
        QGraphicsProxyWidget *pCImageProxyWidgetReflectionInstance = new QGraphicsProxyWidget(0, Qt::Window );

        QImage *img = new QImage(scaleFromImage(QImage::fromData(image)));

        img = mirrorImage(img);

        imageReflcetionItem->setPixmap(QPixmap::fromImage(*img));


        QRectF rect = pCImageProxyWidgetReflectionInstance->boundingRect();
        rect.setWidth(ImageWidth+10);
        rect.setHeight(ImageHeight+10);

        pCImageProxyWidgetReflectionInstance->setWidget(imageReflcetionItem);
        pCImageProxyWidgetReflectionInstance->setPos(m_Column * rect.width() * 1.05, (m_Row) * rect.height() * 1.3 );
        pCImageProxyWidgetReflectionInstance->setCacheMode ( QGraphicsItem::ItemCoordinateCache);

        m_GraphicsScene.addItem ( pCImageProxyWidgetReflectionInstance );
    }

}


void CMainPictureWallArea::setMessage(const QString &text)
{
    QGraphicsTextItem *textMessage = new QGraphicsTextItem(text);
    textMessage->setFont(QFont("Times", 20));
    textMessage->setDefaultTextColor(QColor(255,255,255,255));
    textMessage->setPos(m_Column * textMessage->boundingRect().width() * 1.05, m_Row * textMessage->boundingRect().height() * 1.3 );

    m_GraphicsScene.addItem ( textMessage );

    m_GraphicsScene.setSceneRect ( m_GraphicsScene.itemsBoundingRect() );
}


void CMainPictureWallArea::changeZoomLevelByFactor(EZoomFocus zoom)
{

    if (zoom == IN)
    {
        m_ZoomFactor = m_ZoomFactor + 0.25;
        if ((m_ZoomFactor -1) > 0)
        {
            m_ZoomFactor =1;
        }
    }
    else
    {

        m_ZoomFactor = m_ZoomFactor - 0.25;

        if ((m_ZoomFactor -0.25) < 0)
        {
            m_ZoomFactor =0.25;
        }

    }

    this->setTransform ( QTransform()
                         .translate ( this->contentsRect().width() , this->contentsRect().height() )
                         .scale ( m_ZoomFactor , m_ZoomFactor)
                         .translate ( -this->contentsRect().width() , -this->contentsRect().height() ));

}


void CMainPictureWallArea::wheelEvent ( QWheelEvent * e )
{
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    if (numSteps > 0)
    {
        changeZoomLevelByFactor(CMainPictureWallArea::IN);
    }
    else if (numSteps < 0)
    {
        changeZoomLevelByFactor(CMainPictureWallArea::OUT);
    }


    QGraphicsView::wheelEvent(e);

}


void CMainPictureWallArea::mousePressEvent ( QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_MouseDeltaValueForPressedEvent = e->x();
        m_MouseButtonPressed = true;
    }
    QGraphicsView::mousePressEvent (e);
}

void CMainPictureWallArea::mouseReleaseEvent ( QMouseEvent *e )
{
    if (e->button() == Qt::LeftButton)
    {
        m_MouseButtonPressed = false;
    }

    QGraphicsView::mouseReleaseEvent(e);
}

void CMainPictureWallArea::mouseMoveEvent ( QMouseEvent *e )
{
    int direction;

    if (m_MouseButtonPressed)
    {
        direction = m_MouseDeltaValueForPressedEvent -e->x();

        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() + direction);

        m_MouseDeltaValueForPressedEvent=e->x();
    }

    QGraphicsView::mouseMoveEvent(e);
}

void CMainPictureWallArea::showGoogleImageResult(QHash<QString,QString> result)
{
    mainWidth = this->geometry().width();
    mainHeight = this->geometry().height();

    CHttpImageDownloader *pDownloadImageFromGoogle = new CHttpImageDownloader(result["tbUrl"],result["url"]);

    connect(pDownloadImageFromGoogle,SIGNAL(downloadComplete(QByteArray,QString)),pDownloadImageFromGoogle,SLOT(deleteLater()));
    connect(pDownloadImageFromGoogle,SIGNAL(downloadComplete(QByteArray,QString)),this,SLOT(showImageOnWall(QByteArray,QString )));

    pDownloadImageFromGoogle->start();
}






