#include <QSharedPointer>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "recipe_item_model.h"
#include "recipe_item_model.h"
#include "recipes_list_view.h"
#include "recipe_view_tab.h"

#include "types/recipe.h"
#include "connections/connection_manager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// Hiding close button for search tab
	QWidget *tabButton = ui->RecipeTabs->tabBar()->tabButton(0, QTabBar::RightSide);
	tabButton->resize(0, 0);
	tabButton->hide();

}

MainWindow::~MainWindow() { delete ui; }
