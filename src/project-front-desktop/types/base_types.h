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
};

class Response {};

// Base class that responds for holding data about recipe
class Recipe : public Response{
  unsigned int id;
  QString name;
  QSet<QString> cuisines; // I use set for future use of more than one cuisines
  QSet<QString> courses; // The same as for courses

  QMap<QString, int> ingredients;
  double outCalories;
  double outWeight;
  unsigned int outPortions;

  QString recipeText;
  QString presentationText;

protected:
  inline void setId(unsigned int id);
  inline void setName(QString name);

  inline void setCuisines(QSet<QString> newCuisines);
  inline void setCourses(QSet<QString> newCourses);
  inline void setIngredients(QMap<QString, int> ingredients);

  inline void setCalories(double calories);
  inline void setWeight(double weight);
  inline void setPortions(unsigned int portions);

  inline void setText(QString text);
  inline void setPresentation(QString presentation);

public:
	inline unsigned int getId() const { return id; }
	inline const QString &getName() const { return name; }

	inline const QSet<QString> &getCusines() const { return cuisines; }
	inline const QSet<QString> &getCourses() const { return courses; }
	inline const QMap<QString, int> &getIngredients() const { return ingredients; }

	inline double getCalories() const { return outCalories; }
	inline double getWeight() const { return outWeight; }
	inline unsigned int getBasePortionsCount() const { return outPortions; }

	inline const QString &getRecipeText() const { return recipeText; }
	inline const QString &getPresentationText() const { return presentationText; }

	// Function that responds for saving new data of recipe
	virtual bool update() = 0;

	// Function that responds for loading recipe from some resource into this class;
	virtual bool load() = 0;

	Recipe(unsigned int id, QString name, QSet<QString> courses, QSet<QString> cusines,
			  QMap<QString, int> ingredients, double calories, double weight,
			  unsigned int basePortionCount, QString text,
			  QString presentationText);
	Recipe();

	virtual ~Recipe() {}
};

// Child classes that would implement update and load method
// Local recipe must be saved ONLY localy
class LocalRecipe : public Recipe {
  // Recipe interface
public:
  LocalRecipe(unsigned int id, QString name, QSet<QString> courses, QSet<QString> cusines,
              QMap<QString, int> ingredients, double calories, double weight,
              unsigned int basePortionCount, QString text,
              QString presentationText);
  bool update() override;
  bool load() override;

  ~LocalRecipe() override {}
};

// Remote recipe MUST be saved remotely, but CAN be cashed for future use
class RemoteRecipe : public Recipe {
  // Recipe interface
public:
  bool update() override;
  bool load() override;

  ~RemoteRecipe() override {}
};

// Response that could be held when asking for different tags
class StringsResponse : public Response, public QSet<QString> {};

} // namespace BaseTypes

#endif // BASE_RECIPE_TYPES_H
