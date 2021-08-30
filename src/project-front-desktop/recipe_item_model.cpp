#include "recipe_item_model.h"
#include <QSharedPointer>

RecipesListModel::RecipesListModel(
    QList<QSharedPointer<BaseTypes::Recipe>> recipes, QObject *parent)
    : QAbstractListModel(parent) {
  this->recipes = recipes;
  this->setParent(parent);
}

int RecipesListModel::rowCount(const QModelIndex &parent) const {
  return recipes.count();
}
int RecipesListModel::columnCount(const QModelIndex &parent) const {
  return MODEL_PRESENTATION_COLUMN;
}

QVariant RecipesListModel::data(const QModelIndex &index, int role) const {
  // Validating
  if (!index.isValid() || index.row() >= rowCount() ||
      index.column() > columnCount() || role != Qt::ItemDataRole::DisplayRole) {
    return QVariant();
  }
  BaseTypes::Recipe *foundRecipe = recipes[index.row()].get();
  switch (index.column()) {
  case MODEL_NAME_COLUMN: {
    return QVariant(foundRecipe->getName());
  }
  case MODEL_ID_COLUMN: {
    return QVariant(foundRecipe->getId());
  }
  case MODEL_TAGS_COLUMN: {
    return QVariant(foundRecipe->getTags());
  }
  case MODEL_INGREDIENTS_COLUMN: {
    QMap<QString, QVariant> ingredients;
    for (auto pairKey : foundRecipe->getIngredients().keys()) {
      ingredients.insert(pairKey,
                         QVariant(foundRecipe->getIngredients()[pairKey]));
    }
    return QVariant(ingredients);
  }
  case MODEL_CALORIES_COLUMN: {
    return QVariant(foundRecipe->getCalories());
  }
  case MODEL_WEIGHT_COLUMN: {
    return QVariant(foundRecipe->getWeight());
  }
  case MODEL_MIN_PORTIONS_COLUMN: {
    return QVariant(foundRecipe->getBasePortionsCount());
  }
  case MODEL_TEXT_COLUMN: {
    return QVariant(foundRecipe->getRecipeText());
  }
  case MODEL_PRESENTATION_COLUMN: {
    return QVariant(foundRecipe->getPresentationText());
  }
  }
  return QVariant();
}

bool RecipesListModel::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  return false;
}
