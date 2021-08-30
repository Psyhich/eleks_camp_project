#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include "base_types.h"
#include "recipe_item_model.h"
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QList<QSharedPointer<BaseTypes::Recipe>> recipes;

  ui->listView->setModel(new RecipesListModel(recipes));
}

MainWindow::~MainWindow() { delete ui; }
