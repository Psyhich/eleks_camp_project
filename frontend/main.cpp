#include <QApplication>
#include <QString>
#include <QStandardPaths>
#include <QFile>

#include "mainwindow.h"
#include "connection_manager.h"

int main(int argc, char *argv[]) {
	// Loading default database from resources to default path if it's not set
	QString path = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] + "/cookbook.db";
	if(!QFile::exists(path)){
	  QFile defaultDB(":/resources/../data/cookbook.db");
	  defaultDB.copy(path);
	  defaultDB.close();
	}

	Connections::ConnectionManager::getManager();

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
