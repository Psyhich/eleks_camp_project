#include <QErrorMessage>

#include "tab_manager.h"

#include "recipe_view_tab.h"
#include "recipe_edit_tab.h"

#include "connection_manager.h"
#include "favorites_manager.h"

TabManager::TabManager(QWidget* parrent) : QTabWidget(parrent) {
	setTabsClosable(true);
	setTabPosition(QTabWidget::North);

	searchTab = new SearchTab(this);
	insertTab(0, searchTab, "Search");

	// Hiding close button for search tab
	// Access by tabBar->tabButton doesn't work
	QList<QWidget*> tabButton = tabBar()->findChildren<QWidget*>();
	tabButton[0]->resize(0, 0);
	tabButton[0]->hide();

	// Making tabs closable
	QObject::connect(this, &QTabWidget::tabCloseRequested, this, &TabManager::closeTab);

	// Connecting requests from search tab with own slots
	QObject::connect(searchTab, &SearchTab::requestOpenRecipe, this, &TabManager::openRecipe);
	QObject::connect(searchTab, &SearchTab::requestEditRecipe, this, &TabManager::editRecipe);
	QObject::connect(searchTab, &SearchTab::requestSearch, this, &TabManager::queryRecipes);
	QObject::connect(searchTab, &SearchTab::requestFieldsUpdate, this, [&](){
	  auto response = Connections::ConnectionManager::getManager().getTags();
	  if(response.isSuccessfull()){
		searchTab->updateFields(std::move(response.getTags()));
	  }
	});
	// Connecting add to favorites signal
	QObject::connect(searchTab, &SearchTab::requestFavoriteRecipe, this, &TabManager::toggleFavoriteRecipe);
}

void TabManager::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){
  RecipeViewTab *recipeTab = new RecipeViewTab(recipeToOpen);
  setCurrentIndex(addTab(recipeTab, recipeToOpen->name));

}

void TabManager::closeTab(int tabID){
  removeTab(tabID);
}

void TabManager::closeAbstractTab(AbstractTab *tabToClose) {
  tabToClose->deleteLater();
}

void TabManager::toggleFavoriteRecipe(unsigned int recipeToFavorite) {
	FavoritesManager::getManager().toggleFavorite(recipeToFavorite);
}

void TabManager::queryRecipes(BaseTypes::Query searchQuery){
  auto response = Connections::ConnectionManager::getManager().runSearch(std::move(searchQuery));
  if(response.isSuccessfull()){
	searchTab->closeAll();
	for(auto recipe : response.getRecipes()){
	  searchTab->openRecipe(recipe);
	  foundRecipes.append(recipe);
	  applyOpenedRecipesUpdate(recipe);
	}
  }else{
	QErrorMessage().showMessage("There was an error during search your recipes");
  }
}

void TabManager::editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen){
  RecipeEditTab *editTab = new RecipeEditTab(this, recipeToOpen);

  QObject::connect(editTab, &RecipeEditTab::requestSaveRecipe, this, &TabManager::saveRecipe);
  QObject::connect(editTab, &RecipeEditTab::requestDeleteRecipe, this, &TabManager::deleteRecipe);
  QObject::connect(editTab, &RecipeEditTab::requestCloseTab, this, &TabManager::closeAbstractTab);

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

void TabManager::applyOpenedRecipesUpdate(QSharedPointer<BaseTypes::Recipe> recipeToUpdate){
  if(!recipeToUpdate->getID()) return;
  unsigned int id = *recipeToUpdate->getID();

  for(auto tab : openedTabs) {
	for(auto recipe : tab->getRecipes()){
	  auto recipeID = recipe->getID();
	  if(recipeID && *recipeID == id){
		tab->updateRecipe(recipeToUpdate);
		break; // Breaking bacause tab can't have 2 same recipes
	  }
	}
  }
}

void TabManager::applyFoundRecipesUpdate(QSharedPointer<BaseTypes::Recipe> recipeToUpdate){
  if(!recipeToUpdate->getID()) return;
  unsigned int id = *recipeToUpdate->getID();

  for(auto recipe : foundRecipes) {
	if(*recipe->getID() == id) {
	  searchTab->updateRecipe(recipeToUpdate);
	  break;
	}
  }
}
