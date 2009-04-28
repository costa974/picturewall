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
#include "ImageHolder.h"
#include <QFileInfo>



CImageHolder::CImageHolder(QWidget *parent)
 : QWidget(parent)
{
	setupUi(this);
	
	m_pImageDownloadProgressBar->hide();
	
	m_pImageLoader = new CHttpImageDownloader(QString(),QString(),this);
	
	connect(m_pImageLoader,SIGNAL(downloadComplete(QByteArray,QString)),this,SLOT(imageDownloaded(QByteArray)));
	connect(m_pImageLoader,SIGNAL(downloading(int )),this,SLOT(imageDownloadProgress(int)));
	
}


CImageHolder::~CImageHolder()
{
	delete m_pImageLoader;
}

void CImageHolder::setPixmap(const QPixmap &imageItem)
{
	m_pImageDownloadProgressBar->hide();
	m_pImageLoader->quit();
	m_pImagePlaceHolder->setPixmap(imageItem);
}

void CImageHolder::setImagePath(const QString& path)
{
	m_ImagePath = path;
}

QPixmap CImageHolder::pixmap() const
{
	return QPixmap(*m_pImagePlaceHolder->pixmap());
	
}

void CImageHolder::setOriginalPixmap()
{
	if(m_ImagePath.startsWith("http"))
	{
		m_pImageDownloadProgressBar->show();
		m_pImageLoader->setDownloadImageUrl(m_ImagePath);
		m_pImageLoader->start();		
	}else
	{
		QImage image(m_ImagePath);
		m_pImagePlaceHolder->setPixmap(QPixmap::fromImage(image.scaled ( QSize ( this->width(), this->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation )));
	}
}

void CImageHolder::imageDownloaded(QByteArray imageData)
{
	
	QImage image(QImage::fromData(imageData));
	m_pImageDownloadProgressBar->hide();	
	if(image.isNull())
	{
		m_pImagePlaceHolder->setText("Image Is Not Available On Server");
	}else
	{
	m_pImagePlaceHolder->setPixmap(QPixmap::fromImage(image.scaled ( QSize ( this->width(), this->height()), Qt::KeepAspectRatio, Qt::SmoothTransformation )));
	}
	
}

void CImageHolder::imageDownloadProgress(int progress)
{
	m_pImageDownloadProgressBar->setValue(progress);
}
		

