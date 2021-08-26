#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <QString>
#include <QHash>

namespace QBaseTypes {

  // Base class that responds for holding data about recipe
  class Recipe{
	  unsigned int id;
	  QString name;
	  QList<QString> tags;

	  QHash<QString, int> ingredients;
	  double outCalories;
	  double outWeight;
	  unsigned int outPortions;

	  QString recipeText;
	  QString presentationText;

	public:
	  unsigned int getId() const;
	  const QString&getName() const;
	  const QList<QString>& getTags() const;
	  const QHash<QString, int>& getIngredients() const;

	  double getCalories() const;
	  double getWeight() const;
	  unsigned int getBasePortionsCount() const;

	  const QString& getRecipeText() const;
	  const QString& getPresentationText() const;

	  virtual bool update() = 0; // Function that responds for saving new data of recipe
	  virtual bool load() = 0; // Function that responds for loading recipe from some resource into this class

  };

  // Child classes that would implement update and load method
  // Local recipe must be saved ONLY localy
  class LocalRecipe : public Recipe{
	// Recipe interface
	public:
	  bool update() override;
	  bool load() override;
  };

  // Remote recipe MUST be saved remotely, but CAN be cashed for future use
  class RemoteRecipe : public Recipe{
	// Recipe interface
	public:
	  bool update() override;
	  bool load() override;
  };



}

#endif // BASE_TYPES_H
