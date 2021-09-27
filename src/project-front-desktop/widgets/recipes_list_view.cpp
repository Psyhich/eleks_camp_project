#include "recipes_list_view.h"
#include <QLabel>
#include <QVBoxLayout>

RecipesListView::RecipesListView(QWidget *parrent) : QWidget(parrent) {
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
}

void RecipesListView::addRecipe(QSharedPointer<BaseTypes::Recipe> recipeToAdd){
	RecipeRowView* currentRow = new RecipeRowView(recipeToAdd, this);
	// Connecting newly created row to own signals

	connect(currentRow, &RecipeRowView::favoriteClicked, this, &RecipesListView::requestFavoriteRecipe);
	connect(currentRow, &RecipeRowView::openClicked, this, &RecipesListView::requestOpenRecipe);
	connect(currentRow, &RecipeRowView::editClicked, this, &RecipesListView::requestEditRecipe);

	rows.append(currentRow);
	layout()->addWidget(currentRow);

}

void RecipesListView::removeRecipe(unsigned int recipeID){
  for(int index = 0; index < rows.count(); index++){
	if(rows[index]->getId() == recipeID){
	  rows[index]->deleteLater();
	  rows.removeAt(index);
	  break;
	}
  }
}
