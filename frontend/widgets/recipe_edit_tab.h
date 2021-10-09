#ifndef RECIPE_EDIT_TAB_H
#define RECIPE_EDIT_TAB_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "types/recipe.h"
#include "ingredients_edit_widget.h"

class RecipeEditTab : public QScrollArea {
Q_OBJECT
private:
	QSharedPointer<BaseTypes::Recipe> openedRecipe;

	QLineEdit *nameEdit;

	QComboBox *courseEdit;
	QComboBox *cusineEdit;

	QDoubleSpinBox *caloriesEdit;
	QDoubleSpinBox *weightEdit;
	QSpinBox *portionsEdit;

	IngredientsEditWidget *ingredientsEdit;

	QTextEdit *preparationEdit;
	QTextEdit *presentationEdit;
	QTextEdit *remarksEdit;

	QPushButton *saveButon;
	QPushButton *discardButon;
	QPushButton *deleteButon;

	// This function is needed because we don't need to mutate the original edited recipe
	QSharedPointer<BaseTypes::Recipe> collectNewRecipe();

	void emitRequestSaveRecipe();
	void emitRequestDeleteRecipe();

public:
	RecipeEditTab(QSharedPointer<BaseTypes::Recipe> recipeToOpen=nullptr,
				  QWidget *parent = nullptr);

signals:
	void requestSaveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave);
	void requestDeleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete);

};

#endif // RECIPE_EDIT_TAB_H
