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
#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QDialog>
#include <QLabel>

#include "ImageHolder.h"

/**
	@author vishwajeet <vishwajeet.dusane@gmail.com>
*/
class CustomLabel : public QDialog
{
Q_OBJECT
public:
	CustomLabel ( QWidget *parent = 0 );
	virtual	~CustomLabel();

public slots:
		void setPixmap(const QPixmap& );
		void setImagePath(const QString&);
		void imageZoomedIn();
		void imageZoomedOut();
		
private:
		
		CImageHolder *m_pImageHolderInstance;
		QPixmap m_VisibleImageState;
};	

#endif
