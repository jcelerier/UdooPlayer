QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceQt
TEMPLATE = app
CONFIG += c++11

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE += -O3 -fopenmp -march=native


SOURCES += main.cpp\
		MainWindow.cpp \
	ChannelWidget.cpp \
	ChannelListWidget.cpp \
	MainWidget.cpp \
	PlayThread.cpp \
	SongData.cpp \
	SaveManager.cpp \
	TrackingSlider.cpp

HEADERS  += MainWindow.h \
	ChannelWidget.h \
	ChannelListWidget.h \
	MainWidget.h \
	PlayThread.h \
	SongData.h \
	SaveManager.h \
	TrackingSlider.h

FORMS    += MainWindow.ui \
	ChannelWidget.ui \
	ChannelListWidget.ui \
	MainWidget.ui

INCLUDEPATH += $$PWD/../../watermarking/src/libwatermark
DEPENDPATH += $$PWD/../../watermarking/src/libwatermark

LIBS+=-lsndfile -lfftw3 -lgcov -lportaudiocpp -lportaudio -lavcodec -lavformat -lavutil
