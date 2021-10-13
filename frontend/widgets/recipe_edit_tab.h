#ifndef RECIPE_EDIT_TAB_H
#define RECIPE_EDIT_TAB_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "types/recipe.h"
#include "types/responses.h"

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
	QSharedPointer<BaseTypes::Recipe> collectNewRecipe() const;

	// Emitters
	void emitRequestSaveRecipe();
	void emitRequestDeleteRecipe();

	void emitRequestCloseTab();

	// Construction functions
	QLayout* createForm() noexcept;
	QLayout* createTextPannels() noexcept;
	QLayout* createBottomPanel() noexcept;

public:
	RecipeEditTab(QSharedPointer<BaseTypes::Recipe> recipeToOpen=nullptr,
				  QWidget *parent = nullptr);

	void populateInputs(BaseTypes::Responses::TagsResponse);

signals:
	void requestSaveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave);
	void requestDeleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete);
	void requestCloseTab(QWidget *tabAdress);

};

#endif // RECIPE_EDIT_TAB_H
