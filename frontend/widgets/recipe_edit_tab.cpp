#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>


#include "recipe_edit_tab.h"

RecipeEditTab::RecipeEditTab(QWidget *parent) : QWidget(parent) {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	QGridLayout *formLayout = new QGridLayout();

		QLabel *nameEditLabel = new QLabel("Name of recipe:", this);
		formLayout->addWidget(nameEditLabel, 0, 0);

		nameEdit = new QLineEdit(this);
		formLayout->addWidget(nameEdit, 0, 1, 1, -1);

		QLabel *courseLabelEdit = new QLabel("Course:", this);
		formLayout->addWidget(courseLabelEdit, 1, 0);

		courseEdit = new QComboBox(this);
		formLayout->addWidget(courseEdit, 1, 1, 1, 2);

		QLabel *cusineLabelEdit = new QLabel("Cusine:", this);
		formLayout->addWidget(cusineLabelEdit, 1, 3);

		cusineEdit = new QComboBox(this);
		formLayout->addWidget(cusineEdit, 1, 4, 1, 2);

		QLabel *portionsLabelEdit = new QLabel("Portions count:", this);
		formLayout->addWidget(portionsLabelEdit, 2, 0);

		portionsEdit = new QSpinBox(this);
			portionsEdit->setMinimum(1);
		formLayout->addWidget(portionsEdit, 2, 1);

		QLabel *weightLabelEdit = new QLabel("Dish weight:", this);
		formLayout->addWidget(weightLabelEdit, 2, 2);

		weightEdit = new QDoubleSpinBox(this);
			weightEdit->setMinimum(0.1);
		formLayout->addWidget(weightEdit, 2, 3);

		QLabel *caloriesLabelEdit = new QLabel("Dish calories:", this);
		formLayout->addWidget(caloriesLabelEdit, 2, 4);

		caloriesEdit = new QDoubleSpinBox(this);
			caloriesEdit->setMinimum(0.1);
		formLayout->addWidget(caloriesEdit, 2, 5);

	mainLayout->addLayout(formLayout);

	preparationEdit = new QTextEdit(this);
	mainLayout->addWidget(preparationEdit);

	presentationEdit = new QTextEdit(this);
	mainLayout->addWidget(presentationEdit);

	remarksEdit = new QTextEdit(this);
	mainLayout->addWidget(remarksEdit);

	setLayout(mainLayout);
}
