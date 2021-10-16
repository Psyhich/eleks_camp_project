#include <QVBoxLayout>

#include "search_tab.h"


SearchTab::SearchTab(TabManager *parent) : AbstractTab(parent) {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	filters = new SearchFilters(this);
	mainLayout->addWidget(filters, 0);

	QScrollArea	*scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	QVBoxLayout *innerLayout = new QVBoxLayout(scrollArea);

	recipesView = new RecipesListView(scrollArea);
	innerLayout->addWidget(recipesView);

	scrollArea->setWidget(recipesView);
	scrollArea->setLayout(innerLayout);

	mainLayout->addWidget(scrollArea, 1);

	setLayout(mainLayout);

	QObject::connect(filters, &SearchFilters::searchButtonClicked, this, &SearchTab::runSearch);

	// Connecting all requests from recipe view to itself
	QObject::connect(recipesView, &RecipesListView::requestOpenRecipe, this, &SearchTab::requestOpenRecipe);
	QObject::connect(recipesView, &RecipesListView::requestEditRecipe, this, &SearchTab::requestEditRecipe);
	QObject::connect(recipesView, &RecipesListView::requestFavoriteRecipe, this, &SearchTab::requestFavoriteRecipe);
}

void SearchTab::runSearch(){
	auto query = filters->getFilters();
	emit requestSearch(query);
}

void SearchTab::closeAll(){
  recipesView->clearRecipes();
}

// AbstractTab implementation
void SearchTab::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) {
  recipesView->addRecipe(recipeToOpen);
}
void SearchTab::closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToClose) {
  if(auto id = recipeToClose->getID()){
	recipesView->removeRecipe(*id);
  }
}
QVector<QSharedPointer<BaseTypes::Recipe> > SearchTab::getRecipes() const {
  return recipesView->getRecipes();
}
void SearchTab::updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) {
  recipesView->updateRecipe(recipeToUpdate);
}

