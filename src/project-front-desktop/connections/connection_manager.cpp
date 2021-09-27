#include "connection_manager.h"
#include "connectors.h"

using namespace Connections;

ConnectionManager& ConnectionManager::getManager(){
	static ConnectionManager manager;
	return manager;
}

ConnectionManager::ConnectionManager() {
	// Enabling local connection by default
	currentConnection = localConnection = new LocalConnector();
}

void ConnectionManager::toggleToLocal() {
	if(localConnection != nullptr){
		if(currentConnection != nullptr){ currentConnection->closeConnection(); }
		currentConnection = localConnection;
		currentConnection->openConnection();
	}
}

void ConnectionManager::toggleToRemote() {
	if(remoteConnection != nullptr){
		if(currentConnection != nullptr){ currentConnection->closeConnection(); }
		currentConnection = remoteConnection;
		currentConnection->openConnection();
	}
}

void ConnectionManager::sendRecipe(BaseTypes::Recipe *recipeToSend){
  if(currentConnection != nullptr){
	currentConnection->postRecipe(recipeToSend);
  }
}

QList<BaseTypes::Response*> ConnectionManager::runQuery(BaseTypes::RequestQuery query){
	if(currentConnection != nullptr){
	  return currentConnection->runQuery(query);
	}
	return {};
}

ConnectionManager::~ConnectionManager() {
	if(localConnection != nullptr){
		localConnection->closeConnection();
		delete localConnection;
	}
	if(remoteConnection != nullptr){
		remoteConnection->closeConnection();
		delete remoteConnection;
	}
}
