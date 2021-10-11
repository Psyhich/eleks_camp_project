#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include "recipe_edit_tab.h"

using BaseTypes::Recipe;

RecipeEditTab::RecipeEditTab(QSharedPointer<BaseTypes::Recipe> recipeToOpen,
							 QWidget *parent) : QScrollArea(parent) {
	// We can get here null value, so we should check if it's OKay, if not this tab is recipe creation tab
	// TODO to make it more type strong, can create class that inherits this but named RecipeCreationTab
	openedRecipe = recipeToOpen.isNull() ? QSharedPointer<BaseTypes::Recipe>(new Recipe(0)) : recipeToOpen;

	setWidgetResizable(true);
	QWidget *inners = new QWidget(this);
	QVBoxLayout *mainLayout = new QVBoxLayout(inners);

	// After setting base values and starting widgets and layout creating all input widgets

	// Form for editing name, course, cusine, portions, weight and calories
	QGridLayout *formLayout = new QGridLayout();

		QLabel *nameEditLabel = new QLabel("Name of recipe:", inners);
		formLayout->addWidget(nameEditLabel, 0, 0);

		nameEdit = new QLineEdit(openedRecipe->name, inners);
		formLayout->addWidget(nameEdit, 0, 1, 1, -1);

		QLabel *courseLabelEdit = new QLabel("Course:", inners);
		formLayout->addWidget(courseLabelEdit, 1, 0);

		courseEdit = new QComboBox(inners);
			formLayout->addWidget(courseEdit, 1, 1, 1, 2);
			courseEdit->addItems(openedRecipe->courses.values());
		courseEdit->setEditable(true);

		QLabel *cusineLabelEdit = new QLabel("Cusine:", inners);
		formLayout->addWidget(cusineLabelEdit, 1, 3);

		cusineEdit = new QComboBox(inners);
			formLayout->addWidget(cusineEdit, 1, 4, 1, 2);
			cusineEdit->addItems(openedRecipe->cusines.values());
		cusineEdit->setEditable(true);

		QLabel *portionsLabelEdit = new QLabel("Portions count:", inners);
		formLayout->addWidget(portionsLabelEdit, 2, 0);

		// TODO ask about how we store portions
		portionsEdit = new QSpinBox(inners);
			portionsEdit->setMinimum(1);
			portionsEdit->setMaximum(100);
		formLayout->addWidget(portionsEdit, 2, 1);

		QLabel *weightLabelEdit = new QLabel("Dish weight:", inners);
		formLayout->addWidget(weightLabelEdit, 2, 2);

		weightEdit = new QDoubleSpinBox(inners);
			weightEdit->setMinimum(0.1);
			weightEdit->setMaximum(100000);
			weightEdit->setValue(openedRecipe->outWeight);
		formLayout->addWidget(weightEdit, 2, 3);

		QLabel *caloriesLabelEdit = new QLabel("Dish calories:", inners);
		formLayout->addWidget(caloriesLabelEdit, 2, 4);

		caloriesEdit = new QDoubleSpinBox(inners);
			caloriesEdit->setMinimum(0.1);
			caloriesEdit->setMaximum(100000);
			caloriesEdit->setValue(openedRecipe->outCalories);
		formLayout->addWidget(caloriesEdit, 2, 5);

	mainLayout->addLayout(formLayout);

	// Ingredients panel
	ingredientsEdit = new IngredientsEditWidget(inners);
		ingredientsEdit->loadIngredients(openedRecipe->ingredients);
	mainLayout->addWidget(ingredientsEdit);

	// Text panels
	preparationEdit = new QTextEdit(openedRecipe->recipeText, inners);
	mainLayout->addWidget(preparationEdit);

	presentationEdit = new QTextEdit(openedRecipe->presentationText, inners);
	mainLayout->addWidget(presentationEdit);

	remarksEdit = new QTextEdit(openedRecipe->remarks, inners);
	mainLayout->addWidget(remarksEdit);

	// Button panel(save and delete)
	QHBoxLayout *pannelLayout = new QHBoxLayout();
	pannelLayout->setAlignment(Qt::AlignmentFlag::AlignRight);

		discardButon = new QPushButton("Discard", inners);
		pannelLayout->addWidget(discardButon, 0);

		deleteButon = new QPushButton("Delete", inners);
		pannelLayout->addWidget(deleteButon, 0);

		saveButon = new QPushButton("Save", inners);
		pannelLayout->addWidget(saveButon, 0);
	mainLayout->addLayout(pannelLayout);

	QObject::connect(deleteButon, &QPushButton::clicked, this, &RecipeEditTab::emitRequestDeleteRecipe);
	QObject::connect(saveButon, &QPushButton::clicked, this, &RecipeEditTab::emitRequestSaveRecipe);


	inners->setLayout(mainLayout);
	setWidget(inners);
}

QSharedPointer<Recipe> RecipeEditTab::collectNewRecipe() {
	if(nameEdit->text().isEmpty()){
		return nullptr;
	}

	QSharedPointer<Recipe> newRecipe = QSharedPointer<Recipe>(new Recipe(*openedRecipe->getID()));
	newRecipe->name = nameEdit->text();

	newRecipe->courses.insert(courseEdit->currentText());
	newRecipe->cusines.insert(cusineEdit->currentText());

	newRecipe->recipeText = preparationEdit->toPlainText();
	newRecipe->presentationText = presentationEdit->toPlainText();
	newRecipe->remarks = remarksEdit->toPlainText();

	newRecipe->outCalories = caloriesEdit->value();
	newRecipe->outWeight = weightEdit->value();
	newRecipe->outPortions = portionsEdit->value();

	newRecipe->ingredients = ingredientsEdit->getIngredients();

	return newRecipe;
}

void RecipeEditTab::emitRequestSaveRecipe(){
	if(auto recipe = collectNewRecipe()){
		emit requestSaveRecipe(recipe);
	}
}

void RecipeEditTab::emitRequestDeleteRecipe(){
	emit requestDeleteRecipe(openedRecipe);
}

// TODO maybe think about not passing full Request values
void RecipeEditTab::populateInputs(BaseTypes::Responses::TagsResponse values) {
	courseEdit->clear();
	courseEdit->addItems(values.getCourses()->values());
	if(openedRecipe->courses.values().count() > 0){
		courseEdit->setCurrentText(openedRecipe->courses.values()[0]);
	}

	cusineEdit->clear();
	cusineEdit->addItems(values.getCusines()->values());
	if(openedRecipe->cusines.values().count() > 0){
		cusineEdit->setCurrentText(openedRecipe->cusines.values()[0]);
	}

	ingredientsEdit->updateIngredientsSet(*values.getIngredients());
	ingredientsEdit->updateUnitsSet(*values.getUnits());
}
