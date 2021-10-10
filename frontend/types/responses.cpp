#include <QVector>
#include <QJsonArray>

#include "responses.h"

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
		recipe->ingredients.insert({{
			ingredients[index].toString(),
			BaseTypes::Recipe::IngredientAmount{
							ingredientCounts[index].toDouble(),
							ingredientUnits[index].toString()}
		}});
	  }

	}

	return recipe;
}

// Response class
Response::~Response(){ }

// ErrorResponse class
void ErrorResponse::translate(const server::responses::ResponseVar&& response) {
	auto err = Response::extractType<server::responses::Error>(response);
	setClientID(err.getClientID());
	this->message = QString::fromStdString(err.getMessage());
}
void ErrorResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
}

// TagsResponse class
TagsResponse::TagsResponse(unsigned int clientID):
  Response(clientID), courses{new QSet<QString>()}, cusines{new QSet<QString>()},
  ingredients{new QSet<QString>()}, units{new QSet<QString>()}{
}
QSharedPointer<QSet<QString>> TagsResponse::getCourses() { return courses; }
QSharedPointer<QSet<QString>> TagsResponse::getCusines() { return cusines; }
QSharedPointer<QSet<QString>> TagsResponse::getIngredients() { return ingredients; }
QSharedPointer<QSet<QString>> TagsResponse::getUnits() { return units; }

void TagsResponse::translate(const server::responses::ResponseVar&& response) {
	auto tags = Response::extractType<server::responses::GetInitDataResult>(response);
	setClientID(tags.getClientID());
	for(auto course : tags.getInitData().getFullCourseSet()){
	  courses->insert(QString::fromStdString(course));
	}
	for(auto cusine : tags.getInitData().getFullCuisineSet()){
	  cusines->insert(QString::fromStdString(cusine));
	}
	for(auto ingredient : tags.getInitData().getFullIngredientSet()){
	  ingredients->insert(QString::fromStdString(ingredient));
	}
	for(auto unit : tags.getInitData().getFullUnitSet()){
	  units->insert(QString::fromStdString(unit));
	}
}
void TagsResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
  QJsonArray currentArray = json["initData"]["fullCourseSet"].toArray();
  for(auto course : currentArray){
	courses->insert(course.toString());
  }

  currentArray = json["initData"]["fullCuisineSet"].toArray();
  for(auto cusine : currentArray){
	cusines->insert(cusine.toString());
  }

  currentArray = json["initData"]["fullUnitSet"].toArray();
  for(auto unit : currentArray){
	units->insert(unit.toString());
  }

  currentArray = json["initData"]["fullIngredientSet"].toArray();
  for(auto ingredient : currentArray){
	ingredients->insert(ingredient.toString());
  }

}

// SearchResponse class
SearchResponse::SearchResponse(unsigned int clientID) : Response(clientID),
  foundRecipes(new QVector<QSharedPointer<BaseTypes::Recipe>>()) {}

QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> SearchResponse::getRecipes() { return foundRecipes; }

void SearchResponse::translate(const server::responses::ResponseVar&& responseToTranslate){
	auto searchResult = Response::extractType<server::responses::FindResult>(responseToTranslate);
	setClientID(searchResult.getClientID());

	QSharedPointer<Recipe> currentRecipe;
	for(auto recipe : searchResult.getResults().getFoundRecipes()){
	  currentRecipe.reset(new Recipe(0)); // Setting id to 0, because it will be reset in next line
	  currentRecipe->translateFromServer(recipe);
	  foundRecipes->append(currentRecipe);
	}
	// Shrinking recipes because we wont add more
	foundRecipes->shrink_to_fit();
}
void SearchResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
  QJsonArray recipesArray = json["searchResults"]["foundRecipeArray"].toArray();

  for(auto recipe : recipesArray){
	foundRecipes->append(
		  QSharedPointer<BaseTypes::Recipe>(translateToRecipeFromJson(recipe.toObject())));
  }
}

// AddResponse class
AddResponse::AddResponse(unsigned int clientID, unsigned newRecipeID) : Response(clientID), settedID(newRecipeID){}
void AddResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::AddSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void AddResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
}

// EditResponse class
EditResponse::EditResponse(unsigned int clientID) : Response(clientID) {}

void EditResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::EditSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void EditResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
}

// RemoveResponse class
RemoveResponse::RemoveResponse(unsigned int clientID) : Response(clientID) {}

void RemoveResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::RemoveSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void RemoveResponse::translateFromJSON(const QJsonObject& json) {
  if(json["responseTag"] != responseTag) {
	throw std::runtime_error("Tried to parse into wrong type");
  }
}
