#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ingredients_filter_widget.h"

IngredientsFilterWidget::IngredientsFilterWidget(QSharedPointer<QSet<QString>> variants, QWidget *parrent) : QScrollArea(parrent) {
	filterVariants = variants;
	setWidgetResizable(true);

	QWidget *innerWidget = new QWidget(this);
	QVBoxLayout *mainLayout = new QVBoxLayout(innerWidget);

	addButton = new QPushButton("+", innerWidget);
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addRow()));
	mainLayout->addWidget(addButton, 0, Qt::AlignmentFlag::AlignRight);

	innerWidget->setLayout(mainLayout);
	setWidget(innerWidget);
}

void IngredientsFilterWidget::deleteFilter(IngredientRowFilter *filterToDelete){
	widget()->layout()->removeWidget(filterToDelete);
	filterToDelete->deleteLater();
}

void IngredientsFilterWidget::addRow(){
	widget()->layout()->removeWidget(addButton);

	widget()->layout()->addWidget(new IngredientRowFilter(filterVariants, widget()));

	widget()->layout()->addWidget(addButton);
	widget()->layout()->setAlignment(addButton, Qt::AlignmentFlag::AlignRight);
}

void IngredientsFilterWidget::updateFilters(QSharedPointer<QSet<QString>> newVariants){
	filterVariants = newVariants;
	for(auto child : widget()->children()){
		if(child != addButton){
			reinterpret_cast<IngredientRowFilter*>(child)->updateVariants(newVariants);
		}
	}
}

QSet<QString> IngredientsFilterWidget::getIngredientFilter() {
	QSet<QString> ingredients;
	for(auto child : widget()->children()){
		if(child != addButton){
			ingredients.insert(reinterpret_cast<IngredientRowFilter*>(child)->getFilter());
		}
	}
	return ingredients;
}


IngredientsFilterWidget::IngredientRowFilter::IngredientRowFilter(
	QSharedPointer<QSet<QString>> variants, QWidget *parrent) : QWidget(parrent) {
	QHBoxLayout *rowLayout = new QHBoxLayout(this);

	ingredientFilter = new QComboBox(this);
	ingredientFilter->addItems(variants->values());
	rowLayout->addWidget(ingredientFilter, 1);

	QPushButton *closeButton = new QPushButton(this);
	QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(emitDeletePressed()));
	rowLayout->addWidget(closeButton);

	setLayout(rowLayout);
}

void IngredientsFilterWidget::IngredientRowFilter::updateVariants(
	QSharedPointer<QSet<QString>> newVariants){
	ingredientFilter->clear();
	ingredientFilter->addItems(newVariants->values());
}

void IngredientsFilterWidget::IngredientRowFilter::emitDeletePressed(){ emit deletePressed(this); }

QString IngredientsFilterWidget::IngredientRowFilter::getFilter(){
	return ingredientFilter->currentText();
}
