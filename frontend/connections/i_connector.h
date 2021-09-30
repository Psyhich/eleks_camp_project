#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QList>
#include <QSharedPointer>

#include "recipe.h"
#include "types/responses.h"
#include "types/requests.h"

namespace Connections {
	class IConnector {
	  public:
		virtual void openConnection() = 0;
		virtual void closeConnection() = 0;

		virtual BaseTypes::Responses::SearchResponse runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> query) = 0;

		virtual BaseTypes::Responses::TagsResponse getTags(QSharedPointer<BaseTypes::Requests::GetInitDataRequest> tagRequest) = 0;

		virtual BaseTypes::Responses::RemoveResponse removeRecipe(QSharedPointer<BaseTypes::Requests::RemoveRecipeRequest> removeRequest) = 0;
		virtual BaseTypes::Responses::AddResponse postRecipe(QSharedPointer<BaseTypes::Requests::AddRecipeRequest> addRequest) = 0;
		virtual BaseTypes::Responses::EditResponse editRecipe(QSharedPointer<BaseTypes::Requests::EditRecipeRequest> editRequest) = 0;

		virtual BaseTypes::Responses::ErrorResponse sendError(QSharedPointer<BaseTypes::Requests::Error> error) = 0;

		virtual ~IConnector(){}
	};


}

#endif // CONNECTOR_H
