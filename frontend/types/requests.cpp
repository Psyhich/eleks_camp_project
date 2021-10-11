#include <QJsonArray>

#include "requests.h"

using namespace BaseTypes::Requests;

// Recipe translation functions
QJsonObject translateRecipToJson(const BaseTypes::Recipe& recipeToTranslate){
	QJsonObject recipe;
	recipe["id"] = (qint64)*recipeToTranslate.getID();

	recipe["name"] = recipeToTranslate.name;
	recipe["course"] = recipeToTranslate.courses.values()[0];
	recipe["cuisine"] = recipeToTranslate.cusines.values()[0];

	recipe["outCalories"] = recipeToTranslate.outCalories;
	recipe["outWeight"] = recipeToTranslate.outWeight;
	recipe["outPortions"] = (qint64)recipeToTranslate.outPortions;

	recipe["preparation"] = recipeToTranslate.recipeText;
	recipe["presentation"] = recipeToTranslate.presentationText;
	recipe["remarks"] = recipeToTranslate.remarks;

	QJsonArray ingredientNameArr;
	QJsonArray ingredientCountArr;
	QJsonArray ingredientUnitArr;

	for(auto key : recipeToTranslate.ingredients.keys()){
	  ingredientNameArr.append(key);
	  BaseTypes::Recipe::IngredientAmount amount = recipeToTranslate.ingredients.value(key);
	  ingredientCountArr.append(amount.quantity);
	  ingredientUnitArr.append(amount.quantity);
	}

	recipe["ingredients"] = QJsonObject{
		{"ingredientNameArray", ingredientNameArr},
		{"ingredientQuantityArray", ingredientCountArr},
		{"ingredientUnitArray", ingredientUnitArr}
	};

	return recipe;
}

server::recipe::Recipe translateRecipeToServer(const BaseTypes::Recipe &recipe){
	std::string course;
	if(recipe.courses.size() > 0) {
	  course = recipe.courses.values()[0].toLower().toStdString();
	}

	std::string cusine;
	if(recipe.cusines.size() > 0) {
	  cusine = recipe.cusines.values()[0].toLower().toStdString();
	}

	server::recipe::IngredientsList ingredients;
	for(auto key : recipe.ingredients.keys()) {
		server::recipe::IngredientAmount amount;
		const BaseTypes::Recipe::IngredientAmount &my_amount = recipe.ingredients.value(key);
		amount.quantity = my_amount.quantity;
		amount.unit = my_amount.unit.toLower().toStdString();

		ingredients.insert(std::pair<std::string, server::recipe::IngredientAmount>(key.toLower().toStdString(), amount));
	}

	return server::recipe::Recipe(recipe.getID() ? *recipe.getID() : 0,
					recipe.name.toStdString(),
					course,
					cusine,
					ingredients,
					recipe.outCalories,
					recipe.outWeight,
					recipe.outPortions,
					recipe.recipeText.toStdString(),
					recipe.presentationText.toStdString(),
					recipe.remarks.toStdString());
}

// SearchQueryRequest class
QJsonObject SearchQuery::toJSON() {
	QJsonObject request{{"requestTag", requestTag}}; // Initializing with requestTag
	// Creating another Object for criteria
		QJsonObject criteria;

		QJsonArray favoriteIDs;
		for(auto id : favoriteIDs) {
		  favoriteIDs.append(id);
		}
		criteria["favoriteIDs"] = favoriteIDs;

		criteria["nameSubstring"] = searchSubtring;
		criteria["course"] = courses.values()[0];
		criteria["cuisine"] = cusines.values()[0];

		QJsonArray ingredientsSubset;
		for(auto ingredient : ingredients) {
		  ingredientsSubset.append(ingredient);
		}
		criteria["ingredientsSubset"] = ingredientsSubset;

		criteria["exclusiveIngredients"] = searchExclusively;

	request["searchCriteria"] = criteria;

	return request;
}

server::requests::RequestVar SearchQuery::translate() {
	std::set<unsigned int> favoriteIDs;
	for(auto id : this->favoriteIDs){
	  favoriteIDs.insert(id);
	}

	std::string course;
	if(courses.size() > 0) {
	  course = courses.values()[0].toLower().toStdString();
	}
	std::string cusine;
	if(cusines.size() > 0) {
	  cusine = cusines.values()[0].toLower().toStdString();
	}
	std::set<std::string> ingredients;
	for(auto ingredient : this->ingredients){
		ingredients.insert(ingredient.toLower().toStdString());
	}

	return server::requests::Find(server::searcher::Criteria(
					favoriteIDs,
					searchSubtring.toLower().toStdString(),
					course,
					cusine,
					ingredients,
					searchExclusively
				), 1);
}

// AddRecipeRequest class
QJsonObject AddRecipeRequest::toJSON() {
  QJsonObject request{{"requestTag", requestTag}};
  request["newRecipe"] = translateRecipToJson(*recipeToAdd);
  return request;
}

server::requests::RequestVar AddRecipeRequest::translate() {
	return server::requests::Add(translateRecipeToServer(*this->recipeToAdd), 1);
}

// EditRecipeRequest class
QJsonObject EditRecipeRequest::toJSON() {
  QJsonObject request{{"requestTag", requestTag}};
  request["newRecipe"] = translateRecipToJson(*editedRecipe);
  return request;
}

server::requests::RequestVar EditRecipeRequest::translate() {
  return server::requests::Edit(translateRecipeToServer(*this->editedRecipe), 1);
}

// RemoveRecipeRequest class
QJsonObject RemoveRecipeRequest::toJSON() {
  return {
	{"requestTag", requestTag},
	{"recipeID", (qint64)recipeIDToRemove}
  };
}

server::requests::RequestVar RemoveRecipeRequest::translate() {
  return server::requests::Remove(recipeIDToRemove, 1);
}

// GetInitDataRequest
QJsonObject GetInitDataRequest::toJSON() {
  return {{"requestTag", requestTag}};
}
server::requests::RequestVar GetInitDataRequest::translate() {
  return server::requests::GetInitData(1);
}

//Error class
QJsonObject Error::toJSON() {
  return {{"requestTag", requestTag}};
}

server::requests::RequestVar Error::translate() {
  return server::requests::Error(1);
}
