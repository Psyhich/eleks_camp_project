#include "widgets/mainwindow.h"
#include "connections/connection_manager.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[]) {
	Connections::ConnectionManager::getManager();

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
