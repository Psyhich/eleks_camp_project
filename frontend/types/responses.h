#ifndef RESPONSES_H
#define RESPONSES_H

#include <QMap>
#include <QString>
#include <QSet>
#include <QVector>
#include <QSharedPointer>
#include <QJsonObject>
#include <QDebug>

#include "recipe.h"
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
	virtual void translateFromJSON(const QJsonObject& json) = 0;

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
	static const int responseTag = 0;
	QString message{""};
public:
	ErrorResponse(unsigned int clientID) : Response(clientID) {}

	inline const QString& getMessage() const { return message; }
	void translate(const server::responses::ResponseVar&& response) override;
	void translateFromJSON(const QJsonObject& json) override;

	~ErrorResponse() override {}
};

class TagsResponse : public Response {
private:
	static const int responseTag = 1;
	// I use pointers here to easily move values and not copy them
	QSharedPointer<QSet<QString>> courses;
	QSharedPointer<QSet<QString>> cusines;
	QSharedPointer<QSet<QString>> ingredients;
	QSharedPointer<QSet<QString>> units;
public:
	TagsResponse(unsigned int clientID);

	QSharedPointer<QSet<QString>> getCourses();
	QSharedPointer<QSet<QString>> getCusines();
	QSharedPointer<QSet<QString>> getIngredients();
	QSharedPointer<QSet<QString>> getUnits();

	void translate(const server::responses::ResponseVar&&) override;
	void translateFromJSON(const QJsonObject& json) override;

	~TagsResponse() override {}
};

class SearchResponse : public Response {
private:
	static const int responseTag = 2;
	// It kinda looks awfull but I use pointers to move less data in function calls
	QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> foundRecipes;
public:
	SearchResponse(unsigned int clientID);

	QSharedPointer<QVector<QSharedPointer<BaseTypes::Recipe>>> getRecipes();
	void translate(const server::responses::ResponseVar&& responseToTranslate);
	void translateFromJSON(const QJsonObject& json) override;

	~SearchResponse() override {}
};

class AddResponse : public Response {
private:
	static const int responseTag = 3;
	unsigned int settedID{0};
	inline unsigned int getID() const { return settedID; }
public:
	AddResponse(unsigned int clientID, unsigned newRecipeID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;
	inline unsigned int getSettedID() { return settedID; }

	~AddResponse() override {}
};

class EditResponse : public Response {
private:
	static const int responseTag = 4;
public:
	EditResponse(unsigned int clientID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;

	~EditResponse() override {}
};

class RemoveResponse : public Response {
private:
	static const int responseTag = 5;
public:
	RemoveResponse(unsigned int clientID);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;

	~RemoveResponse() override {}
};

} // namespace BaseTypes

#endif // RESPONSES_H
