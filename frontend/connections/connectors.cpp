#include "connectors.h"
#include <QDebug>

using namespace Connections;


LocalConnector::LocalConnector() : IConnector(){

}

void LocalConnector::openConnection() {

}

void LocalConnector::closeConnection() {

}

QList<BaseTypes::Response*> LocalConnector::runQuery(BaseTypes::RequestQuery query) {
  qDebug() << "Got query" << query.name;

	BaseTypes::Recipe *recipe = new BaseTypes::Recipe(0);

	recipe->name = "Soup";
	recipe->courses.insert("Starter");
	recipe->cuisines.insert("Ukraine");
	recipe->ingredients = {{"Liter of water", 1}, {"Bowl", 1}, {"Spoon", 1}};
	recipe->outWeight = 1000;
	recipe->outCalories = 10;
	recipe->recipeText = "Take liter of water and boil it until it's hot";
	recipe->presentationText = "Pour hot water into bowl and eat with spoon";

  return {recipe};
}
void LocalConnector::postRecipe(BaseTypes::Recipe* recipeToPost) {

  qDebug() << recipeToPost->getID() << " " << recipeToPost->name;
}

LocalConnector::~LocalConnector() {

}
