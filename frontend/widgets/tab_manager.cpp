#include "tab_manager.h"

#include "recipe_view_tab.h"
#include "recipe_edit_tab.h"

#include "types/favorites_manager.h"
#include "connection_manager.h"

TabManager::TabManager(QWidget* parrent) : QTabWidget(parrent) {
	searchTab = new SearchTab();
	addTab(searchTab, "Search");

	// Hiding close button for search tab

	// Making tabs closable
	QObject::connect(this, &TabManager::tabCloseRequested, this, &TabManager::closeRecipe);

	// Connecting requests from search tab with own slots
	QObject::connect(searchTab, &SearchTab::requestOpenRecipe, this, &TabManager::openRecipe);
	QObject::connect(searchTab, &SearchTab::requestEditRecipe, this, &TabManager::editRecipe);
	// Connecting add to favorites signal
	QObject::connect(searchTab, &SearchTab::requestFavoriteRecipe, this, &TabManager::toggleFavoriteRecipe);
}

void TabManager::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){
  RecipeViewTab *recipeTab = new RecipeViewTab(recipeToOpen);
  setCurrentIndex(addTab(recipeTab, recipeToOpen->name));

}

void TabManager::closeRecipe(int tabID){
  removeTab(tabID);
}

void TabManager::closeTab(QWidget *tabToClose) {
  tabToClose->deleteLater();
}

void TabManager::toggleFavoriteRecipe(unsigned int recipeToFavorite) {
	FavoritesManager::getManager().toggleFavorite(recipeToFavorite);
}

void TabManager::editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){
  RecipeEditTab *editTab = new RecipeEditTab(recipeToOpen, this);

  QObject::connect(editTab, &RecipeEditTab::requestSaveRecipe, this, &TabManager::saveRecipe);
  QObject::connect(editTab, &RecipeEditTab::requestDeleteRecipe, this, &TabManager::deleteRecipe);
  QObject::connect(editTab, &RecipeEditTab::requestCloseTab, this, &TabManager::closeTab);

  setCurrentIndex(addTab(editTab, recipeToOpen.isNull() ? "New Recipe" : recipeToOpen->name));
  editTab->populateInputs(Connections::ConnectionManager::getManager().getTags().getTags());
}

void TabManager::saveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave){
  // TODO think about error handling
  if(*recipeToSave->getID() != 0){ // Only recipes with ID 0 aren't posted to server
	Connections::ConnectionManager::getManager().editRecipe(recipeToSave);
  }else{
	Connections::ConnectionManager::getManager().sendRecipe(recipeToSave);
  }
}

void TabManager::deleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete){
  // TODO the same here, error handling
  if(*recipeToDelete->getID() != 0){
	Connections::ConnectionManager::getManager().removeRecipe(*recipeToDelete->getID());
  }
}
