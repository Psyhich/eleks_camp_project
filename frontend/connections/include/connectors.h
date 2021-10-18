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

	BaseTypes::Responses::SearchResponse runSearch(BaseTypes::Requests::SearchQuery&& filter) override;

	BaseTypes::Responses::TagsResponse getTags(BaseTypes::Requests::GetInitDataRequest&& tagRequest) override;

	BaseTypes::Responses::RemoveResponse removeRecipe(BaseTypes::Requests::RemoveRecipeRequest&& removeRequest) override;
	BaseTypes::Responses::AddResponse postRecipe(BaseTypes::Requests::AddRecipeRequest&& arrRequest) override;
	BaseTypes::Responses::EditResponse editRecipe(BaseTypes::Requests::EditRecipeRequest&& editRequest) override;

	BaseTypes::Responses::ErrorResponse sendError(BaseTypes::Requests::Error&& error) override;

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

	BaseTypes::Responses::SearchResponse runSearch(BaseTypes::Requests::SearchQuery&& filter) override;

	BaseTypes::Responses::TagsResponse getTags(BaseTypes::Requests::GetInitDataRequest&& tagRequest) override;

	BaseTypes::Responses::RemoveResponse removeRecipe(BaseTypes::Requests::RemoveRecipeRequest&& removeRequest) override;
	BaseTypes::Responses::AddResponse postRecipe(BaseTypes::Requests::AddRecipeRequest&& arrRequest) override;
	BaseTypes::Responses::EditResponse editRecipe(BaseTypes::Requests::EditRecipeRequest&& editRequest) override;

	BaseTypes::Responses::ErrorResponse sendError(BaseTypes::Requests::Error&& error) override;

	~RemoteConnector() override;
};

}
#endif // CONNECTORS_H
