#include <QJsonDocument>
#include <QTcpSocket>
#include <utility>

#include "connectors.h"


using namespace Connections;
using namespace BaseTypes::Requests;
using namespace BaseTypes::Responses;

// Remote protocol is easy:
// Connect
// Request
// Get Response
// Disconnect

QJsonObject RemoteConnector::postJson(const QJsonObject& json){
  QByteArray parsedJSON = QJsonDocument(json).toJson(QJsonDocument::Compact);
  parsedJSON.push_back('\0');

  QTcpSocket socket;
  socket.setReadBufferSize(0);
  socket.connectToHost(address, port);

  if(!socket.waitForConnected(-1)){}
  socket.write(parsedJSON);

  if(!socket.waitForBytesWritten(-1)){}

  QByteArray byteResponse;
  // Waiting till all packets arived
  do{
	if(!socket.waitForReadyRead(-1)){}
	byteResponse.append(socket.readAll());
  } while(byteResponse[byteResponse.count() - 1] != '\0');
  // Removing last \0 character
  byteResponse.remove(byteResponse.count() - 1, 1);

  return QJsonDocument::fromJson(byteResponse).object();
}

RemoteConnector::RemoteConnector(QString remoteAdress, quint16 _port) :
  address{remoteAdress}, port{_port} {
}

void RemoteConnector::openConnection(){}
void RemoteConnector::closeConnection(){}

SearchResponse RemoteConnector::runSearch(SearchQuery&& filter){
	SearchResponse response;

	response.translateFromJSON(postJson(filter.toJSON()));

	return response;
}

TagsResponse RemoteConnector::getTags(GetInitDataRequest&& request){
  TagsResponse response;

  response.translateFromJSON(postJson(request.toJSON()));

  return response;

}

RemoveResponse RemoteConnector::removeRecipe(RemoveRecipeRequest&& request){
  RemoveResponse response;

  response.translateFromJSON(postJson(request.toJSON()));

  return response;
}

AddResponse RemoteConnector::postRecipe(AddRecipeRequest&& request){
  AddResponse response;

  response.translateFromJSON(postJson(request.toJSON()));

  return response;
}

EditResponse RemoteConnector::editRecipe(EditRecipeRequest&& request){
  EditResponse response;

  response.translateFromJSON(postJson(request.toJSON()));

  return response;
}

ErrorResponse RemoteConnector::sendError(Error&& error){
  ErrorResponse response;

  response.translateFromJSON(postJson(error.toJSON()));

  return response;
}

RemoteConnector::~RemoteConnector(){}
