#ifndef INGREDIENTS_EDIT_WIDGET_H
#define INGREDIENTS_EDIT_WIDGET_H

#include <QWidget>
#include <QList>
#include <QSet>
#include <QComboBox>
#include <QDoubleSpinBox>

#include "row_holder.h"
#include "types/recipe.h"

class IngredientEditRow : public RowDisplay {
private:
	QComboBox *ingredientEdit;
	QDoubleSpinBox *ingredientCountEdit;
	QComboBox *unitEdit;
public:
	IngredientEditRow(QSet<QString> ingredients, QSet<QString> units, QWidget* parrent=nullptr);

	void updateIngredients(QSet<QString> newVariants);
	void updateUnits(QSet<QString> newUnits);

	QVector<QString> getStrings() override;
	void setStrings(const QVector<QString> &tupleToset) override;
};

class IngredientsEditWidget : public RowHolder {
Q_OBJECT
private:
	QSet<QString> ingredients;
	QSet<QString> units;
protected:
	RowDisplay* createRow() override;
public:
	IngredientsEditWidget(QWidget *parent = nullptr);

	QMap<QString, BaseTypes::Recipe::IngredientAmount> getIngredients();
	void loadIngredients(const QMap<QString, BaseTypes::Recipe::IngredientAmount> &ingredients);

public slots:
	void updateIngredientsSet(QSet<QString> newIngredients);
	void updateUnitsSet(QSet<QString> newUnits);
};

#endif // INGREDIENTS_EDIT_WIDGET_H
