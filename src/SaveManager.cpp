#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "SongData.h"
#include "ChannelWidget.h"
#include "ui_ChannelWidget.h"
#include <QFileInfo>
#include <KF5/KArchive/KZip>

SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

SongData SaveManager::load(const QString loadpath)
{
	//// Création d'un dossier temporaire ////
	tempdir.reset(new QTemporaryDir);

	//// Extraction de l'archive dans le dossier temp ////
	KZip archive(loadpath);

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
	sd.tempo  = settings.value("General/tempo").toInt();
	sd.name   = settings.value("General/songName").toString().toStdString();
	sd.sigNumerateur = settings.value("General/sigNumerator").toInt();
	sd.sigDenominateur = settings.value("General/sigDenominator").toInt();

	for(int i = 0; i < count; ++ i)
	{
		sd.tracks.emplace_back(settings.value(QString("Track%1/name").arg(i)).toString().toStdString(),
						  (tempdir->path() + "/" + settings.value(QString("Track%1/filename").arg(i)).toString()).toStdString(),
						  settings.value(QString("Track%1/volume").arg(i)).toInt(),
						  settings.value(QString("Track%1/pan").arg(i)).toInt());
	}

	return sd;
}

void SaveManager::save(const QString savepath, MainWidget* manager)
{
	//// Ouverture du fichier .ini dans le dossier temporaire
	QStringList nameFilter("*.ini");
	QDir directory(tempdir->path());
	QString iniFile = tempdir->path() + "/" + directory.entryList(nameFilter).first();

	//// Modification
	QSettings settings(iniFile, QSettings::IniFormat);
	int count = settings.value("General/trackCount").toInt();

	for(int i = 0; i < count; ++ i)
	{
		settings.setValue(QString("Track%1/volume").arg(i), manager->ui->channelList->channels[i]->ui->volume->value());
		settings.setValue(QString("Track%1/pan").arg(i), manager->ui->channelList->channels[i]->ui->pan->value());
	}

	settings.sync();

	//// Écriture dans l'archive
	KZip archive(savepath);

	if (!archive.open(QIODevice::ReadWrite))
	{
		throw std::runtime_error("Fichier invalide.");
	}

	qDebug() << iniFile << directory.entryList(nameFilter).first();

	archive.addLocalFile(iniFile, directory.entryList(nameFilter).first());
}
