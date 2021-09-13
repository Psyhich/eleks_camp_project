#ifndef RECIPE_ROW_VIEW_H
#define RECIPE_ROW_VIEW_H

#include "base_types.h"
#include <QSharedPointer>
#include <QWidget>

class RecipeRowView : public QWidget {
  Q_OBJECT
  QSharedPointer<BaseTypes::Recipe> currentRecipe;

public:
  RecipeRowView(QSharedPointer<BaseTypes::Recipe> recipe, QWidget *parent = nullptr);
  inline const QSharedPointer<const BaseTypes::Recipe> getRecipe() { return currentRecipe; }
};

#endif // RECIPE_ROW_VIEW_H
