#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>

#include <QTemporaryDir>
#include <memory>
#include <SongData.h>
class SaveManager : public QObject
{
		Q_OBJECT
	public:
		explicit SaveManager(QObject *parent = 0);

		// Dossier temporaire ou sont extraits les .song
		std::shared_ptr<QTemporaryDir> tempdir{};


	public slots:
		// Charge un fichier
		SongData load(QString name);

};

#endif // SAVEMANAGER_H
