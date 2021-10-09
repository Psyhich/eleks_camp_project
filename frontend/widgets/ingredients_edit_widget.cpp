#include <QHBoxLayout>

#include "ingredients_edit_widget.h"

// IngredientEditRow class
IngredientEditRow::IngredientEditRow(
	QSet<QString> ingredients, QSet<QString> units, QWidget *parrent) : RowDisplay(parrent) {

	QHBoxLayout *mainLayout = new QHBoxLayout(this);

	ingredientEdit = new QComboBox(this);
	ingredientEdit->setEditable(true);
	mainLayout->addWidget(ingredientEdit);


	ingredientCountEdit = new QDoubleSpinBox(this);
	ingredientCountEdit->setMinimum(0);
	mainLayout->addWidget(ingredientCountEdit);


	unitEdit = new QComboBox(this);
	unitEdit->setEditable(true);
	mainLayout->addWidget(unitEdit);

	setLayout(mainLayout);

	updateIngredients(ingredients);
	updateUnits(units);
}

void IngredientEditRow::updateIngredients(QSet<QString> newVariants){
	ingredientEdit->clear();
	ingredientEdit->addItems(newVariants.values());
}

void IngredientEditRow::updateUnits(QSet<QString> newUnits){
	unitEdit->clear();
	unitEdit->addItems(newUnits.values());
}


QVector<QString> IngredientEditRow::getStrings(){
	return {ingredientEdit->itemText(0), ingredientCountEdit->text(), unitEdit->itemText(0)};
}

void IngredientEditRow::setStrings(const QVector<QString> &tupleToset) {
  // Vector should be in format {name, count, unit}
  ingredientEdit->setCurrentText(tupleToset[0]);
  ingredientCountEdit->setValue(tupleToset[1].toDouble());
  unitEdit->setCurrentText(tupleToset[2]);
}

// IngredientsEditWidget class
RowDisplay* IngredientsEditWidget::createRow() {
  return new IngredientEditRow(ingredients, units);

}

IngredientsEditWidget::IngredientsEditWidget(QWidget *parent) : RowHolder(parent) {

}

void IngredientsEditWidget::updateIngredientsSet(QSet<QString> newIngredients){
  ingredients = newIngredients;
  for(auto row : getRows()){
	dynamic_cast<IngredientEditRow*>(row)->updateIngredients(ingredients);
  }
}

void IngredientsEditWidget::updateUnitsSet(QSet<QString> newUnits){
  units = newUnits;
  for(auto row : getRows()){
	dynamic_cast<IngredientEditRow*>(row)->updateUnits(units);
  }
}

QMap<QString, BaseTypes::Recipe::IngredientAmount> IngredientsEditWidget::getIngredients(){
	QMap<QString, BaseTypes::Recipe::IngredientAmount> ingredients;
	// Every row return array of 3 {ingredient name, count, unit}
	for(auto row : getRows()){
		QVector<QString> tuple = row->getStrings();

		ingredients.insert(tuple[0],
			BaseTypes::Recipe::IngredientAmount{tuple[1].toDouble(), tuple[2]});
	}
	return ingredients;
}

void IngredientsEditWidget::loadIngredients(
	const QMap<QString, BaseTypes::Recipe::IngredientAmount> &ingredients){
	// Creating enough rows to change their values
	int row = getRows().count();
	for (; row < ingredients.count(); row++) { addRow(); }

	// Now, changing values of each row
	row = 0;
	for(auto ingredientName : ingredients.keys()){
		BaseTypes::Recipe::IngredientAmount amount = ingredients.value(ingredientName);
		getRows()[row]->setStrings({
				ingredientName, QString::number(amount.quantity), amount.unit});
		row++;
	}

}
