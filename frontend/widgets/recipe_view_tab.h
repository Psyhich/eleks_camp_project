#ifndef RECIPE_VIEW_TAB_H
#define RECIPE_VIEW_TAB_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QTextBrowser>
#include <QSpinBox>
#include <QTableWidget>

#include "types/recipe.h"

class RecipeViewTab : public QScrollArea {
	Q_OBJECT
private:
	// Qt Widgets
	QLabel *nameLabel;

	QLabel *recipeCalories;
	QLabel *recipeWeight;
	QSpinBox *recipePortions;

	QTableWidget *ingredientsWidget;
	QWidget *tagsWidget;

	QTextBrowser *recipePreparationText;
	QTextBrowser *recipePresentationText;

	// This class will only have pointer to current recipe and will notify about closing it
	// Something like cache for currently opened recipes will hold all recipes
	QSharedPointer<BaseTypes::Recipe> curretRecipe;
public:
	RecipeViewTab(QSharedPointer<BaseTypes::Recipe> recipeToShow, QWidget *parent = nullptr);
	~RecipeViewTab() override;

signals:
	void recipeClosed(unsigned int id);

public slots:
	void updateRecipe(); // Function to reapply all recipe data from pointer to this object
	void recalculateValues();

};

#endif // RECIPE_VIEW_TAB_H

