#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ingredients_filter_widget.h"


IngredientRowFilter::IngredientRowFilter(
	QSharedPointer<QSet<QString>> variants, QWidget *parrent) : RowDisplay(parrent) {
	QHBoxLayout *rowLayout = new QHBoxLayout(this);

	ingredientFilter = new QComboBox(this);
	ingredientFilter->addItems(variants->values());
	rowLayout->addWidget(ingredientFilter, 1);

	QPushButton *closeButton = new QPushButton(this);
	QObject::connect(closeButton, SIGNAL(clicked()), this, SIGNAL(deletePressed()));
	rowLayout->addWidget(closeButton);

	setLayout(rowLayout);
}

void IngredientRowFilter::updateVariants(
	QSharedPointer<QSet<QString>> newVariants){
	ingredientFilter->clear();
	ingredientFilter->addItems(newVariants->values());
}


QVector<QString> IngredientRowFilter::getStrings(){
	return {ingredientFilter->currentText()};
}
IngredientsFilterWidget::IngredientsFilterWidget(QSharedPointer<QSet<QString>> variants, QWidget *parrent) : RowHolder(parrent) {
	filterVariants = variants;
}

void IngredientsFilterWidget::updateFilters(QSharedPointer<QSet<QString>> newVariants){
	filterVariants = newVariants;

	for(auto child : getRows()){
	  dynamic_cast<IngredientRowFilter*>(child)->updateVariants(newVariants);
	}
}

QSet<QString> IngredientsFilterWidget::getIngredientFilter() {
	QSet<QString> ingredients;
	for(auto row : getRows()){
			ingredients.insert(row->getStrings()[0]);
	}
	return ingredients;
}


RowDisplay *IngredientsFilterWidget::createRow() {
  return new IngredientRowFilter(filterVariants);
}
