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
#include "PictureWallMainWindow.h"


#include <QFileDialog>

CPictureWallMainWindow::CPictureWallMainWindow(QWidget *parent)
 : QWidget(parent)
{
	setupUi(this);

	m_pImageToSearchOnGoogle->setVisible(false);

	m_pGoogleSearcherInstance = new CGoogleSearcher(this);

	connect(m_pDirectorySelectionToolButton,SIGNAL(pressed()),this,SLOT(changeDirectorySlot()));
        connect(this,SIGNAL(directoryChangedSignal(QString)),m_pMainPictureWallArea,SLOT(loadImagesFromDirectoryRecursivelySlot(QString)));

	connect(m_pGoogleImageSearchOption,SIGNAL(toggled ( bool )),this,SLOT(selectGoogleSearchOption(bool)));
	connect(m_pLocalImageViewerOption,SIGNAL(toggled ( bool )),this,SLOT(selectLocalImageViewerSelected(bool)));

	connect(m_pImageToSearchOnGoogle,SIGNAL(returnPressed ()),this,SLOT(startNewGoogleSearch()));

	connect(this,SIGNAL(googleSearchResult(QHash<QString,QString>)),m_pMainPictureWallArea,SLOT(showGoogleImageResult(QHash<QString,QString>)));




}


CPictureWallMainWindow::~CPictureWallMainWindow()
{
	if(m_pGoogleSearcherInstance != NULL)
	{	
		delete m_pGoogleSearcherInstance;
	}
}

void CPictureWallMainWindow::changeDirectorySlot()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 m_pCurrentOpenDirectoryPathLabel->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

	if(!dir.isEmpty())
	{
		m_pCurrentOpenDirectoryPathLabel->setText(dir);	
		emit directoryChangedSignal(dir);
	}
	
	delete m_pGoogleSearcherInstance;
	m_pGoogleSearcherInstance =0;
}

void CPictureWallMainWindow::selectGoogleSearchOption(bool checked )
{
	if(checked)
	{
		m_pImageToSearchOnGoogle->setVisible(true);
		m_pCurrentOpenDirectoryPathLabel->setVisible(false);
		m_pDirectorySelectionToolButton->setVisible(false);
		emit googleSearchOptionSelected();
	}

}

void CPictureWallMainWindow::selectLocalImageViewerSelected(bool checked )
{
	if(checked)
	{
		m_pImageToSearchOnGoogle->setVisible(false);
		m_pCurrentOpenDirectoryPathLabel->setVisible(true);
		m_pDirectorySelectionToolButton->setVisible(true);
		emit localImageViewerSelected();
	}


}

void CPictureWallMainWindow::startNewGoogleSearch()
{
	if(m_pGoogleSearcherInstance != NULL)
	{	
		delete m_pGoogleSearcherInstance;
	}

	m_pGoogleSearcherInstance = new CGoogleSearcher(this);
	connect(m_pGoogleSearcherInstance,SIGNAL(parsedResult(QHash<QString,QString>)),this,SIGNAL(googleSearchResult(QHash<QString,QString>)));

	m_pGoogleSearcherInstance->setSearchString(m_pImageToSearchOnGoogle->text());
	m_pGoogleSearcherInstance->search(m_pImageToSearchOnGoogle->text());
	m_pMainPictureWallArea->cleanAllResults();
}



