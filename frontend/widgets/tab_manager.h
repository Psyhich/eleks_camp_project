#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <QTabWidget>
#include <QWidget>
#include <QSharedPointer>

#include "search_tab.h"
#include "types/recipe.h"

class TabManager : public QTabWidget {
private:
	SearchTab *searchTab;

	//QMap<unsigned int, QSharedPointer<BaseTypes::Recipe>> openedCache; // TODO implement recipe cache that will update all widgets that contain opened recipes
public:
	TabManager(QWidget *parrent=nullptr);
signals:

public slots:
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);

	void toggleFavoriteRecipe(unsigned int recipeToFavorite);
private slots:
	void closeRecipe(int tabID);
	void closeTab(QWidget *tabToClose);
	void saveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave);
	void deleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete);
};

#endif // TABMANAGER_H
