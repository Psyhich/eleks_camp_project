#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "connector.h"
#include "types/base_types.h"

namespace Connections {

	// There can be only one connection manager
	// Class that gives abstraction beetwean UI and different interaction protocols
	class ConnectionManager {

	  private:
		IConnector* localConnection = nullptr;
		IConnector* remoteConnection = nullptr;

		IConnector* currentConnection = nullptr;

		ConnectionManager();

	  public:
		ConnectionManager(const ConnectionManager& copy) = delete;
		void operator=(const ConnectionManager& assign) = delete;

		static ConnectionManager& getManager();

		~ConnectionManager();


		void toggleToLocal();
		void toggleToRemote();

		void openRemoteConnection(QString address);

		void sendRecipe(BaseTypes::Recipe* recipeToSend);
		QList<BaseTypes::Response*> runQuery(BaseTypes::RequestQuery query);

	};
}

#endif // CONNECTION_MANAGER_H
