#include <QSharedPointer>
#include <QInputDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "recipe_item_model.h"
#include "recipe_item_model.h"
#include "recipes_list_view.h"
#include "recipe_view_tab.h"

#include "types/recipe.h"
#include "connections/connection_manager.h"

void getAdressAndPort(QString &address, quint16 &port);

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// Hiding close button for search tab
	QWidget *tabButton = ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide);
	tabButton->resize(0, 0);
	tabButton->hide();

	// Connecting menu button to tab manager to create new recipes
	QObject::connect(ui->actionCreate, &QAction::triggered,
					 [&](){ ui->RecipeTabs->editRecipe(QSharedPointer<BaseTypes::Recipe>()); });

	// Connecting other menu buttons to lambdas that will change connection types
	QObject::connect(ui->actionConnect_to_local, &QAction::triggered, [&](){
	  Connections::ConnectionManager::getManager().toggleToLocal();
	});

	QObject::connect(ui->actionConnect_to_database, &QAction::triggered, [&](){
	  QString address;
	  quint16 port;
	  getAdressAndPort(address, port);
	  Connections::ConnectionManager::getManager().toggleToRemote(address, port);
	});



}

void getAdressAndPort(QString &address, quint16 &port){
  address = QInputDialog::getText(nullptr, "Input address of remote", "Enter address of remote:");
  port = QInputDialog::getInt(nullptr, "Input port", "Enter port of remote:");
}

MainWindow::~MainWindow() { delete ui; }
