SOURCES += main.cpp \
 PictureWallMainWindow.cpp \
 MainPictureWallArea.cpp \
 ImageProxyWidget.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = picturewall
OBJECTS_DIR = ../bin/tmp
MOC_DIR = ../bin/tmp

DESTDIR = ../bin
QT += gui
HEADERS += PictureWallMainWindow.h \
MainPictureWallArea.h \
ImageProxyWidget.h
FORMS += PictureWallMainWindow.ui

