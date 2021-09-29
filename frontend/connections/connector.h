#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "types/base_types.h"
#include <QList>
#include <QSharedPointer>

namespace Connections {
	class IConnector {
	  public:
		virtual void openConnection() = 0;
		virtual void closeConnection() = 0;
		virtual QList<BaseTypes::Response*> runQuery(BaseTypes::RequestQuery query) = 0;
		virtual void postRecipe(BaseTypes::Recipe *recipeToPost) = 0;
		virtual ~IConnector(){}
	};
}

#endif // CONNECTOR_H
