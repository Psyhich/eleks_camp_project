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
	remoteConnection = QSharedPointer<IConnector>(new RemoteConnector("0.0.0",0));
}

void ConnectionManager::toggleToLocal() {
	if(!localConnection.isNull()){
		currentConnection = localConnection;
	}
}

void ConnectionManager::toggleToRemote(QString address, quint16 port) {
	if(!remoteConnection.isNull()){
		remoteConnection = QSharedPointer<IConnector>(new RemoteConnector(address, port));
		currentConnection = remoteConnection;
	}
}

bool ConnectionManager::sendRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSend){
  if(auto connection = currentConnection.lock()){
	QSharedPointer<BaseTypes::Requests::AddRecipeRequest>
		request(new BaseTypes::Requests::AddRecipeRequest(recipeToSend));
	return  connection->postRecipe(request).isSuccessfull();
  }
  return false;
}

QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> ConnectionManager::runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> query){
	if(auto connection = currentConnection.lock()){
		return connection->runSearch(query).getRecipes();
	}
	return {};
}


BaseTypes::Responses::TagsResponse ConnectionManager::getTags(){
  if(auto connection = currentConnection.lock()){
	QSharedPointer<BaseTypes::Requests::GetInitDataRequest>
		request(new BaseTypes::Requests::GetInitDataRequest());
	return connection->getTags(request);
  }
  return false;
}
bool ConnectionManager::removeRecipe(unsigned int recipeID){
  if(auto connection = currentConnection.lock()){
	QSharedPointer<BaseTypes::Requests::RemoveRecipeRequest>
		request(new BaseTypes::Requests::RemoveRecipeRequest(recipeID));
	return connection->removeRecipe(request).isSuccessfull();
  }
  return false;
}
bool ConnectionManager::editRecipe(QSharedPointer<BaseTypes::Recipe> editedRecipe){
  if(auto connection = currentConnection.lock()){
	QSharedPointer<BaseTypes::Requests::EditRecipeRequest>
		request(new BaseTypes::Requests::EditRecipeRequest(editedRecipe));
	return connection->editRecipe(request).isSuccessfull();
  }
  return false;
}


