/***************************************************************************
 *   Copyright (C) 2007 by Gokul   *
 *   gokul@linux-7q2y   *
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
#include "CustomLabel.h"

#include <QIcon>
#include <QStringList>

#include <QHBoxLayout>
#include <QWheelEvent>

CustomLabel::CustomLabel(QWidget *parent)
 : QDialog(parent)
{
	
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    
    label = new CImageHolder(this);
    
	 horizontalLayout->setMargin(0);
     horizontalLayout->addWidget(label);
}


CustomLabel::~CustomLabel()
{

}

void CustomLabel::setPixmap(const QPixmap& image)
{
	label->setPixmap(image);
}

void CustomLabel::setImagePath(const QString& path)
{
	label->setImagePath(path);
}

void CustomLabel::imageZoomedIn()
{
	m_VisibleImageState = label->pixmap();
	label->setOriginalPixmap();
}

void CustomLabel::imageZoomedOut()
{
	label->setPixmap(m_VisibleImageState);
	//label->setZoomOut();
}

