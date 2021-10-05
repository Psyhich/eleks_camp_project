#ifndef RESPONSES_H
#define RESPONSES_H

#include <QMap>
#include <QString>
#include <QSet>
#include <QVector>
#include <QSharedPointer>
#include <QDebug>
#include "recipe.h"
#include "../server/recipe/include/recipe.h"
#include "../server/responses/include/responses.h"

namespace BaseTypes::Responses {


class Response {
private:
	unsigned int clientID{0};
protected:
	inline void setClientID(unsigned int newClientID){ clientID = newClientID; }
public:
	Response(unsigned int _clientID) : clientID(_clientID) {}

	bool isSuccessfull() { return clientID != 0; }
	virtual void translate(const server::responses::ResponseVar&& response) = 0;
	virtual void translateFromJSON(const QString& str) = 0;

	template<class T> static const T& extractType(server::responses::ResponseVar response){
		try {
			T& extracted = std::get<T>(response);
			return extracted;
		}  catch (const std::bad_variant_access& ex()) {
			qDebug() << "Tried to reach wrong variant(" << typeid(T).name() << ")\n";
			throw std::runtime_error("Tried to reach wrong variant");
		}
	}

	virtual ~Response();
};


class ErrorResponse : Response {
private:
	QString message{""};
public:
	ErrorResponse(unsigned int clientID) : Response(clientID) {}

	inline const QString& getMessage() const { return message; }
	void translate(const server::responses::ResponseVar&& response) override;
	void translateFromJSON(const QString& str) override;

	~ErrorResponse() override {}
};

class TagsResponse : public Response {
private:
	// I use pointers here to easily move values and not copy them
	QSharedPointer<QVector<QString>> courses;
	QSharedPointer<QVector<QString>> cusines;
	QSharedPointer<QVector<QString>> ingredients;
public:
	TagsResponse(unsigned int clientID);

	QSharedPointer<QVector<QString>> getCourses();
	QSharedPointer<QVector<QString>> getCusines();
	QSharedPointer<QVector<QString>> getIngredients();

	void translate(const server::responses::ResponseVar&&) override;
	void translateFromJSON(const QString& str) override;

	~TagsResponse() override {}
};

class SearchResponse : public Response {
private:
	// It kinda looks awfull but I use pointers to move less data in function calls
	QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> foundRecipes;
public:
	SearchResponse(unsigned int clientID);

	QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> getRecipes();
	void translate(const server::responses::ResponseVar&& responseToTranslate);
	void translateFromJSON(const QString& str) override;

	~SearchResponse() override {}
};

class AddResponse : public Response {
private:
	// TODO ask server for returning newly created ID
	unsigned int settedID{0};
	inline unsigned int getID() const { return settedID; }
public:
	AddResponse(unsigned int clientID, unsigned newRecipeID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QString& str) override;

	~AddResponse() override {}
};

class EditResponse : public Response {
public:
	EditResponse(unsigned int clientID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QString& str) override;

	~EditResponse() override {}
};

class RemoveResponse : public Response {
public:
	RemoveResponse(unsigned int clientID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QString& str) override;

	~RemoveResponse() override {}
};

} // namespace BaseTypes

#endif // RESPONSES_H