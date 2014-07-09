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

		std::shared_ptr<QTemporaryDir> tempdir{};


	public slots:
		SongData load(QString name);

};

#endif // SAVEMANAGER_H
