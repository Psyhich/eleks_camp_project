#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include "types/base_types.h"
#include "recipe_item_model.h"
#include <QSharedPointer>
#include "recipe_item_model.h"
#include "recipes_list_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// Setting invisible widgets
	ui->SearchFilters->setHidden(true);

	// Hiding close button for search tab
	ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
	ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide)->hide();
	QSet<QString> courses;
	courses.insert("Starter");

	QSet<QString> cusines;
	cusines.insert("Ukraine");

	QSharedPointer<BaseTypes::Recipe> recipe = QSharedPointer<BaseTypes::Recipe>(new BaseTypes::LocalRecipe(0, "Soup", courses, cusines, QMap<QString, int>(), 1000, 1000, 1, "Take water and boil it", ""));
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);


}

MainWindow::~MainWindow() { delete ui; }
