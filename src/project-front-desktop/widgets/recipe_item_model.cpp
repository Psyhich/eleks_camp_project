#include "recipe_item_model.h"
#include <QSharedPointer>


RecipesList::RecipesList(QList<BaseTypes::Recipe*> recipesToAdd){
  for(BaseTypes::Recipe* recipe : recipesToAdd){
	recipes.append(QSharedPointer<BaseTypes::Recipe>(recipe));
	emit this->recipeAdded(recipes.back());
  }
}

inline QSharedPointer<BaseTypes::Recipe> RecipesList::operator[](int index){ return recipes[index]; }

QSharedPointer<BaseTypes::Recipe> RecipesList::get(unsigned int recipeID){
  for(QSharedPointer<BaseTypes::Recipe> recipe : recipes){
	if(recipe->getId() == recipeID){
	  return recipe;
	}
  }
  return nullptr;
}
// Add/Remove
void RecipesList::removeRecipe(unsigned int recipeID){
  for(int index = 0; index < recipes.count(); index++){
	if(recipes[index]->getId() == recipeID){
	  recipes.removeAt(index);
	  emit recipeRemoved(recipeID);
	  break;
	}
  }
}
void RecipesList::addRecipe(BaseTypes::Recipe* recipeToAdd){
  recipes.append(QSharedPointer<BaseTypes::Recipe>(recipeToAdd));
  emit recipeAdded(recipes.back());
}
