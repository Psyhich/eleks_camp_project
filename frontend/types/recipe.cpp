#include "recipe.h"

using namespace BaseTypes;

Recipe::Recipe(unsigned int recipeID) {
	id = recipeID;
	hasInitializedID = true;
}

const unsigned int* Recipe::getID() const {
  if(hasInitializedID) {
	return &id;
  }
  return nullptr;
}
