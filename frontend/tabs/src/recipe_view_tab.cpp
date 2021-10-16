#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QScrollArea>

#include "recipe_view_tab.h"
#include "tab_manager.h"

// This constructor creates base layout of all widget and insert values of setted recipe
// After this we can call updateRecipe to update only value
RecipeViewTab::RecipeViewTab(QSharedPointer<BaseTypes::Recipe> recipeToSet,
							 TabManager *parent) : AbstractTab(parent){

	QBoxLayout *fullLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setWidgetResizable(true);

	curretRecipe = recipeToSet;
	QWidget *inners = new QWidget(this);

	QVBoxLayout *mainLayout = new QVBoxLayout(inners);
	mainLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
	mainLayout->setContentsMargins(2,5,2,5);

	// Recipe name
	nameLabel = new QLabel(curretRecipe->name);
	nameLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignHCenter);

	// Recipe tags
	mainLayout->addWidget(createTagsWidget());

	// Recipe basic values(calories, weight, portions)
	mainLayout->addLayout(createBaseValues());

	// Ingredients
	mainLayout->addLayout(createIngredientsTable());

	// Recipe texts
	mainLayout->addLayout(createRecipeTexts());

	inners->setLayout(mainLayout);
	scrollArea->setWidget(inners);

	fullLayout->addWidget(scrollArea);
	setLayout(fullLayout);
}


QWidget *RecipeViewTab::createTagsWidget(){
	QScrollArea *tags = new QScrollArea();

	tags->setWidgetResizable(true);
	tags->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
	tags->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	tags->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	tagsWidget = new QWidget(tags);
	tagsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	QHBoxLayout *tagsLayout = new QHBoxLayout(tagsWidget);

	tagsLayout->setContentsMargins(2, 5, 2, 5);

	for(auto course : curretRecipe->courses){
	  QLabel *courseLabel = new QLabel(course);
	  tagsLayout->addWidget(courseLabel);
	}
	for(auto cusine : curretRecipe->cusines){
	  QLabel *cusineLabel = new QLabel(cusine);
	  tagsLayout->addWidget(cusineLabel);
	}

	tagsWidget->setLayout(tagsLayout);
	tags->setWidget(tagsWidget);

	return tags;
}

QLayout *RecipeViewTab::createBaseValues(){
	QHBoxLayout *baseValsLayout = new QHBoxLayout();

	QLabel* caloriesLabel = new QLabel("Calories:");
	baseValsLayout->addWidget(caloriesLabel);
	recipeCalories = new QLabel(QString::number(curretRecipe->outCalories, 'f', 2));
	baseValsLayout->addWidget(recipeCalories);

	QLabel *weightLabel = new QLabel("Weight:");
	baseValsLayout->addWidget(weightLabel);
	QString stringValue = QString::number(curretRecipe->outWeight, 'f', 2);

	recipeWeight = new QLabel(stringValue);
	baseValsLayout->addWidget(recipeWeight);

	QLabel *portionsLabel = new QLabel("Portions:");
	baseValsLayout->addWidget(portionsLabel);
	recipePortions = new QSpinBox();
	recipePortions->setMinimum(1);
	QObject::connect(recipePortions, SIGNAL(valueChanged(int)), this, SLOT(recalculateValues()));
	baseValsLayout->addWidget(recipePortions);

	return baseValsLayout;
}

QLayout *RecipeViewTab::createIngredientsTable(){
	QVBoxLayout *outLayout = new QVBoxLayout();
	QLabel *ingredientsLabel = new QLabel("Ingredients:", this);
	outLayout->addWidget(ingredientsLabel);

	ingredientsWidget = new QTableWidget(curretRecipe->ingredients.count(), 3);
	ingredientsWidget->setEditTriggers(QTableView::EditTrigger::NoEditTriggers);

	//Setting size parameters
	ingredientsWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	ingredientsWidget->horizontalHeader()->setHidden(true);

	int row = 0;
	for(auto pair = curretRecipe->ingredients.begin(); row < curretRecipe->ingredients.count(); row++, pair++){
	  QTableWidgetItem *ingredientName = new QTableWidgetItem(pair.key());
	  QTableWidgetItem *ingredientCount = new QTableWidgetItem(QString::number(pair.value().quantity, 'f', 2));
	  QTableWidgetItem *ingredientUnit = new QTableWidgetItem(pair.value().unit);
	  ingredientsWidget->setItem(row, 0, ingredientName);
	  ingredientsWidget->setItem(row, 1, ingredientCount);
	  ingredientsWidget->setItem(row, 2, ingredientUnit);
	}
	outLayout->addWidget(ingredientsWidget);

	return outLayout;
}

QLayout *RecipeViewTab::createRecipeTexts(){
	QVBoxLayout *outLayout = new QVBoxLayout();

	// Preparation
	recipePreparationText = new QTextBrowser();
	recipePreparationText->setText(curretRecipe->recipeText);
	outLayout->addWidget(recipePreparationText);

	// Presentations
	recipePresentationText = new QTextBrowser();
	if(curretRecipe->presentationText.isEmpty()) {
		recipePresentationText->setHidden(true);
	} else {
		recipePresentationText->setText(curretRecipe->presentationText);
	}
	outLayout->addWidget(recipePresentationText);

	// Remarks
	recipeRemarksText = new QTextBrowser();
	if(curretRecipe->remarks.isEmpty()) {
		recipeRemarksText->setHidden(true);
	} else {
		recipeRemarksText->setText(curretRecipe->remarks);
	}
	outLayout->addWidget(recipeRemarksText);

	return outLayout;
}

void RecipeViewTab::recalculateValues(){
	// We should recalculate weight, calories and recipe ingredients
	const double conversionRate = recipePortions->value() / curretRecipe->outPortions;

	recipeCalories->setText(
		  QString::number(curretRecipe->outCalories * conversionRate, 'f', 2));
	recipeWeight->setText(
		  QString::number(curretRecipe->outWeight * conversionRate, 'f', 2));

	double baseValue;
	for(int row = 0; row < ingredientsWidget->rowCount(); row++){
	  // This should affect only column with index 1
	  baseValue = curretRecipe->ingredients.find(
			ingredientsWidget->item(row, 0)->text())
			.value().quantity;

	  ingredientsWidget->item(row, 1)->
		  setText(QString::number(baseValue * conversionRate, 'f', 2));
	}

}

RecipeViewTab::~RecipeViewTab(){
  emit recipeClosed(*curretRecipe->getID());
}

// AbstractTab implementation
void RecipeViewTab::openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) {
  updateRecipe(recipeToOpen);

}
void RecipeViewTab::closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToClose) {
  parentWidget()->closeAbstractTab(this);
}
void RecipeViewTab::updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) {
	curretRecipe = recipeToUpdate;

	nameLabel->setText(curretRecipe->name);

	// Tags
	for(auto child : tagsWidget->children()){
		child->deleteLater();
	}
	for(auto course : curretRecipe->courses){
	  QLabel *courseLabel = new QLabel(course, tagsWidget);
	  tagsWidget->layout()->addWidget(courseLabel);
	}
	for(auto cusine : curretRecipe->cusines){
	  QLabel *cusineLabel = new QLabel(cusine, tagsWidget);
	  tagsWidget->layout()->addWidget(cusineLabel);
	}

	// Recipe and calories will be set after recalculation that will be called after all values set
	ingredientsWidget->clear();
	int row = 0;
	for(auto pair = curretRecipe->ingredients.begin(); row < curretRecipe->ingredients.count(); row++, pair++){
	  QTableWidgetItem *ingredientName = new QTableWidgetItem(pair.key());
	  QTableWidgetItem *ingredientCount = new QTableWidgetItem(QString::number(pair.value().quantity, 'f', 2));
	  QTableWidgetItem *ingredientUnit = new QTableWidgetItem(pair.value().unit);
	  ingredientsWidget->setItem(row, 0, ingredientName);
	  ingredientsWidget->setItem(row, 1, ingredientCount);
	  ingredientsWidget->setItem(row, 2, ingredientUnit);
	}

	// Texts
	recipePreparationText->setText(curretRecipe->recipeText);

	recipePresentationText->setText(curretRecipe->presentationText);
	recipePresentationText->setVisible(!curretRecipe->presentationText.isEmpty());

	recipeRemarksText->setText(curretRecipe->remarks);
	recipeRemarksText->setVisible(!curretRecipe->remarks.isEmpty());

	recalculateValues();
}
QVector<QSharedPointer<BaseTypes::Recipe>> RecipeViewTab::getRecipes() const {
  return {curretRecipe};
}
