#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "i_connector.h"
#include "local_server_keeper.h"
#include "i_frontend_exchange.h"

namespace Connections {
class LocalConnector : public Connections::IConnector {
private:
	server::LocalServerKeeper currentLocal;
	server::localex::IFrontendExchange& exchanger;
public:
	LocalConnector();

	void openConnection() override;
	void closeConnection() override;

	BaseTypes::Responses::SearchResponse runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> filter) override;

	BaseTypes::Responses::TagsResponse getTags(QSharedPointer<BaseTypes::Requests::GetInitDataRequest> tagRequest) override;

	virtual BaseTypes::Responses::RemoveResponse removeRecipe(QSharedPointer<BaseTypes::Requests::RemoveRecipeRequest> removeRequest) override;
	virtual BaseTypes::Responses::AddResponse postRecipe(QSharedPointer<BaseTypes::Requests::AddRecipeRequest> arrRequest) override;
	virtual BaseTypes::Responses::EditResponse editRecipe(QSharedPointer<BaseTypes::Requests::EditRecipeRequest> editRequest) override;

	virtual BaseTypes::Responses::ErrorResponse sendError(QSharedPointer<BaseTypes::Requests::Error> error) override;

	~LocalConnector() override;
};

class RemoteConnector : public Connections::IConnector {
private:
	QString address;
	quint16 port;
	QJsonObject postJson(const QJsonObject& json);
public:
	RemoteConnector(QString remoteAddres, quint16 port);

	void openConnection() override;
	void closeConnection() override;

	BaseTypes::Responses::SearchResponse runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> filter) override;

	BaseTypes::Responses::TagsResponse getTags(QSharedPointer<BaseTypes::Requests::GetInitDataRequest> tagRequest) override;

	virtual BaseTypes::Responses::RemoveResponse removeRecipe(QSharedPointer<BaseTypes::Requests::RemoveRecipeRequest> removeRequest) override;
	virtual BaseTypes::Responses::AddResponse postRecipe(QSharedPointer<BaseTypes::Requests::AddRecipeRequest> arrRequest) override;
	virtual BaseTypes::Responses::EditResponse editRecipe(QSharedPointer<BaseTypes::Requests::EditRecipeRequest> editRequest) override;

	virtual BaseTypes::Responses::ErrorResponse sendError(QSharedPointer<BaseTypes::Requests::Error> error) override;

	~RemoteConnector() override;
};

}
#endif // CONNECTORS_H
