#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base_types.h"
#include <QList>

namespace Connections {
	class IConnector {
	  public:
		virtual QList<BaseTypes::Response> runQuery(BaseTypes::RequestQuery query) = 0;
		virtual void postRecipe(BaseTypes::Recipe recipeToPost) = 0;
		virtual ~IConnector() = 0;
	};
}

#endif // CONNECTOR_H
