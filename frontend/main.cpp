#include "widgets/mainwindow.h"

#include <QApplication>
#include <QString>

int main(int argc, char *argv[]) {
	// Registring QList of unsigned int as meta type
	// To store favorite recipes IDs in favorites manager
	qRegisterMetaTypeStreamOperators<QList<unsigned int> >("QList<unsigned int>");

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
