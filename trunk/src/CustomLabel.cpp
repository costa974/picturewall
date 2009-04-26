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
    
    m_pImageHolderInstance = new CImageHolder(this);
	horizontalLayout->setMargin(0);	
     horizontalLayout->addWidget(m_pImageHolderInstance);

}


CustomLabel::~CustomLabel()
{
	delete m_pImageHolderInstance;
}

void CustomLabel::setPixmap(const QPixmap& image)
{
	m_VisibleImageState = image;
	m_pImageHolderInstance->setPixmap(image);
}

void CustomLabel::setImagePath(const QString& path)
{
	m_pImageHolderInstance->setImagePath(path);
}

void CustomLabel::imageZoomedIn()
{
	m_pImageHolderInstance->setOriginalPixmap();
}

void CustomLabel::imageZoomedOut()
{
	m_pImageHolderInstance->setPixmap(m_VisibleImageState);
}

