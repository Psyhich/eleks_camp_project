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
	currentLayout->addLayout(gridLayout);

	ingredientFilters = new IngredientsFilterWidget(QSharedPointer<QSet<QString>>(new QSet<QString>()), this);
	ingredientFilters->setHidden(true);
	currentLayout->addWidget(ingredientFilters);

	QObject::connect(searchWithIngredients, &QCheckBox::clicked, ingredientFilters, &QWidget::setVisible);
	QObject::connect(searchWithIngredients, &QCheckBox::clicked, searchExact, &QWidget::setEnabled);

	setLayout(currentLayout);
}

CriteriaWidget::NotFullRequest CriteriaWidget::getNotFullRequest(){
	NotFullRequest requestToReturn;
	requestToReturn.course = courseSetter->currentText();
	requestToReturn.cusine = cusineSetter->currentText();
	if(searchWithIngredients->isChecked()){
		requestToReturn.ingredients = ingredientFilters->getIngredientFilter();
		requestToReturn.serchExact = searchExact->isChecked();
	}
	return requestToReturn;
}

void CriteriaWidget::updateTags(BaseTypes::Responses::TagsResponse tagsToUpdate){

	courseSetter->clear();
	tagsToUpdate.getCourses()->insert("");
	courseSetter->insertItems(0, tagsToUpdate.getCourses()->values());

	cusineSetter->clear();
	tagsToUpdate.getCusines()->insert("");
	cusineSetter->insertItems(0, tagsToUpdate.getCusines()->values());

	ingredientFilters->updateFilters(tagsToUpdate.getIngredients());

}
