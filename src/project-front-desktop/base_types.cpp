#include "base_types.h"

namespace BaseTypes {
  // Recipe methods
  // Setters
  inline void Recipe::setId(unsigned int id){ this->id = id; }
  inline void Recipe::setName(QString name) { this->name = name;}
  inline void Recipe::setTags(QList<QString> tags) { this->tags = tags; }

  inline void Recipe::setIngredients(QMap<QString, int> ingredients) { this->ingredients = ingredients; }
  inline void Recipe::setCalories(double calories) { this->outCalories = calories; }
  inline void Recipe::setWeight(double weight) { this->outWeight = weight; }
  inline void Recipe::setPortions(unsigned int portions) { this->outPortions = portions; }
  inline void Recipe::setText(QString text) { this->recipeText = text; }
  inline void Recipe::setPresentation(QString presentation) { this->presentationText = presentation; }


  // LocalRecipe methods
  LocalRecipe::LocalRecipe(unsigned int id, QString name, QList<QString> tags, QMap<QString, int> ingredients, double calories, double weight, unsigned int basePortionCount, QString text, QString presentationText){
	setId(id);
	setName(name);
	setTags(tags);
	setIngredients(ingredients);
	setCalories(calories);
	setWeight(weight);
	setPortions(basePortionCount);
	setText(text);
	setPresentation(presentationText);
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
