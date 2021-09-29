#include "connector.h"


namespace Connections {
  BaseTypes::Recipe translateRecipe(server::recipe::Recipe recipeToTranslate) {
	BaseTypes::Recipe translated(recipeToTranslate.getId());
	translated.name = recipeToTranslate.getName();

  }


}
