#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>

#include <QTemporaryDir>
#include <memory>
#include <SongData.h>

/**
 * @brief The SaveManager class
 *
 * Ouverture des fichiers de sauvegarde
 *
 */
class MainWidget;
class SaveManager : public QObject
{
		Q_OBJECT
	public:
		explicit SaveManager(QObject *parent = 0);

		// Dossier temporaire ou sont extraits les données contenues dans les fichiers .song
		std::shared_ptr<QTemporaryDir> tempdir{};

		// Charge un fichier
		SongData load(const QString name);

		// Utilisé pour sauvegarder les paramètres de vol / pan..
		void save(const QString name, MainWidget* manager);

};

#endif // SAVEMANAGER_H
