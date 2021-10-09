#include <QVector>
#include "responses.h"

using namespace BaseTypes::Responses;

// Response class
Response::~Response(){ }

// ErrorResponse class
void ErrorResponse::translate(const server::responses::ResponseVar&& response) {
	auto err = Response::extractType<server::responses::Error>(response);
	setClientID(err.getClientID());
	this->message = QString::fromStdString(err.getMessage());
}
void ErrorResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
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
void TagsResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
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
void SearchResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

// AddResponse class
AddResponse::AddResponse(unsigned int clientID, unsigned newRecipeID) : Response(clientID), settedID(newRecipeID){}
void AddResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::AddSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void AddResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

// EditResponse class
EditResponse::EditResponse(unsigned int clientID) : Response(clientID) {}

void EditResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::EditSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void EditResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

// RemoveResponse class
RemoveResponse::RemoveResponse(unsigned int clientID) : Response(clientID) {}

void RemoveResponse::translate(const server::responses::ResponseVar&& responseToTranslate) {
	auto addResp = Response::extractType<server::responses::RemoveSuccess>(responseToTranslate);
	setClientID(addResp.getClientID());
}
void RemoveResponse::translateFromJSON(const QString& str) {
	throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}
