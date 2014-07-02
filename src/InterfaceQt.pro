QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceQt
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
		MainWindow.cpp \
	ChannelWidget.cpp \
	ChannelListWidget.cpp \
	MainWidget.cpp \
	PlayThread.cpp

HEADERS  += MainWindow.h \
	ChannelWidget.h \
	ChannelListWidget.h \
	MainWidget.h \
	PlayThread.h

FORMS    += MainWindow.ui \
	ChannelWidget.ui \
	ChannelListWidget.ui \
	MainWidget.ui


INCLUDEPATH += $$PWD/../watermarking/src/libwatermark
DEPENDPATH += $$PWD/../watermarking/src/libwatermark

LIBS+=-lsndfile -lfftw3 -lgcov -lportaudiocpp -lportaudio
