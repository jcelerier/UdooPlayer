#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "SongData.h"

#include <QFileInfo>
#include <KF5/KArchive/KZip>

SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

SongData SaveManager::load(QString loadpath)
{
	//// Création d'un dossier temporaire ////
	tempdir.reset(new QTemporaryDir);

	//// Extraction de l'archive dans le dossier temp ////
	KZip archive(loadpath);
	qDebug() << loadpath;

	if (!archive.open(QIODevice::ReadOnly))
	{
		throw std::runtime_error("Fichier invalide.");
	}

	const KArchiveDirectory *root = archive.directory();

	root->copyTo(tempdir->path(), true);

	archive.close();

	//// Lecture des données
	// On cherche le .ini :
	QStringList nameFilter("*.ini");
	QDir directory(tempdir->path());
	QString iniFile = tempdir->path() + "/" + directory.entryList(nameFilter).first();

	//// Chargement
	QSettings settings(iniFile, QSettings::IniFormat);
	SongData sd;

	int count = settings.value("General/trackCount").toInt();
	sd.tempo =  settings.value("General/tempo").toInt();
	sd.tracks.reserve(count);

	for(int i = 0; i < count; ++ i)
	{
		sd.tracks.emplace(sd.tracks.begin() + i,
						  settings.value(QString("Track%1/name").arg(i)).toString().toStdString(),
						  (tempdir->path() + "/" + settings.value(QString("Track%1/filename").arg(i)).toString()).toStdString(),
						  settings.value(QString("Track%1/volume").arg(i)).toInt(),
						  settings.value(QString("Track%1/pan").arg(i)).toInt());
	}

	return sd;
}
