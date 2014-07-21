QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = InterfaceQt
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++1y

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Ofast -march=native -flto -fopenmp
QMAKE_LFLAGS_RELEASE -= -Wl,-O1
QMAKE_LFLAGS_RELEASE += -Wl,-O3 -Wl,-flto

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
	TrackingSlider.cpp \
	SerialManager.cpp

HEADERS  += MainWindow.h \
	ChannelWidget.h \
	ChannelListWidget.h \
	MainWidget.h \
	PlayThread.h \
	SongData.h \
	SaveManager.h \
	TrackingSlider.h \
	SerialManager.h

FORMS    += MainWindow.ui \
	ChannelWidget.ui \
	ChannelListWidget.ui \
	MainWidget.ui

INCLUDEPATH += $$PWD/../../watermarking/src/libwatermark
DEPENDPATH += $$PWD/../../watermarking/src/libwatermark

LIBS+= -lgomp -lgcov -lportaudiocpp -lportaudio -lavcodec -lavformat -lavutil -lsndfile


INCLUDEPATH += /usr/local/include/KF5/KArchive
LIBS += -lKF5Archive

RESOURCES += \
	Resources.qrc

OTHER_FILES += \
	TrackingSliderVerticalEnabled.qss \
	TrackingSliderVerticalDisabled.qss \
	TrackingSliderHorizontalEnabled.qss \
	TrackingSliderHorizontalDisabled.qss
