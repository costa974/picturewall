//
// C++ Interface: GoogleSearcher
//
// Description: 
//
//
// Author: vishwajeet <vishwajeet.dusane@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GOOGLESEARCHER_H
#define GOOGLESEARCHER_H

#include <QObject>
#include <QHash>
#include <QWebView>
#include <QThread>

/**
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CGoogleSearcher : public QObject
{
Q_OBJECT
public:
    CGoogleSearcher(QObject *parent = 0);

    ~CGoogleSearcher();

	void setSearchString(const QString &searchString);


public slots:
     void search(QString searchString= QString());
     void searchComplete();	
	
     void parse(QString);

signals:
     void parsedResult(QHash<QString,QString>);
     void doParsing(QString);		

private:

	bool isImageData(const QString &);
	QString fetchDataFromRawChunk(const QString &key,const QString &rawData);

private:
	QWebView *m_pGoogleAJAXapiMedia;
	int searchResultLabel;
	QString searchString;
};

#endif
