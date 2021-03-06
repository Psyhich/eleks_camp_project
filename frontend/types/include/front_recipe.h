#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QSet>
#include <QMap>

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
};

}


#endif // RECIPE_H
