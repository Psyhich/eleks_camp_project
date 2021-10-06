#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ingredients_filter_widget.h"

IngredientsFilterWidget::IngredientsFilterWidget(QSharedPointer<QSet<QString>> variants, QWidget *parrent) : QScrollArea(parrent) {
	filterVariants = variants;
	setWidgetResizable(true);

	QWidget *innerWidget = new QWidget(this);
	QVBoxLayout *mainLayout = new QVBoxLayout(innerWidget);

	addButton = new QPushButton("+", innerWidget);
	QObject::connect(addButton, &QPushButton::clicked, this, &IngredientsFilterWidget::addRow);
	mainLayout->addWidget(addButton, 0, Qt::AlignmentFlag::AlignRight);

	innerWidget->setLayout(mainLayout);
	setWidget(innerWidget);
}

void IngredientsFilterWidget::deleteFilter(IngredientRowFilter *filterToDelete){
	widget()->layout()->removeWidget(filterToDelete);
	rows.removeOne(filterToDelete);
	filterToDelete->deleteLater();
}

void IngredientsFilterWidget::addRow(){
	widget()->layout()->removeWidget(addButton);

	IngredientRowFilter *row = new IngredientRowFilter(filterVariants, widget());
	rows.append(row);

	QObject::connect(row, &IngredientRowFilter::deletePressed, this, &IngredientsFilterWidget::deleteFilter);
	widget()->layout()->addWidget(row);

	widget()->layout()->addWidget(addButton);
	widget()->layout()->setAlignment(addButton, Qt::AlignmentFlag::AlignRight);
}

void IngredientsFilterWidget::updateFilters(QSharedPointer<QSet<QString>> newVariants){
	filterVariants = newVariants;

	for(auto child : rows){
		child->updateVariants(newVariants);
	}
}

QSet<QString> IngredientsFilterWidget::getIngredientFilter() {
	QSet<QString> ingredients;
	for(auto row : rows){
			ingredients.insert(row->getFilter());
	}
	return ingredients;
}


IngredientRowFilter::IngredientRowFilter(
	QSharedPointer<QSet<QString>> variants, QWidget *parrent) : QWidget(parrent) {
	QHBoxLayout *rowLayout = new QHBoxLayout(this);

	ingredientFilter = new QComboBox(this);
	ingredientFilter->addItems(variants->values());
	rowLayout->addWidget(ingredientFilter, 1);

	QPushButton *closeButton = new QPushButton(this);
	QObject::connect(closeButton, &QPushButton::clicked, this, &IngredientRowFilter::emitDeletePressed);
	rowLayout->addWidget(closeButton);

	setLayout(rowLayout);
}

void IngredientRowFilter::updateVariants(
	QSharedPointer<QSet<QString>> newVariants){
	ingredientFilter->clear();
	ingredientFilter->addItems(newVariants->values());
}

void IngredientRowFilter::emitDeletePressed(){ emit deletePressed(this); }

QString IngredientRowFilter::getFilter(){
	return ingredientFilter->currentText();
}
