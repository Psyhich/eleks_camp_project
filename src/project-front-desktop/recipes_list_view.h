#ifndef RECIPES_LIST_VIEW_H
#define RECIPES_LIST_VIEW_H

#include <QScrollArea>
#include <QSharedPointer>
#include <QWidget>
#include "base_types.h"
#include "recipe_row_view.h"

class RecipesListView : public QScrollArea
{
  QList<RecipeRowView *> rows;

  public:
	RecipesListView(QWidget *parrent=nullptr);
	~RecipesListView();
  public slots:
	void addRecipe(QSharedPointer<BaseTypes::Recipe> recipe);
	void removeRecipe(unsigned int recipeID);

};

#endif // RECIPES_LIST_VIEW_H
