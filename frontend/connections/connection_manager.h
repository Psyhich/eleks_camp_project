#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

#include "i_connector.h"

namespace Connections {

	// There can be only one connection manager
	// Class that gives abstraction beetwean UI and different interaction protocols
	class ConnectionManager {
	  private:
		QSharedPointer<IConnector> localConnection;
		QSharedPointer<IConnector> remoteConnection;

		QWeakPointer<IConnector> currentConnection;

		ConnectionManager();

	  public:
		ConnectionManager(const ConnectionManager& copy) = delete;
		void operator=(const ConnectionManager& assign) = delete;

		static ConnectionManager& getManager();

		void toggleToLocal();
		void toggleToRemote(QString address, quint16 port);

		BaseTypes::Responses::TagsResponse getTags();

		unsigned int sendRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSend);
		QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> runSearch(QSharedPointer<BaseTypes::Requests::SearchQuery> query);
		bool removeRecipe(unsigned int recipeID);
		bool editRecipe(QSharedPointer<BaseTypes::Recipe> editedRecipe);

	};
}

#endif // CONNECTION_MANAGER_H
