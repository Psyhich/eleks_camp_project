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

server::recipe::Recipe Recipe::translateToServer() const {
	std::string course;
	if(courses.size() > 0) {
	  course = courses.values()[0].toLower().toStdString();
	}

	std::string cusine;
	if(cusines.size() > 0) {
	  cusine = cusines.values()[0].toLower().toStdString();
	}

	server::recipe::IngredientsList ingredients;
	for(auto key : this->ingredients.keys()) {
		server::recipe::IngredientAmount amount;
		const Recipe::IngredientAmount &my_amount = this->ingredients.value(key);
		amount.quantity = my_amount.quantity;
		amount.unit = my_amount.unit.toLower().toStdString();

		ingredients.insert(std::pair<std::string, server::recipe::IngredientAmount>(key.toLower().toStdString(), amount));
	}

	return server::recipe::Recipe(this->hasInitializedID ? *this->getID() : 0,
					name.toStdString(),
					course,
					cusine,
					ingredients,
					outCalories,
					outWeight,
					outPortions,
					recipeText.toStdString(),
					presentationText.toStdString(),
					remarks.toStdString());
}

void Recipe::translateFromServer(server::recipe::Recipe recipeToTranslate) {
	this->id = recipeToTranslate.getId();
	this->name = QString::fromStdString(recipeToTranslate.getName());

	this->courses = {QString::fromStdString(recipeToTranslate.getCourse())};
	this->cusines = {QString::fromStdString(recipeToTranslate.getCuisine())};

	// Translating ingredients
	for(auto pair : recipeToTranslate.getIngredients()){
	  BaseTypes::Recipe::IngredientAmount amount;
	  amount.quantity = pair.second.quantity;
	  amount.unit = QString::fromStdString(pair.second.unit);
	  this->ingredients.insert(QString::fromStdString(pair.first), amount);
	}

	this->outWeight = recipeToTranslate.getOutWeight();
	this->outCalories = recipeToTranslate.getOutCalories();
	this->outPortions = recipeToTranslate.getOutPortions();

	this->recipeText = QString::fromStdString(recipeToTranslate.getPreparation());
	this->presentationText = QString::fromStdString(recipeToTranslate.getPresentation());
	this->remarks = QString::fromStdString(recipeToTranslate.getRemarks());
}
