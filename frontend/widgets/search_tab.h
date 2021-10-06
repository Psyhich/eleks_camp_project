#ifndef SEARCH_TAB_H
#define SEARCH_TAB_H

#include <QWidget>

#include "search_filters.h"
#include "recipes_list_view.h"

class SearchTab : public QWidget {
Q_OBJECT
private:
	SearchFilters *filters;
	RecipesListView *recipesView;

public:
	SearchTab(QWidget *parent = nullptr);

signals:
	void requestOpenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void requestEditRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit);
	void requestFavoriteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit);
public slots:
	void runSearch();

};

#endif // SEARCH_TAB_H
