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
	CGoogleSearcher class is responsible creating a query in google image searched API format, execute query, fetch result, parse result and extract only thubnail view URL and original image url.CGoogleSearcher class also does recursive search for the same query so that most of the results can be obtaied. So far 20 iterations are done i.e. 20 times the same query is requested on google image search.

	CGoogleSearcher class emit signal for every single search result parsedResult. emited result contains thumbnail view URL and original image URL.

	As google image search API is using AJAX. CGoogleSearcher class uses QWebView class object to query over google which fetches the result from it. This feature is available in Qt4.5.x onwards.

	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CGoogleSearcher : public QObject
{
    Q_OBJECT
public:
    CGoogleSearcher(QObject *parent = 0);

    ~CGoogleSearcher();

    /**
     * This function set the new query that will queried to google for images.

     * @param searchString query string that need to be queried to google for images 
     */
    void setSearchString(const QString &searchString);


public slots:
    /**
     *  If called from outside, it will start new search using the passes query string, if the passes parameter is empty then deafault query will be used to start the search

	This slot iterate over 20 iteration once started and same query is queried to google image server for more results

     * @param searchString 
	@see setSearchString
     */
    void search(QString searchString= QString());

private slots:
    /**
     * This slot is called internally when the query result is fetched from the google server.
     */
    void searchComplete();

    /**
     * This slot is called when query result is fetched from the server and raw data need to be parsed. This slot only extracts thumbnail view URL and Original image URL from the raw data. Rest of the data is ignored. 
     * @param  rawData result query data from google server
     */
    void parse(QString rawData);

signals:
    /**
     * This signal is emiited for single record found in the searched query result. Record emited by this function is QHash which is key value pair based data.
	Emited data only contains thumbnail view URL and original image	URL

 	For Example:
		To access original image URL key is "url" 
		To access thumbnail view URL key is "tbUrl"
		
     * @param  
     */
    void parsedResult(QHash<QString,QString>);

	
    /**
     * This signal is emited when google server has responded with query result.  
     * @param  rawData google server return response for the query
     */
    void doParsing(QString rawData);

private:

    /**
     * 
     * @param  imageData Query result from google server
     * @return true if the data is valid response from the google server and it contains required information for the searched images
     */
    bool isImageData(const QString &imageData);

	
    /**
     * This function parsed the required key within the raw data or query result from google server 
     * @param key Key that need to be searched withing raw data
     * @param rawData Query response from google server where key needs to be searched
     * @return value of that key if found else return empty string 
     */
    QString fetchDataFromRawChunk(const QString &key,const QString &rawData);

private:
    QWebView *m_pGoogleAJAXapiMedia;
    int searchResultLabel;
    QString searchString;
};

#endif
