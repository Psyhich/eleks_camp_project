#ifndef SEARCH_TAB_H
#define SEARCH_TAB_H

#include <QWidget>

#include "abstract_tab.h"
#include "search_filters.h"
#include "recipes_list_view.h"

class SearchTab : public AbstractTab {
	Q_OBJECT
private:
	SearchFilters *filters;
	RecipesListView *recipesView;

public:
	SearchTab(TabManager *parent);
	void runSearch();

signals:
	void requestOpenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void requestEditRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit);
	void requestFavoriteRecipe(unsigned int recipeToEdit);
	void requestSearch(BaseTypes::Query queryForSearch);
public slots:
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) override;
	QVector<QSharedPointer<BaseTypes::Recipe> > getRecipes() const override;

	void closeAll();
};

#endif // SEARCH_TAB_H
