#include <QStandardItemModel>
#include <QSharedPointer>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "recipe_item_model.h"
#include "recipe_item_model.h"
#include "recipes_list_view.h"
#include "types/recipe.h"
#include "connections/connection_manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// Setting invisible widgets
	ui->SearchFilters->setHidden(true);

	// Hiding close button for search tab
	ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
	ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide)->hide();
	QSharedPointer<BaseTypes::Recipe> recipe(new BaseTypes::Recipe());
	recipe->name = "Added";

	Connections::ConnectionManager::getManager().sendRecipe(recipe);


	QSharedPointer<BaseTypes::Requests::SearchQuery> query(
		new BaseTypes::Requests::SearchQuery(
		  {},"Added",{},{},{},false)
		);
	auto resp = Connections::ConnectionManager::getManager().runSearch(query);
	for(auto recipe : *resp){
	  ui->RecipesView->addRecipe(recipe);
	}

}

MainWindow::~MainWindow() { delete ui; }
