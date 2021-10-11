﻿#include <QLabel>
#include <QVBoxLayout>

#include "recipes_list_view.h"

RecipesListView::RecipesListView(QWidget *parrent) : QWidget(parrent) {
	this->setLayout(new QVBoxLayout(this));
	this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
}

void RecipesListView::addRecipe(QSharedPointer<BaseTypes::Recipe> recipeToAdd){
	//if(recipeCache.contains(recipeToAdd)){
		// Calling update methods and updating row representing this recipe
		//emit recipeUpdated(*recipeToAdd->getID());

	//}
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

void RecipesListView::clearRecipes(){
  // Deleting rows, but not stored values, we just clean the list
  for(auto row : rows){
	row->deleteLater();
  }
  rows.clear();
}
