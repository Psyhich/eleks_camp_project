#include "connection_manager.h"
#include "connectors.h"

using namespace Connections;

ConnectionManager& ConnectionManager::getManager(){
	static ConnectionManager manager;
	return manager;
}

ConnectionManager::ConnectionManager() {
	// Enabling local connection by default
	currentConnection = localConnection = QSharedPointer<IConnector>(new LocalConnector());
}

void ConnectionManager::toggleToLocal() {
	// We shouldn't check if it's nullptr, because we initialize localConnector from the start
	currentConnection = localConnection;
}

void ConnectionManager::toggleToRemote(QString address, quint16 port) {
	remoteConnection = QSharedPointer<IConnector>(new RemoteConnector(address, port));
	currentConnection = remoteConnection;
}

// Search bound funcs
BaseTypes::Responses::TagsResponse ConnectionManager::getTags(){
  if(auto connection = currentConnection.lock()){
	BaseTypes::Requests::GetInitDataRequest	request;
	return connection->getTags(std::move(request));
  }
  return BaseTypes::Responses::TagsResponse();
}

BaseTypes::Responses::SearchResponse ConnectionManager::runSearch(BaseTypes::Query&& query){
	if(auto connection = currentConnection.lock()){
		BaseTypes::Requests::SearchQuery request(std::move(query));
		return connection->runSearch(std::move(request));
	}
	return BaseTypes::Responses::SearchResponse();
}

// Recipe bound funcs
BaseTypes::Responses::AddResponse ConnectionManager::sendRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSend){
  if(auto connection = currentConnection.lock()){
	BaseTypes::Requests::AddRecipeRequest request(recipeToSend);
	return std::move(connection->postRecipe(std::move(request)));
  }
  return BaseTypes::Responses::AddResponse();
}

BaseTypes::Responses::RemoveResponse ConnectionManager::removeRecipe(unsigned int recipeID){
  if(auto connection = currentConnection.lock()){
	BaseTypes::Requests::RemoveRecipeRequest request(recipeID);
	return connection->removeRecipe(std::move(request));
  }
  return BaseTypes::Responses::RemoveResponse();
}

BaseTypes::Responses::EditResponse ConnectionManager::editRecipe(QSharedPointer<BaseTypes::Recipe> editedRecipe){
  if(auto connection = currentConnection.lock()){
	BaseTypes::Requests::EditRecipeRequest request(editedRecipe);
	return connection->editRecipe(std::move(request));
  }
  return BaseTypes::Responses::EditResponse();
}


