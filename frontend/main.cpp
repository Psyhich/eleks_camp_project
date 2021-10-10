#include "widgets/mainwindow.h"
#include "connections/connection_manager.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[]) {
	// Registring QList of unsigned int as meta type
	// To store favorite recipes IDs in favorites manager
	qRegisterMetaType<QList<unsigned int> >("QList<unsigned int>");

	Connections::ConnectionManager::getManager();

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
