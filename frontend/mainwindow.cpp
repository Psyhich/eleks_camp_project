#include <QSharedPointer>
#include <QInputDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "recipe_view_tab.h"

#include "front_recipe.h"
#include "connection_manager.h"

bool getAdressAndPort(QString &address, quint16 &port);

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	tabManager = new TabManager(ui->centralwidget);
	ui->centralwidget->layout()->addWidget(tabManager);
	// Hiding close button for search tab

	// Connecting menu button to tab manager to create new recipes
	QObject::connect(ui->actionCreate, &QAction::triggered,
					 [&](){
	  tabManager->editRecipe(QSharedPointer<BaseTypes::Recipe>());
	});

	// Connecting other menu buttons to lambdas that will change connection types
	QObject::connect(ui->actionConnect_to_local, &QAction::triggered, [&](){
	  Connections::ConnectionManager::getManager().toggleToLocal();
	  ui->actionConnect_to_database->setChecked(false);
	  ui->actionConnect_to_local->setChecked(true);
	});

	QObject::connect(ui->actionConnect_to_database, &QAction::triggered, [&](){
		QString address;
		quint16 port;

		bool isPressedOK = getAdressAndPort(address, port);

		if(!isPressedOK || address.isEmpty() || (port == 0) ){
		  return;
		}

		Connections::ConnectionManager::getManager().toggleToRemote(address, port);
		ui->actionConnect_to_database->setChecked(true);
		ui->actionConnect_to_local->setChecked(false);
	});

}

bool getAdressAndPort(QString &address, quint16 &port){
	bool isPressedOK = false;
	address = QInputDialog::getText(nullptr,
									"Input address of remote",
									"Enter address of remote:",
									QLineEdit::EchoMode::Normal,
									"",
									&isPressedOK);

	if(!isPressedOK) { return isPressedOK; }
	port = QInputDialog::getInt(nullptr,
								"Input port",
								"Enter port of remote:",
								0, 0, 65535, 1, &isPressedOK);
	return isPressedOK;
}

MainWindow::~MainWindow() { delete ui; }
