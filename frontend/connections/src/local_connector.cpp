#include <QStandardPaths>
#include <utility>

#include "connectors.h"
#include "recipe.h"

using namespace Connections;

LocalConnector::LocalConnector() :
  currentLocal(server::LocalServerKeeper((QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0] + "/cookbook.db").toStdString())),
  exchanger(currentLocal.getLocalExchange()){

	// NOTE reqquest clientID should be 1!!
}

void LocalConnector::openConnection() {}
void LocalConnector::closeConnection() {}

BaseTypes::Responses::SearchResponse LocalConnector::runSearch(BaseTypes::Requests::SearchQuery&& query){
	exchanger.sendRequest(query.translate());
	auto response = BaseTypes::Responses::SearchResponse(); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::TagsResponse LocalConnector::getTags(BaseTypes::Requests::GetInitDataRequest&& tagRequest){
	exchanger.sendRequest(tagRequest.translate());
	auto response = BaseTypes::Responses::TagsResponse(); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::RemoveResponse LocalConnector::removeRecipe(BaseTypes::Requests::RemoveRecipeRequest&& removeRequest){
	exchanger.sendRequest(removeRequest.translate());
	auto response = BaseTypes::Responses::RemoveResponse(); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::AddResponse LocalConnector::postRecipe(BaseTypes::Requests::AddRecipeRequest&& addRequest){
  exchanger.sendRequest(addRequest.translate());
  auto resp = BaseTypes::Responses::AddResponse();
  resp.translate(exchanger.getResponse());
  return resp;
}
BaseTypes::Responses::EditResponse LocalConnector::editRecipe(BaseTypes::Requests::EditRecipeRequest&& editRequest){
	exchanger.sendRequest(editRequest.translate());
	auto response = BaseTypes::Responses::EditResponse(); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

BaseTypes::Responses::ErrorResponse LocalConnector::sendError(BaseTypes::Requests::Error&& error){
	exchanger.sendRequest(error.translate());
	auto response = BaseTypes::Responses::ErrorResponse(); // Setting to 0, because next line will change its value
	response.translate(exchanger.getResponse());
	return response;
}

LocalConnector::~LocalConnector(){

}



