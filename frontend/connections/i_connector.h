#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "recipe.h"
#include "types/responses.h"
#include "types/requests.h"
#include <QList>
#include <QSharedPointer>

namespace Connections {
	class IConnector {
	  public:
		virtual void openConnection() = 0;
		virtual void closeConnection() = 0;

		virtual QList<QSharedPointer<BaseTypes::Recipe>> runSearch(BaseTypes::SearchQuery query) = 0;

		virtual QSharedPointer<BaseTypes::TagsResponse> getTags() = 0;

		virtual bool removeRecipe(unsigned int recipeID) = 0;
		virtual QSharedPointer<BaseTypes::Recipe> postRecipe(QSharedPointer<BaseTypes::Recipe> recipeToPost) = 0;
		virtual QSharedPointer<BaseTypes::Recipe> editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit) = 0;

		virtual void sendError(BaseTypes::Error error) = 0;

		virtual ~IConnector(){}
	};


}

#endif // CONNECTOR_H
