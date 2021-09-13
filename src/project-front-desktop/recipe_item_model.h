#ifndef RECIPE_ITEM_MODEL_H
#define RECIPE_ITEM_MODEL_H

#include <QObject>
#include "base_types.h"
#include <QSharedPointer>
#include <QAbstractItemModel>
#include <qabstractitemmodel.h>

class RecipesList  : public QObject{
Q_OBJECT
  QList<QSharedPointer<BaseTypes::Recipe>> recipes;

public:
  RecipesList() {}
  RecipesList(QList<BaseTypes::Recipe *> recipesToAdd);

  inline QSharedPointer<BaseTypes::Recipe> operator[](int index);
  inline QSharedPointer<BaseTypes::Recipe> get(unsigned int recipeID);

  void removeRecipe(unsigned int recipeID);
  void addRecipe(BaseTypes::Recipe *recipeToAdd);
signals:
  void recipeAdded(QSharedPointer<BaseTypes::Recipe> recipeAdded);
  void recipeRemoved(unsigned int removedID);

};

#endif // RECIPE_ITEM_MODEL_H
