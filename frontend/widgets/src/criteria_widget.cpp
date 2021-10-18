#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "criteria_widget.h"

CriteriaWidget::CriteriaWidget(QWidget *parent) : QWidget(parent) {
	QVBoxLayout *currentLayout = new QVBoxLayout(this);

	// Creating basic grid with labels and sping boxes for course and cusine
	QGridLayout *gridLayout = new QGridLayout();
		QLabel *courseLabel = new QLabel("Course:", this);
		gridLayout->addWidget(courseLabel, 0, 0);

		courseSetter = new QComboBox(this);
		gridLayout->addWidget(courseSetter, 0, 1);

		QLabel *cusineLabel = new QLabel("Cusine:", this);
		gridLayout->addWidget(cusineLabel, 0, 2);

		cusineSetter = new QComboBox(this);
		gridLayout->addWidget(cusineSetter, 0, 3);

		// Adding checkboxes
		searchWithIngredients = new QCheckBox("By ingredients", this);
		gridLayout->addWidget(searchWithIngredients, 1, 0);

		searchExact = new QCheckBox("Exact", this);
		searchExact->setDisabled(true);
		gridLayout->addWidget(searchExact, 1, 2);

		searchByFavorites = new QCheckBox("Use favorites", this);
		gridLayout->addWidget(searchByFavorites, 1, 3);

	currentLayout->addLayout(gridLayout);

	ingredientFilters = new IngredientsFilterWidget(QSet<QString>(), this);
	ingredientFilters->setHidden(true);
	currentLayout->addWidget(ingredientFilters);

	QObject::connect(searchWithIngredients, &QCheckBox::clicked, ingredientFilters, &QWidget::setVisible);
	QObject::connect(searchWithIngredients, &QCheckBox::clicked, searchExact, &QWidget::setEnabled);

	setLayout(currentLayout);
}

bool CriteriaWidget::partlyPopulateQuery(BaseTypes::Query &queryToPopulate){
	queryToPopulate.courses = {courseSetter->currentText()};
	queryToPopulate.cusines = {cusineSetter->currentText()};
	if(searchWithIngredients->isChecked()){
		queryToPopulate.ingredients = ingredientFilters->getIngredientFilter().values();
		queryToPopulate.searchExclusively = searchExact->isChecked();
	}
	return searchByFavorites->isChecked();
}

void CriteriaWidget::updateTags(const BaseTypes::TagsHolder& tagsToUpdate){

	courseSetter->clear();
	QList<QString> courseValues = tagsToUpdate.courses.values();
	courseValues.push_front("");
	courseSetter->insertItems(0, courseValues);

	cusineSetter->clear();
	QList<QString> cusineValues = tagsToUpdate.cusines.values();
	cusineValues.push_front("");
	cusineSetter->insertItems(0, cusineValues);

	ingredientFilters->updateFilters(tagsToUpdate.ingredients);
}
