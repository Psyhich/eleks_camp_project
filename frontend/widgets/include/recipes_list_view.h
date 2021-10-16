#ifndef RECIPES_LIST_VIEW_H
#define RECIPES_LIST_VIEW_H

#include <QScrollArea>
#include <QSharedPointer>
#include <QWidget>

#include "recipe_row_view.h"

class RecipesListView : public QWidget {
	Q_OBJECT
private:
	//QSet<QSharedPointer<BaseTypes::Recipe>> recipeCache; // TODO implement recipe cache to update all widgets that contain opened recipe
	QList<RecipeRowView *> rows;

public:
	RecipesListView(QWidget *parrent=nullptr);

	QVector<QSharedPointer<BaseTypes::Recipe>> getRecipes() const;

signals:
	void requestOpenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void requestEditRecipe(QSharedPointer<BaseTypes::Recipe> recipeToEdit);
	void requestFavoriteRecipe(unsigned int recipeID);

public slots:
	void addRecipe(QSharedPointer<BaseTypes::Recipe> recipeToAdd);
	void removeRecipe(unsigned int recipeID);
	void clearRecipes();
	void updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate);

};

#endif // RECIPES_LIST_VIEW_H
