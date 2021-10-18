#ifndef FRONT_RESPONSES_H
#define FRONT_RESPONSES_H

#include <QMap>
#include <QString>
#include <QSet>
#include <QVector>
#include <QSharedPointer>
#include <QJsonObject>
#include <QDebug>
#include <stdexcept>
#include <optional>

#include "front_recipe.h"
#include "response_structs.h"
#include "responses.h"

namespace BaseTypes::Responses {


class Response {
private:
	bool succesfull{false};
protected:
	inline void setSuccesfull(bool value){ succesfull = value; }
public:
	Response() {}

	inline bool isSuccessfull() { return succesfull; }

	virtual void translate(const server::responses::ResponseVar&& response) = 0;
	virtual void translateFromJSON(const QJsonObject& json) = 0;

	template<class T> static std::optional<T> extractType(server::responses::ResponseVar response){
		try {
			T extracted = std::move(std::get<T>(response));
			return extracted;
		}  catch (const std::bad_variant_access&) {
			return std::nullopt;
		}
	}

	virtual ~Response();
};

class ErrorResponse : Response {
private:
	static const int responseTag = 0;
	QString message{""};
public:
	ErrorResponse() {}

	inline const QString& getMessage() const { return message; }
	void translate(const server::responses::ResponseVar&& response) override;
	void translateFromJSON(const QJsonObject& json) override;

	~ErrorResponse() override {}
};

class TagsResponse : public Response {
private:
	static const int responseTag = 1;
	TagsHolder tags;

	// I use pointers here to easily move values and not copy them
public:
	TagsResponse();

	TagsHolder&& getTags();

	void translate(const server::responses::ResponseVar&&) override;
	void translateFromJSON(const QJsonObject& json) override;

	~TagsResponse() override {}
};

class SearchResponse : public Response {
private:
	static const int responseTag = 2;

	QVector<QSharedPointer<BaseTypes::Recipe>> foundRecipes;
public:
	SearchResponse();

	QVector<QSharedPointer<BaseTypes::Recipe>>&& getRecipes();
	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;

	~SearchResponse() override {}
};

class AddResponse : public Response {
private:
	static const int responseTag = 3;
	unsigned int settedID{0};
	inline unsigned int getID() const { return settedID; }
public:
	AddResponse(unsigned newRecipeID=0);

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;
	inline unsigned int getSettedID() { return settedID; }

	~AddResponse() override {}
};

class EditResponse : public Response {
private:
	static const int responseTag = 4;
public:
	EditResponse();

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;

	~EditResponse() override {}
};

class RemoveResponse : public Response {
private:
	static const int responseTag = 5;
public:
	RemoveResponse();

	void translate(const server::responses::ResponseVar&& responseToTranslate) override;
	void translateFromJSON(const QJsonObject& json) override;

	~RemoveResponse() override {}
};

} // namespace BaseTypes

#endif // FRONT_RESPONSES_H
