#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QSet>
#include <QMap>
#include "../server/recipe/include/recipe.h"

namespace BaseTypes {

class Recipe {
private:
	unsigned int id{0};
	bool hasInitializedID{false};
public:
	struct IngredientAmount{
		double quantity;
		QString unit;
	};

	QString name{""};
	QString recipeText{""};
	QString presentationText{""};
	QString remarks{""};

	QSet<QString> cusines; // I use set for future use of more than one cuisines
	QSet<QString> courses; // The same as for courses

	QMap<QString, IngredientAmount> ingredients;
	double outCalories{0};
	double outWeight{0};
	unsigned int outPortions{1};

	// Returns reference to ID if it was initialized
	const unsigned int* getID() const;

	Recipe(unsigned int recipeID);

	Recipe() : hasInitializedID(false) {}

	// TODO maybe move this functions to connections namespace,
	// TODO They only polute includes and class, but needed only in connection namespace
	void translateFromServer(server::recipe::Recipe response);
	server::recipe::Recipe translateToServer() const;

};

}


#endif // RECIPE_H
