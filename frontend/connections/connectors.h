#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "connector.h"
namespace Connections {
	class LocalConnector : public Connections::IConnector {
	  public:
		LocalConnector();

		// IConnector interface
	  public:
		void openConnection() override;
		void closeConnection() override;

		QList<BaseTypes::Response*> runQuery(BaseTypes::RequestQuery query) override;
		void postRecipe(BaseTypes::Recipe* recipeToPost) override;
		~LocalConnector() override;
	};
}
#endif // CONNECTORS_H
