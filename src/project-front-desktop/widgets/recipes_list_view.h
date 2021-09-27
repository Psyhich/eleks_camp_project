#ifndef RECIPES_LIST_VIEW_H
#define RECIPES_LIST_VIEW_H

#include <QScrollArea>
#include <QSharedPointer>
#include <QWidget>
#include "types/base_types.h"
#include "recipe_row_view.h"

class RecipesListView : public QWidget
{
  QList<RecipeRowView *> rows;

  public:
	RecipesListView(QWidget *parrent=nullptr);

 signals:
	void requestOpenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){}
	void requestEditRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit){}
	void requestFavoriteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit){}

  public slots:
	void addRecipe(QSharedPointer<BaseTypes::Recipe> recipeToAdd);
	void removeRecipe(unsigned int recipeID);

};

#endif // RECIPES_LIST_VIEW_H
