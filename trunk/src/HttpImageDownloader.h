//
// C++ Interface: HttpImageDownloader
//
// Description: 
//
//
// Author: vishwajeet <vishwajeet.dusane@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef HTTPIMAGEDOWNLOADER_H
#define HTTPIMAGEDOWNLOADER_H

#include <QThread>
#include <QHttp>
#include <QBuffer>
/**
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CHttpImageDownloader : public QThread
{
Q_OBJECT
public:
    CHttpImageDownloader(const QString &imageUrl,const QString &imageMainUrl,QObject *parent = 0);

    virtual ~CHttpImageDownloader();


    void setDownloadImageUrl(const QString &imageUrl);	

public slots:
	void downloadImage(const QString &imageUrl);

protected:
	virtual void run();

private slots:
    
    void httpRequestFinished(int requestId, bool error);
    void readResponseHeader(const QHttpResponseHeader &responseHeader);
    void updateDataReadProgress(int bytesRead, int totalBytes);

signals:
    void downloading(int );
    void downloadComplete(QByteArray,QString);

private:
    QHttp *http;
    QBuffer buffer;
    int httpGetId;
    QString m_ImageUrl;
    QString m_ImageMainUrl;	
};

#endif
