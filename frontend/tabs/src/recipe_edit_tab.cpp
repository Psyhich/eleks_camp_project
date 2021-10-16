#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>

#include "recipe_edit_tab.h"
#include "tab_manager.h"

using BaseTypes::Recipe;

RecipeEditTab::RecipeEditTab(TabManager *parent, QSharedPointer<Recipe> recipeToOpen) :
  AbstractTab(parent) {
	// We can get here null value, so we should check if it's OKay, if not this tab is recipe creation tab
	// TODO to make it more type strong, can create class that inherits this but named RecipeCreationTab
	openedRecipe = recipeToOpen.isNull() ?
		  QSharedPointer<Recipe>(new Recipe(0)) : recipeToOpen;

	QBoxLayout *rootLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);


	QWidget *inners = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout(inners);

	// After setting base values and starting widgets and layout creating all input widgets
	mainLayout->addLayout(createForm(), 1);

	// Ingredients panel
	ingredientsEdit = new IngredientsEditWidget(inners);
		ingredientsEdit->loadIngredients(openedRecipe->ingredients);
	mainLayout->addWidget(ingredientsEdit, 1);

	// Text pannels
	mainLayout->addLayout(createTextPannels(), 1);

	// Buttons panel
	mainLayout->addLayout(createBottomPanel());

	inners->setLayout(mainLayout);
	scrollArea->setWidget(inners);

	rootLayout->addWidget(scrollArea);
	setLayout(rootLayout);
}

// Form for editing name, course, cusine, portions, weight and calories
QLayout* RecipeEditTab::createForm() noexcept {
	QGridLayout *formLayout = new QGridLayout();

	QLabel *nameEditLabel = new QLabel("Name of recipe:");
	formLayout->addWidget(nameEditLabel, 0, 0);

	nameEdit = new QLineEdit(openedRecipe->name);
	formLayout->addWidget(nameEdit, 0, 1, 1, -1);

	QLabel *courseLabelEdit = new QLabel("Course:");
	formLayout->addWidget(courseLabelEdit, 1, 0);

	courseEdit = new QComboBox();
		formLayout->addWidget(courseEdit, 1, 1, 1, 2);
		courseEdit->addItems(openedRecipe->courses.values());
	courseEdit->setEditable(true);

	QLabel *cusineLabelEdit = new QLabel("Cusine:");
	formLayout->addWidget(cusineLabelEdit, 1, 3);

	cusineEdit = new QComboBox();
		formLayout->addWidget(cusineEdit, 1, 4, 1, 2);
		cusineEdit->addItems(openedRecipe->cusines.values());
	cusineEdit->setEditable(true);

	QLabel *portionsLabelEdit = new QLabel("Portions count:");
	formLayout->addWidget(portionsLabelEdit, 2, 0);

	// TODO ask about how we store portions
	portionsEdit = new QSpinBox();
		portionsEdit->setMinimum(1);
		portionsEdit->setMaximum(100);
	formLayout->addWidget(portionsEdit, 2, 1);

	QLabel *weightLabelEdit = new QLabel("Dish weight:");
	formLayout->addWidget(weightLabelEdit, 2, 2);

	weightEdit = new QDoubleSpinBox();
		weightEdit->setMinimum(0.1);
		weightEdit->setMaximum(100000);
		weightEdit->setValue(openedRecipe->outWeight);
	formLayout->addWidget(weightEdit, 2, 3);

	QLabel *caloriesLabelEdit = new QLabel("Dish calories:");
	formLayout->addWidget(caloriesLabelEdit, 2, 4);

	caloriesEdit = new QDoubleSpinBox();
		caloriesEdit->setMinimum(0.1);
		caloriesEdit->setMaximum(100000);
		caloriesEdit->setValue(openedRecipe->outCalories);
	formLayout->addWidget(caloriesEdit, 2, 5);

	return formLayout;
}

QLayout* RecipeEditTab::createBottomPanel() noexcept {
	// Button panel(save and delete)
	QHBoxLayout *pannelLayout = new QHBoxLayout();
	pannelLayout->setAlignment(Qt::AlignmentFlag::AlignRight);

	discardButon = new QPushButton("Discard");
	pannelLayout->addWidget(discardButon, 0);

	deleteButon = new QPushButton("Delete");
	pannelLayout->addWidget(deleteButon, 0);

	saveButon = new QPushButton("Save");
	pannelLayout->addWidget(saveButon, 0);

	QObject::connect(deleteButon, &QPushButton::clicked,
					 this, &RecipeEditTab::emitRequestDeleteRecipe);
	QObject::connect(saveButon, &QPushButton::clicked,
					 this, &RecipeEditTab::emitRequestSaveRecipe);

	return pannelLayout;
}

QLayout* RecipeEditTab::createTextPannels() noexcept{
	QVBoxLayout *panelsLayout = new QVBoxLayout();
	// Text panels
	preparationEdit = new QTextEdit(openedRecipe->recipeText);
	panelsLayout->addWidget(preparationEdit, 1);

	presentationEdit = new QTextEdit(openedRecipe->presentationText);
	panelsLayout->addWidget(presentationEdit, 1);

	remarksEdit = new QTextEdit(openedRecipe->remarks);
	panelsLayout->addWidget(remarksEdit, 1);

	return panelsLayout;
}

QSharedPointer<Recipe> RecipeEditTab::collectNewRecipe() const {
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
	emitRequestCloseTab();
}

void RecipeEditTab::emitRequestDeleteRecipe(){
	emit requestDeleteRecipe(openedRecipe);
	emitRequestCloseTab();
}

void RecipeEditTab::emitRequestCloseTab(){
  emit requestCloseTab(this);
}

void RecipeEditTab::populateInputs(const BaseTypes::TagsHolder& values) {
	courseEdit->clear();
	courseEdit->addItems(values.courses.values());
	if(openedRecipe->courses.values().count() > 0){
		courseEdit->setCurrentText(openedRecipe->courses.values()[0]);
	}

	cusineEdit->clear();
	cusineEdit->addItems(values.cusines.values());
	if(openedRecipe->cusines.values().count() > 0){
		cusineEdit->setCurrentText(openedRecipe->cusines.values()[0]);
	}

	ingredientsEdit->updateIngredientsSet(values.ingredients);
	ingredientsEdit->updateUnitsSet(values.units);
}

void RecipeEditTab::reopenRecipe(QSharedPointer<BaseTypes::Recipe> recipeToReopen) {
  openedRecipe = recipeToReopen;

  nameEdit->setText(openedRecipe->name);

  courseEdit->setCurrentText(openedRecipe->courses.values()[0]);
  cusineEdit->setCurrentText(openedRecipe->cusines.values()[0]);

  caloriesEdit->setValue(openedRecipe->outCalories);
  weightEdit->setValue(openedRecipe->outWeight);
  portionsEdit->setValue(openedRecipe->outPortions);

  ingredientsEdit->loadIngredients(openedRecipe->ingredients);

  preparationEdit->setText(openedRecipe->recipeText);

  presentationEdit->setText(openedRecipe->presentationText);
  presentationEdit->setVisible(!openedRecipe->presentationText.isEmpty());

  remarksEdit->setText(openedRecipe->remarks);
  remarksEdit->setVisible(!openedRecipe->remarks.isEmpty());
}

// AbstractTab interface
void RecipeEditTab::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) {
  reopenRecipe(recipeToOpen);
}

void RecipeEditTab::closeRecipe(QSharedPointer<BaseTypes::Recipe>) {
  parentWidget()->closeAbstractTab(this);
}

void RecipeEditTab::updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) {
  reopenRecipe(recipeToUpdate);
}

QVector<QSharedPointer<BaseTypes::Recipe>> RecipeEditTab::getRecipes() const {
  return {openedRecipe};
}
