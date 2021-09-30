#include "connectors.h"
#include <QDebug>
#include "../server/recipe/include/recipe.h"

using namespace Connections;

LocalConnector::LocalConnector() : currentLocal(server::LocalServerKeeper()), exchanger(currentLocal.getLocalExchange()){
	// NOTE reqquest clientID should be 1!!
}

void LocalConnector::openConnection() {

}

void LocalConnector::closeConnection() {

}

BaseTypes::Responses::SearchResponse LocalConnector::runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> query){
	exchanger.sendRequest(query->translate());
	auto response = BaseTypes::Responses::SearchResponse(0); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::TagsResponse LocalConnector::getTags(QSharedPointer<BaseTypes::Requests::GetInitDataRequest> tagRequest){
	exchanger.sendRequest(tagRequest->translate());
	auto response = BaseTypes::Responses::TagsResponse(0); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::RemoveResponse LocalConnector::removeRecipe(QSharedPointer<BaseTypes::Requests::RemoveRecipeRequest> removeRequest){
	exchanger.sendRequest(removeRequest->translate());
	auto response = BaseTypes::Responses::RemoveResponse(0); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::AddResponse LocalConnector::postRecipe(QSharedPointer<BaseTypes::Requests::AddRecipeRequest> addRequest){
  exchanger.sendRequest(addRequest->translate());
  auto resp = BaseTypes::Responses::AddResponse(0, 0);
  resp.translate(exchanger.getResponse());
  return resp;
}
BaseTypes::Responses::EditResponse LocalConnector::editRecipe(QSharedPointer<BaseTypes::Requests::EditRecipeRequest> editRequest){
	exchanger.sendRequest(editRequest->translate());
	auto response = BaseTypes::Responses::EditResponse(0); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::ErrorResponse LocalConnector::sendError(QSharedPointer<BaseTypes::Requests::Error> error){
	exchanger.sendRequest(error->translate());
	auto response = BaseTypes::Responses::ErrorResponse(0); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

LocalConnector::~LocalConnector(){

}



