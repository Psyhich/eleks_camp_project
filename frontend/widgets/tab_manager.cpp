#include "tab_manager.h"
#include "recipe_view_tab.h"
#include "types/favorites_manager.h"

TabManager::TabManager(QWidget* parrent) : QTabWidget(parrent) {
	searchTab = new SearchTab();
	addTab(searchTab, "Search");

	// Hiding close button for search tab

	// Connecting requests from search tab with own slots
	QObject::connect(searchTab, &SearchTab::requestOpenRecipe, this, &TabManager::openRecipe);
	// Making tabs closable
	QObject::connect(this, &TabManager::tabCloseRequested, this, &TabManager::closeRecipe);
	// Connecting add to favorites signal
	QObject::connect(searchTab, &SearchTab::requestFavoriteRecipe, this, &TabManager::addToFavorites);
}

void TabManager::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){
  RecipeViewTab *recipeTab = new RecipeViewTab(recipeToOpen);
  addTab(recipeTab, recipeToOpen->name);
}

void TabManager::closeRecipe(int tabID){
  removeTab(tabID);
}

void TabManager::addToFavorites(unsigned int recipeID){
	FavoritesManager::getManager().addToFavorites(recipeID);
}
