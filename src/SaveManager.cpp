#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "SongData.h"

SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

SongData SaveManager::load(QString name)
{
	QSettings settings(name, QSettings::IniFormat);
	SongData sd;

	int count = settings.value("General/trackCount").toInt();
	sd.tracks.reserve(count);

	for(int i = 0; i < count; ++ i)
	{
		sd.tracks.emplace(sd.tracks.begin() + i,
						  settings.value(QString("Track%1/name").arg(i)).toString().toStdString(),
						  settings.value(QString("Track%1/filename").arg(i)).toString().toStdString(),
						  settings.value(QString("Track%1/volume").arg(i)).toInt(),
						  settings.value(QString("Track%1/pan").arg(i)).toInt());
	}

	return sd;
}
