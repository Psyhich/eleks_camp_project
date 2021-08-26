#include "base_types.h"

namespace QBaseTypes {
  // Recipe methods
  // Getters
  inline unsigned int Recipe::getId() const { return id; }
  inline const QString&Recipe::getName() const { return name; }
  inline const QList<QString>& Recipe::getTags() const { return tags; }

  inline const QHash<QString, int>& Recipe::getIngredients() const { return ingredients; }
  inline double Recipe::getCalories() const { return outCalories; }
  inline double Recipe::getWeight() const { return outWeight; }
  inline unsigned int Recipe::getBasePortionsCount() const { return outPortions; }

  inline const QString& Recipe::getRecipeText() const { return recipeText; }
  inline const QString& Recipe::getPresentationText() const { return presentationText; }

  // LocalRecipe methods
  bool LocalRecipe::update(){
	// TODO implement
	return true;
  }
  bool LocalRecipe::load(){
	// TODO implement
	return false;
  }

  // RemoteRecipe methods
  bool RemoteRecipe::update(){
	// TODO implement
	return true;
  }
  bool RemoteRecipe::load(){
	// TODO implement
	return false;
  }


}
