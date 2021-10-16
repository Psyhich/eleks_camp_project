#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <QTabWidget>
#include <QWidget>
#include <QSharedPointer>

#include "abstract_tab.h"
#include "search_tab.h"
#include "front_recipe.h"

class TabManager : public QTabWidget {
private:
	SearchTab *searchTab;

	QVector<QSharedPointer<BaseTypes::Recipe>> foundRecipes; // All recipes that can appear in search tab
	QVector<AbstractTab *> openedTabs;

	// For calling update recipes should have same ID
	void applyOpenedRecipesUpdate(QSharedPointer<BaseTypes::Recipe> recipeToUpdate);
	void applyFoundRecipesUpdate(QSharedPointer<BaseTypes::Recipe> recipeToUpdate);

public:
	TabManager(QWidget *parrent=nullptr);
signals:

public slots:
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void queryRecipes(BaseTypes::Query searchQuery);

	void toggleFavoriteRecipe(unsigned int recipeToFavorite);
	void closeAbstractTab(AbstractTab *tabToClose);
private slots:
	void closeTab(int tabID);
	void saveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave);
	void deleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete);
};

#endif // TAB_MANAGER_H
