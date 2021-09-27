#include "base_types.h"

namespace BaseTypes {
	Recipe::Recipe(unsigned int recipeID) {
		id = recipeID;
		hasInitializedID = true;
	}

	const unsigned int* Recipe::getID(){
	  if(hasInitializedID) {
		return &id;
	  }
	  return nullptr;
	}


}
