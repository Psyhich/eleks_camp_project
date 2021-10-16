#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QList>
#include <QSharedPointer>

#include "front_recipe.h"
#include "front_responses.h"
#include "front_requests.h"

namespace Connections {
	class IConnector {
	  public:
		virtual void openConnection() = 0;
		virtual void closeConnection() = 0;

		virtual BaseTypes::Responses::SearchResponse runSearch(BaseTypes::Requests::SearchQuery&& query) = 0;

		virtual BaseTypes::Responses::TagsResponse getTags(BaseTypes::Requests::GetInitDataRequest&& tagRequest) = 0;

		virtual BaseTypes::Responses::RemoveResponse removeRecipe(BaseTypes::Requests::RemoveRecipeRequest&& removeRequest) = 0;
		virtual BaseTypes::Responses::AddResponse postRecipe(BaseTypes::Requests::AddRecipeRequest&& addRequest) = 0;
		virtual BaseTypes::Responses::EditResponse editRecipe(BaseTypes::Requests::EditRecipeRequest&& editRequest) = 0;

		virtual BaseTypes::Responses::ErrorResponse sendError(BaseTypes::Requests::Error&& error) = 0;

		virtual ~IConnector(){}
	};


}

#endif // CONNECTOR_H
