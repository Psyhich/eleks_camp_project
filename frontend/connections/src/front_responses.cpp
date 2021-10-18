#include <QVector>
#include <QJsonArray>

#include "front_responses.h"
#include "recipe.h"

using namespace BaseTypes::Responses;

BaseTypes::Recipe* translateToRecipeFromJson(const QJsonObject &json){
	BaseTypes::Recipe *recipe = new BaseTypes::Recipe(json["id"].toInt());
	recipe->name = json["name"].toString();

	recipe->courses = {json["course"].toString()};
	recipe->cusines = {json["cuisine"].toString()};

	recipe->outCalories = json["outCalories"].toDouble();
	recipe->outWeight = json["outWeight"].toDouble();
	recipe->outPortions = json["outPortions"].toInt();

	recipe->recipeText = json["preparation"].toString();
	recipe->presentationText = json["presentation"].toString();
	recipe->remarks = json["remarks"].toString();

	// Ingredients
	QJsonArray ingredients = json["ingredients"]["ingredientNameArray"].toArray();
	QJsonArray ingredientCounts = json["ingredients"]["ingredientQuantityArray"].toArray();
	QJsonArray ingredientUnits = json["ingredients"]["ingredientUnitArray"].toArray();
	if(ingredients.count() == ingredientCounts.count() &&
	   ingredients.count() == ingredientUnits.count()){
	  for(int index = 0; index < ingredients.count(); index++){
		recipe->ingredients.insert(
			ingredients[index].toString(),
			BaseTypes::Recipe::IngredientAmount{
							ingredientCounts[index].toDouble(),
							ingredientUnits[index].toString()}
		);
	  }

	}

	return recipe;
}
BaseTypes::Recipe* translateRecipeFromServer(const server::recipe::Recipe &response){
	BaseTypes::Recipe *recipe = new BaseTypes::Recipe(response.getId());
	recipe->name = QString::fromStdString(response.getName());

	recipe->courses = {QString::fromStdString(response.getCourse())};
	recipe->cusines = {QString::fromStdString(response.getCuisine())};

	// Translating ingredients
	for(auto pair : response.getIngredients()){
	  BaseTypes::Recipe::IngredientAmount amount;
	  amount.quantity = pair.second.quantity;
	  amount.unit = QString::fromStdString(pair.second.unit);
	  recipe->ingredients.insert(QString::fromStdString(pair.first), amount);
	}

	recipe->outWeight = response.getOutWeight();
	recipe->outCalories = response.getOutCalories();
	recipe->outPortions = response.getOutPortions();

	recipe->recipeText = QString::fromStdString(response.getPreparation());
	recipe->presentationText = QString::fromStdString(response.getPresentation());
	recipe->remarks = QString::fromStdString(response.getRemarks());

	return recipe;
}

// Response class
Response::~Response(){ }

// ErrorResponse class
void ErrorResponse::translate(const server::responses::ResponseVar&& response) {
	if(auto err = Response::extractType<server::responses::Error>(response)){
		setSuccesfull(true);
		message = QString::fromStdString(err->getMessage());
	}
}
void ErrorResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	return;
  }
  setSuccesfull(true);
}

// TagsResponse class
TagsResponse::TagsResponse() { }
BaseTypes::TagsHolder&& TagsResponse::getTags() { return std::move(tags); }

void TagsResponse::translate(const server::responses::ResponseVar&& response) {
	if(auto tags = Response::extractType<server::responses::GetInitDataResult>(response)){
		setSuccesfull(true);
		for(auto course : tags->getInitData().getFullCourseSet()){
		  this->tags.courses.insert(QString::fromStdString(course));
		}
		for(auto cusine : tags->getInitData().getFullCuisineSet()){
		  this->tags.cusines.insert(QString::fromStdString(cusine));
		}
		for(auto ingredient : tags->getInitData().getFullIngredientSet()){
		  this->tags.ingredients.insert(QString::fromStdString(ingredient));
		}
		for(auto unit : tags->getInitData().getFullUnitSet()){
		  this->tags.units.insert(QString::fromStdString(unit));
		}
	}
}
void TagsResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	return;
  }
  QJsonArray currentArray = json["initData"]["fullCourseSet"].toArray();
  for(auto course : currentArray){
	tags.courses.insert(course.toString());
  }

  currentArray = json["initData"]["fullCuisineSet"].toArray();
  for(auto cusine : currentArray){
	tags.cusines.insert(cusine.toString());
  }

  currentArray = json["initData"]["fullUnitSet"].toArray();
  for(auto unit : currentArray){
	tags.units.insert(unit.toString());
  }

  currentArray = json["initData"]["fullIngredientSet"].toArray();
  for(auto ingredient : currentArray){
	tags.ingredients.insert(ingredient.toString());
  }
  setSuccesfull(true);

}

// SearchResponse class
SearchResponse::SearchResponse() {}

QVector<QSharedPointer<BaseTypes::Recipe>>&& SearchResponse::getRecipes() { return std::move(foundRecipes); }

void SearchResponse::translate(const server::responses::ResponseVar&& responseToTranslate){
	if(auto searchResult = Response::extractType<server::responses::FindResult>(responseToTranslate)){
		setSuccesfull(true);

		QSharedPointer<Recipe> currentRecipe;
		for(auto recipe : searchResult->getResults().getFoundRecipes()){
		  currentRecipe = QSharedPointer<BaseTypes::Recipe>(translateRecipeFromServer(recipe));
		  foundRecipes.append(currentRecipe);
		}
		// Shrinking recipes because we wont add more
		foundRecipes.shrink_to_fit();
	}
}
void SearchResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"].toInt() != responseTag) {
	return;
  }
  QJsonArray recipesArray = json["searchResults"]["foundRecipeArray"].toArray();

  for(auto recipe : recipesArray){
	foundRecipes.append(
		  QSharedPointer<BaseTypes::Recipe>(translateToRecipeFromJson(recipe.toObject())));
  }
  foundRecipes.shrink_to_fit();
  setSuccesfull(true);
}

// AddResponse class
AddResponse::AddResponse(unsigned newRecipeID) : settedID(newRecipeID) {}
void AddResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	if(auto addResp = Response::extractType<server::responses::AddSuccess>(responseToTranslate)) {
		setSuccesfull(true);
		settedID = addResp->getRecipeID();
	}
}
void AddResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"].toInt() != responseTag) {
	return;
  }
  setSuccesfull(true);
}

// EditResponse class
EditResponse::EditResponse() {}

void EditResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	if(auto addResp = Response::extractType<server::responses::EditSuccess>(responseToTranslate)){
		setSuccesfull(true);
	}
}
void EditResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"].toInt() != responseTag) {
	return;
  }
  setSuccesfull(true);
}

// RemoveResponse class
RemoveResponse::RemoveResponse() {}

void RemoveResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	if(auto addResp = Response::extractType<server::responses::RemoveSuccess>(responseToTranslate)) {
	  setSuccesfull(true);
	}
}
void RemoveResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"].toInt() != responseTag) {
	return;
  }
  setSuccesfull(true);
}
