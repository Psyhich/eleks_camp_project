#ifndef FRONT_REQUESTS_H
#define FRONT_REQUESTS_H

#include <QString>
#include <QList>
#include <QSet>
#include <QSharedPointer>
#include <QJsonObject>

#include "../server/requests/include/requests.h"
#include "responses.h"


namespace BaseTypes::Requests {

class Request {
public:
	virtual QJsonObject toJSON() = 0;
	virtual server::requests::RequestVar translate() = 0;

	virtual ~Request(){}
};

class SearchQuery : public Request {
	QSet<unsigned int> favoriteIDs;
	QString searchSubtring;
	QSet<QString> courses;
	QSet<QString> cusines;
	QList<QString> ingredients;
	bool searchExclusively;

	static const int requestTag = 2;
public:
	SearchQuery(QSet<unsigned int> _favoriteIDs, QString _name, QSet<QString> _courses,
				 QSet<QString> _cuisines, QList<QString> _ingredients, bool _searchExclusively) :
	  favoriteIDs(_favoriteIDs), searchSubtring(_name),
	  courses(_courses), cusines(_cuisines),
	  ingredients(_ingredients), searchExclusively(_searchExclusively) {
	}

	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~SearchQuery() override {}

};

class AddRecipeRequest : public Request {
private:
	QSharedPointer<BaseTypes::Recipe> recipeToAdd;

	static const int requestTag = 3;
public:
	AddRecipeRequest(QSharedPointer<Recipe> _recipeToAdd) : recipeToAdd(_recipeToAdd) {}

	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~AddRecipeRequest() override {}
};

class EditRecipeRequest : public Request {
	QSharedPointer<BaseTypes::Recipe> editedRecipe;

	static const int requestTag = 4;
  public:
	EditRecipeRequest(QSharedPointer<Recipe> _editedRecipe) : editedRecipe(_editedRecipe) {}

	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~EditRecipeRequest() override {}
};

class RemoveRecipeRequest : public Request {
	unsigned int recipeIDToRemove;

	const static int requestTag = 5;
public:
	RemoveRecipeRequest(unsigned int _recipeIDToRemove) : recipeIDToRemove(_recipeIDToRemove) {}

	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~RemoveRecipeRequest() override {}
};

class GetInitDataRequest : public Request {
	static const int requestTag = 1;
public:
	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~GetInitDataRequest() override {}
};

class Error : public Request {
	static const int requestTag = 0;
public:
	QString errorMessage;
	Error(QString msg="") : errorMessage(msg){ }

	QJsonObject toJSON() override;
	server::requests::RequestVar translate() override;

	~Error() override {}
};

}


#endif // REQUESTS_H
