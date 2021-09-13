#include "recipes_list_view.h"
#include <QVBoxLayout>

RecipesListView::RecipesListView(QWidget *parrent) : QScrollArea(parrent)
{
  setLayout(new QVBoxLayout(this));
}

RecipesListView::~RecipesListView()
{

  for (RecipeRowView* ptr : rows) {
	ptr->deleteLater();
	delete ptr;
  }
}

void RecipesListView::addRecipe(QSharedPointer<BaseTypes::Recipe> recipeToAdd){
  rows.append(new RecipeRowView(recipeToAdd, this));
}

void RecipesListView::removeRecipe(unsigned int recipeID){
  for(int index = 0; index < rows.count(); index++){
	if(rows[index]->getRecipe()->getId() == recipeID){
	  delete rows[index];
	  rows.removeAt(index);
	  break;
	}
  }
}
