#include <QJsonDocument>
#include <QTcpSocket>

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
  socket.connectToHost(address, port);

  SearchResponse response(0);
  if(!socket.waitForConnected(-1)){}
  socket.write(parsedJSON);

  if(!socket.waitForBytesWritten(-1)){}
  if(!socket.waitForReadyRead(-1)){}

  QByteArray byteResponse = socket.readAll();
  // Removing last \0 character
  byteResponse.remove(byteResponse.count() - 1, 1);

  return QJsonDocument::fromJson(byteResponse).object();
}

RemoteConnector::RemoteConnector(QString remoteAdress, quint16 _port) :
  address{remoteAdress}, port{_port} {
}

void RemoteConnector::openConnection(){}
void RemoteConnector::closeConnection(){}

SearchResponse RemoteConnector::runSearch(QSharedPointer<SearchQuery> filter){
	SearchResponse response(0);

	response.translateFromJSON(postJson(filter->toJSON()));

	return response;
}

TagsResponse RemoteConnector::getTags(QSharedPointer<GetInitDataRequest> request){
  TagsResponse response(0);

  response.translateFromJSON(postJson(request->toJSON()));

  return response;

}

RemoveResponse RemoteConnector::removeRecipe(QSharedPointer<RemoveRecipeRequest> request){
  RemoveResponse response(0);

  response.translateFromJSON(postJson(request->toJSON()));

  return response;
}

AddResponse RemoteConnector::postRecipe(QSharedPointer<AddRecipeRequest> request){
  AddResponse response(0, 0);

  response.translateFromJSON(postJson(request->toJSON()));

  return response;
}

EditResponse RemoteConnector::editRecipe(QSharedPointer<EditRecipeRequest> request){
  EditResponse response(0);

  response.translateFromJSON(postJson(request->toJSON()));

  return response;
}

ErrorResponse RemoteConnector::sendError(QSharedPointer<Error> error){
  ErrorResponse response(0);

  response.translateFromJSON(postJson(error->toJSON()));

  return response;
}

RemoteConnector::~RemoteConnector(){}



