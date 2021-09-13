#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include "base_types.h"
#include "recipe_item_model.h"
#include <QSharedPointer>
#include "recipe_item_model.h"
#include "recipes_list_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
