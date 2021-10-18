#ifndef RECIPE_EDIT_TAB_H
#define RECIPE_EDIT_TAB_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "abstract_tab.h"

#include "front_recipe.h"
#include "response_structs.h"

#include "ingredients_edit_widget.h"

class RecipeEditTab : public AbstractTab {
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

	void reopenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToReopen);

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
	RecipeEditTab(TabManager *parent,
				  QSharedPointer<BaseTypes::Recipe> recipeToOpen=nullptr);

	void populateInputs(const BaseTypes::TagsHolder& tagsForUpdate);

signals:
	void requestSaveRecipe(QSharedPointer<BaseTypes::Recipe> recipeToSave);
	void requestDeleteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToDelete);
	void requestCloseTab(AbstractTab *tabAdress);


public slots:
	// AbstractTab interface
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) override;
	void updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) override;
	QVector<QSharedPointer<BaseTypes::Recipe> > getRecipes() const override;
};

#endif // RECIPE_EDIT_TAB_H
