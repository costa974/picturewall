//
// C++ Implementation: HttpImageDownloader
//
// Description:
//
//
// Author: vishwajeet <vishwajeet.dusane@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "HttpImageDownloader.h"

#include <QUrl>

CHttpImageDownloader::CHttpImageDownloader(const QString &imageUrl,const QString &imageMainUrl,QObject *parent)
        : QThread(parent)
{
    m_ImageUrl = imageUrl;
    m_ImageMainUrl = imageMainUrl;
    http = new QHttp(this);

    connect(http, SIGNAL(requestFinished(int, bool)),
            this, SLOT(httpRequestFinished(int, bool)));
    connect(http, SIGNAL(dataReadProgress(int, int)),
            this, SLOT(updateDataReadProgress(int, int)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)),
            this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
}


CHttpImageDownloader::~CHttpImageDownloader()
{
}

void CHttpImageDownloader::run()
{
    downloadImage(m_ImageUrl);
}


void CHttpImageDownloader::setDownloadImageUrl(const QString &imageUrl)
{
    this->m_ImageUrl = imageUrl;

}

void CHttpImageDownloader::downloadImage(const QString &imageUrl)
{

    buffer.open(QBuffer::ReadWrite);

    QUrl url(imageUrl);

    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    http->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    if (!url.userName().isEmpty())
        http->setUser(url.userName(), url.password());

    httpGetId = http->get(url.toString(), &buffer);
}


void CHttpImageDownloader::httpRequestFinished(int requestId, bool error)
{
    if (requestId != httpGetId)
        return;

    emit downloadComplete(buffer.data(),m_ImageMainUrl);

    buffer.close();

}

void CHttpImageDownloader::readResponseHeader(const QHttpResponseHeader &responseHeader)
{
    switch (responseHeader.statusCode())
    {
    case 200:                   // Ok
    case 301:                   // Moved Permanently
    case 302:                   // Found
    case 303:                   // See Other
    case 307:                   // Temporary Redirect
        // these are not error conditions
        break;

        http->abort();
    }
}

void CHttpImageDownloader::updateDataReadProgress(int bytesRead, int totalBytes)
{
    int downloadPercentComplete =0;

    if (bytesRead >1)
    {
        downloadPercentComplete = ((double)bytesRead/totalBytes) * 100;
    }

    emit downloading(downloadPercentComplete);
}



