#ifndef RECIPE_VIEW_TAB_H
#define RECIPE_VIEW_TAB_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QSpinBox>
#include <QTableWidget>

#include "front_recipe.h"
#include "abstract_tab.h"

class RecipeViewTab : public AbstractTab {
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
	QTextBrowser *recipeRemarksText;

	// This class will only have pointer to current recipe and will notify about closing it
	// Something like cache for currently opened recipes will hold all recipes
	QSharedPointer<BaseTypes::Recipe> curretRecipe;

	QWidget *createTagsWidget();
	QLayout *createBaseValues();
	QLayout *createIngredientsTable();
	QLayout *createRecipeTexts();


public:
	RecipeViewTab(QSharedPointer<BaseTypes::Recipe> recipeToShow, TabManager *parent = nullptr);
	~RecipeViewTab() override;

signals:
	void recipeClosed(unsigned int id);

public slots:
	void recalculateValues();


	// AbstractTab interface
public slots:
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) override;
	QVector<QSharedPointer<BaseTypes::Recipe> > getRecipes() const override;
};

#endif // RECIPE_VIEW_TAB_H

