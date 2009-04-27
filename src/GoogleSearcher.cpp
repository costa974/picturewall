//
// C++ Implementation: GoogleSearcher
//
// Description:
//
//
// Author: vishwajeet <vishwajeet.dusane@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "GoogleSearcher.h"

#include <QWebFrame>

CGoogleSearcher::CGoogleSearcher(QObject *parent)
        : QObject(parent)
{
    m_pGoogleAJAXapiMedia = new QWebView();

    searchResultLabel = 0;
    connect(m_pGoogleAJAXapiMedia,SIGNAL(loadFinished(bool)),this,SLOT(searchComplete()));

    connect(this,SIGNAL(doParsing(QString)),this,SLOT(parse(QString)));

}


CGoogleSearcher::~CGoogleSearcher()
{
    delete m_pGoogleAJAXapiMedia;
}

void CGoogleSearcher::setSearchString(const QString &searchString)
{
    this->searchString = searchString;
}


void CGoogleSearcher::search(QString searchString)
{
    if (searchString.isEmpty())
    {
        searchString = this->searchString;
    }
    else
    {
        this->searchString = searchString;
        searchResultLabel=0;

    }


    if (searchResultLabel > 20)
    {
        return;
    }


    QString searchUrl = "http://ajax.googleapis.com/ajax/services/search/images?v=1.0&q="+searchString+"&start="+QString().setNum(searchResultLabel + 4)+"&filter=0&rsz=large";
    searchUrl = searchUrl.replace(' ','+');
    m_pGoogleAJAXapiMedia->setUrl(searchUrl);
    searchResultLabel ++;
}

void CGoogleSearcher::searchComplete()
{

    QWebFrame *mainFrame = m_pGoogleAJAXapiMedia->page()->mainFrame();
    QString frameText = mainFrame->toHtml();

    emit doParsing(frameText);
    search();

}

void CGoogleSearcher::parse(QString rawData)
{
    QHash<QString,QString> parsedImageRecord;

    QStringList rawChunk = rawData.split("{");


    for (int i=0;i<rawChunk.count();++i)
    {

        if (!isImageData(rawChunk.at(i)))
        {

            continue;
        }

        parsedImageRecord["url"] = fetchDataFromRawChunk("url",rawChunk.at(i));
        parsedImageRecord["tbUrl"] = fetchDataFromRawChunk("tbUrl",rawChunk.at(i));
        parsedImageRecord["tbUrl"].replace("\\u003d","=");
        emit parsedResult(parsedImageRecord);
        parsedImageRecord.clear();
    }

}

bool CGoogleSearcher::isImageData(const QString &rawData)
{
    if (rawData.contains("GsearchResultClass") && rawData.contains("GimageSearch") )
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString CGoogleSearcher::fetchDataFromRawChunk(const QString &key,const QString &rawData)
{
    QString value;
    QStringList imageDataList = rawData.split(',');

    for (int i =0;i<imageDataList.count();++i)
    {
        if (imageDataList.at(i).contains(QString("\"")+key+QString("\"")))
        {

            value = imageDataList.at(i).split("\":\"").at(1);
            value = value.remove("\"",Qt::CaseInsensitive).remove("}",Qt::CaseInsensitive);
            return value;
        }
    }

    return value;
}


