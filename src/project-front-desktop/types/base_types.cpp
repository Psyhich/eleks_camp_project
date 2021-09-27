#include "base_types.h"

namespace BaseTypes {
  // Recipe methods
  Recipe::Recipe(unsigned int id, QString name, QSet<QString> courses, QSet<QString> cusines,
			  QMap<QString, int> ingredients, double calories, double weight,
			  unsigned int basePortionCount, QString text,
				 QString presentationText){
	this->id = id;
	this->name = name;
	this->courses = courses;
	this->cuisines = cusines;
	this->ingredients = ingredients;
	this->outCalories = calories;
	this->outWeight = weight;
	this->outPortions = basePortionCount;
	this->recipeText = text;
	this->presentationText = presentationText;
  }

  Recipe::Recipe() {}

  // Setters
  inline void Recipe::setId(unsigned int id){ this->id = id; }
  inline void Recipe::setName(QString name) { this->name = name;}

  inline void Recipe::setCourses(QSet<QString> newCourses) { this->courses = newCourses; }
  inline void Recipe::setCuisines(QSet<QString> newCuisines) { this->cuisines = newCuisines; }
  inline void Recipe::setIngredients(QMap<QString, int> ingredients) { this->ingredients = ingredients; }

  inline void Recipe::setCalories(double calories) { this->outCalories = calories; }
  inline void Recipe::setWeight(double weight) { this->outWeight = weight; }
  inline void Recipe::setPortions(unsigned int portions) { this->outPortions = portions; }

  inline void Recipe::setText(QString text) { this->recipeText = text; }
  inline void Recipe::setPresentation(QString presentation) { this->presentationText = presentation; }



  // LocalRecipe methods
  LocalRecipe::LocalRecipe(unsigned int id, QString name, QSet<QString> courses, QSet<QString> cusines,
			  QMap<QString, int> ingredients, double calories, double weight,
			  unsigned int basePortionCount, QString text,
			  QString presentationText) : Recipe(id, name, courses, cusines, ingredients, calories, weight, basePortionCount, text, presentationText){
  }
  bool LocalRecipe::update() {
	// TODO implement
	return true;
  }
  bool LocalRecipe::load(){
	// TODO implement
	return false;
  }


  // RemoteRecipe methods
  bool RemoteRecipe::update(){
	// TODO implement
	return true;
  }
  bool RemoteRecipe::load(){
	// TODO implement
	return false;
  }

}
