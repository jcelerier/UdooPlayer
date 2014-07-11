QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceQt
TEMPLATE = app
CONFIG += c++11

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE += -O3 -fopenmp -march=native

QMAKE_CXXFLAGS_DEBUG -= -O1
QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0 -Wno-unknown-pragmas

SOURCES += main.cpp\
		MainWindow.cpp \
	ChannelWidget.cpp \
	ChannelListWidget.cpp \
	MainWidget.cpp \
	PlayThread.cpp \
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

LIBS+=-lgomp -lgcov -lportaudiocpp -lportaudio -lavcodec -lavformat -lavutil


INCLUDEPATH += /usr/local/include/KF5/KArchive
LIBS += -lKF5Archive
