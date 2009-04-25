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

	connect(m_pDirectorySelectionToolButton,SIGNAL(pressed()),this,SLOT(changeDirectorySlot()));
        connect(this,SIGNAL(directoryChangedSignal(QString)),m_pMainPictureWallArea,SLOT(loadImagesFromDirectoryRecursivelySlot(QString)));
}


CPictureWallMainWindow::~CPictureWallMainWindow()
{
	qDebug("Destructor  CPictureWallMainWindow");
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
	

}


