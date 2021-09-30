#ifndef FRONT_REQUESTS_H
#define FRONT_REQUESTS_H

#include <QString>
#include <QList>
#include <QSet>
#include <QSharedPointer>
#include "../server/requests/include/requests.h"
#include "responses.h"


// TODO remake Request type to have 2 virtual methods: toString() - for JSON, translate() - for local protocols
namespace BaseTypes::Requests {

class Request {
public:
	virtual QString toJSONString() = 0;
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
public:
	SearchQuery(QSet<unsigned int> _favoriteIDs, QString _name, QSet<QString> _courses,
				 QSet<QString> _cuisines, QList<QString> _ingredients, bool _searchExclusively) :
	  favoriteIDs(_favoriteIDs), searchSubtring(_name),
	  courses(_courses), cusines(_cuisines),
	  ingredients(_ingredients), searchExclusively(_searchExclusively) {
	}

	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~SearchQuery() override {}

};
class AddRecipeRequest : public Request {
private:
	QSharedPointer<Recipe> recipeToAdd;
public:
	AddRecipeRequest(QSharedPointer<Recipe> _recipeToAdd) : recipeToAdd(_recipeToAdd) {}

	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~AddRecipeRequest() override {}
};

class EditRecipeRequest : public Request {
	QSharedPointer<Recipe> editedRecipe;
  public:
	EditRecipeRequest(QSharedPointer<Recipe> _editedRecipe) : editedRecipe(_editedRecipe) {}

	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~EditRecipeRequest() override {}
};

class RemoveRecipeRequest : public Request {
	unsigned int recipeIDToRemove;
public:
	RemoveRecipeRequest(unsigned int _recipeIDToRemove) : recipeIDToRemove(_recipeIDToRemove) {}

	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~RemoveRecipeRequest() override {}
};

class GetInitDataRequest : public Request {
public:
	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~GetInitDataRequest() override {}
};

class Error : public Request {
public:
	QString errorMessage;
	Error(QString msg="") : errorMessage(msg){ }

	QString toJSONString() override;
	server::requests::RequestVar translate() override;

	~Error() override {}
};

}


#endif // REQUESTS_H
