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
	QSharedPointer<BaseTypes::Recipe> recipe = QSharedPointer<BaseTypes::Recipe>(new BaseTypes::Recipe(0));

	recipe->name = "Soup";
	recipe->courses.insert("Starter");
	recipe->cuisines.insert("Ukraine");
	recipe->ingredients = {{"Liter of water", 1}, {"Bowl", 1}, {"Spoon", 1}};
	recipe->outWeight = 1000;
	recipe->outCalories = 10;
	recipe->recipeText = "Take liter of water and boil it until it's hot";
	recipe->presentationText = "Pour hot water into bowl and eat with spoon";

	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);
	ui->RecipesView->addRecipe(recipe);


}

MainWindow::~MainWindow() { delete ui; }
