/********************************************************************************
** Form generated from reading ui file 'PictureWallMainWindow.ui'
**
** Created: Sun Apr 19 11:09:41 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PICTUREWALLMAINWINDOW_H
#define UI_PICTUREWALLMAINWINDOW_H

#include <MainPictureWallArea.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PictureWallMainWindowDesignerUI
{
public:
    QVBoxLayout *verticalLayout;
    CMainPictureWallArea *m_pMainPictureWallArea;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *m_pCurrentOpenDirectoryPathLabel;
    QToolButton *m_pDirectorySelectionToolButton;

    void setupUi(QWidget *PictureWallMainWindowDesignerUI)
    {
        if (PictureWallMainWindowDesignerUI->objectName().isEmpty())
            PictureWallMainWindowDesignerUI->setObjectName(QString::fromUtf8("PictureWallMainWindowDesignerUI"));
        PictureWallMainWindowDesignerUI->resize(634, 485);
        verticalLayout = new QVBoxLayout(PictureWallMainWindowDesignerUI);
        verticalLayout->setMargin(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pMainPictureWallArea = new CMainPictureWallArea(PictureWallMainWindowDesignerUI);
        m_pMainPictureWallArea->setObjectName(QString::fromUtf8("m_pMainPictureWallArea"));
        m_pMainPictureWallArea->setFrameShape(QFrame::NoFrame);
        m_pMainPictureWallArea->setFrameShadow(QFrame::Plain);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        m_pMainPictureWallArea->setBackgroundBrush(brush);
        m_pMainPictureWallArea->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::NonCosmeticDefaultPen|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        m_pMainPictureWallArea->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        m_pMainPictureWallArea->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        m_pMainPictureWallArea->setRubberBandSelectionMode(Qt::IntersectsItemShape);

        verticalLayout->addWidget(m_pMainPictureWallArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_pCurrentOpenDirectoryPathLabel = new QLabel(PictureWallMainWindowDesignerUI);
        m_pCurrentOpenDirectoryPathLabel->setObjectName(QString::fromUtf8("m_pCurrentOpenDirectoryPathLabel"));

        horizontalLayout->addWidget(m_pCurrentOpenDirectoryPathLabel);

        m_pDirectorySelectionToolButton = new QToolButton(PictureWallMainWindowDesignerUI);
        m_pDirectorySelectionToolButton->setObjectName(QString::fromUtf8("m_pDirectorySelectionToolButton"));

        horizontalLayout->addWidget(m_pDirectorySelectionToolButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PictureWallMainWindowDesignerUI);

        QMetaObject::connectSlotsByName(PictureWallMainWindowDesignerUI);
    } // setupUi

    void retranslateUi(QWidget *PictureWallMainWindowDesignerUI)
    {
        PictureWallMainWindowDesignerUI->setWindowTitle(QApplication::translate("PictureWallMainWindowDesignerUI", "Form", 0, QApplication::UnicodeUTF8));
        m_pCurrentOpenDirectoryPathLabel->setText(QApplication::translate("PictureWallMainWindowDesignerUI", "I:\\backup\\My Stuff\\Wallpapers\\BMPS", 0, QApplication::UnicodeUTF8));
        m_pDirectorySelectionToolButton->setText(QApplication::translate("PictureWallMainWindowDesignerUI", "...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PictureWallMainWindowDesignerUI);
    } // retranslateUi

};

namespace Ui {
    class PictureWallMainWindowDesignerUI: public Ui_PictureWallMainWindowDesignerUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREWALLMAINWINDOW_H
