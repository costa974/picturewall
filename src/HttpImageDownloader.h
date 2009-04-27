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
	CHttpImageDownloader class provides methods to download image files from the web servers.CHttpImageDownloader class runs in a different thread and once the image is downloaded 100%, it emits downloadComplete() signal. CHttpImageDownloader class also emits signal for progress of the downloaded image.

	CHttpImageDownloader class also stores the thumbnail view URL and original view URL of the image, when download complete it emits original view URL with the downaloded image byte array.

	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CHttpImageDownloader : public QThread
{
    Q_OBJECT
public:
    /**
     *
     * @param imageUrl image URL that need to be downloaded
     * @param imageMainUrl image URL that need to be emitted with downloadComplete() signal
     * @param parent
     */
    CHttpImageDownloader(const QString &imageUrl,const QString &imageMainUrl,QObject *parent = 0);

    virtual ~CHttpImageDownloader();


    /**
     * This function set the URL from which image needs to be downloaded.
     * @param imageUrl URL for the image loacation
     */
    void setDownloadImageUrl(const QString &imageUrl);

public slots:

    /**
     * This slot invoked download process for the set URL
     * @param imageUrl
     */
    void downloadImage(const QString &imageUrl);

protected:
    virtual void run();

private slots:
    void httpRequestFinished(int requestId, bool error);
    void readResponseHeader(const QHttpResponseHeader &responseHeader);
    void updateDataReadProgress(int bytesRead, int totalBytes);

signals:
    /**
     * This signal is emitted when image download from the web server is started. This signal emits progress in percent for the downloaded image. Progress emitted byt his signal range from 0-100
     * @param
     */
    void downloading(int );

    /**
     * This signal is called when image is downloaded web server. This signal emits bytearray of the downloaded image and also original image URL.
     * @param  downloadedImageData downloaded image data from the web server
     * @param  mainURL URL for the original image
     */
    void downloadComplete(QByteArray downloadedImageData,QString mainURL);

private:
    QHttp *http;
    QBuffer buffer;
    int httpGetId;
    QString m_ImageUrl;
    QString m_ImageMainUrl;
};

#endif
