#ifndef BASE_RECIPE_TYPES_H
#define BASE_RECIPE_TYPES_H

#include <QMap>
#include <QString>
#include <QSet>

namespace BaseTypes {

struct RequestQuery {
	QList<unsigned int> favoriteIDs;
	QString name;
	QSet<QString> courses;
	QSet<QString> cuisines;
	QList<QString> ingredients;
	bool searchExclusively;

	RequestQuery(QList<unsigned int> _favoriteIDs, QString _name, QSet<QString> _courses,
				 QSet<QString> _cuisines, QList<QString> _ingredients, bool _searchExclusively) :
	  favoriteIDs(_favoriteIDs), name(_name), courses(_courses), cuisines(_cuisines), ingredients(_ingredients), searchExclusively(_searchExclusively) {}
};

class Response {};

// Base class that responds for holding data about recipe
class Recipe : public Response{
private:
  unsigned int id;
  bool hasInitializedID = false;
public:
	QString name;
	QSet<QString> cuisines; // I use set for future use of more than one cuisines
	QSet<QString> courses; // The same as for courses

	QMap<QString, int> ingredients;
	double outCalories;
	double outWeight;
	unsigned int outPortions;

	QString recipeText;
	QString presentationText;

	// Returns reference to ID if it was initialized
	const unsigned int* getID();

	Recipe(unsigned int recipeID);
	Recipe(){}
};

// Response that could be held when asking for different tags
class StringsResponse : public Response, public QSet<QString> {};

} // namespace BaseTypes

#endif // BASE_RECIPE_TYPES_H
