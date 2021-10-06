#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>

#include "recipe_view_tab.h"

// This constructor creates base layout of all widget and insert values of setted recipe
// After this we can call updateRecipe to update only value
RecipeViewTab::RecipeViewTab(QSharedPointer<BaseTypes::Recipe> recipeToSet, QWidget *parent) : QScrollArea(parent) {
	setWidgetResizable(true);

	curretRecipe = recipeToSet;
	QWidget *inners = new QWidget(this);
	inners->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	QVBoxLayout *mainLayout = new QVBoxLayout(inners);
	mainLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
	mainLayout->setContentsMargins(2,5,2,5);

	// Recipe name
	nameLabel = new QLabel(curretRecipe->name);
	nameLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignHCenter);

	// Recipe tags
	QScrollArea *tags = new QScrollArea(inners);
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

	mainLayout->addWidget(tags);

	// Recipe basic values(calories, weight, portions)
	QWidget* baseValsHolder = new QWidget(inners);
		QHBoxLayout *baseValsLayout = new QHBoxLayout(baseValsHolder);

		QLabel* caloriesLabel = new QLabel("Calories:", baseValsHolder);
		baseValsLayout->addWidget(caloriesLabel);
		recipeCalories = new QLabel(QString::number(curretRecipe->outCalories, 'f', 2), baseValsHolder);
		baseValsLayout->addWidget(recipeCalories);

		QLabel *weightLabel = new QLabel("Weight:", baseValsHolder);
		baseValsLayout->addWidget(weightLabel);
		QString stringValue = QString::number(curretRecipe->outWeight, 'f', 2);

		recipeWeight = new QLabel(stringValue, baseValsHolder);
		baseValsLayout->addWidget(recipeWeight);

		QLabel *portionsLabel = new QLabel("Portions:", baseValsHolder);
		baseValsLayout->addWidget(portionsLabel);
		recipePortions = new QSpinBox(baseValsHolder);
		recipePortions->setMinimum(1);
		QObject::connect(recipePortions, SIGNAL(valueChanged(int)), this, SLOT(recalculateValues()));
		baseValsLayout->addWidget(recipePortions);

		baseValsHolder->setLayout(baseValsLayout);
	mainLayout->addWidget(baseValsHolder);

	// Ingredients
	QLabel *ingredientsLabel = new QLabel("Ingredients:", this);
	mainLayout->addWidget(ingredientsLabel);

	ingredientsWidget = new QTableWidget(curretRecipe->ingredients.count(), 3, inners);
	ingredientsWidget->setEditTriggers(QTableView::EditTrigger::NoEditTriggers);

	//Setting size parameters
	ingredientsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	ingredientsWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ingredientsWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
	mainLayout->addWidget(ingredientsWidget);




	// Recipe texts
	recipePreparationText = new QTextBrowser(inners);
	recipePreparationText->setText(curretRecipe->recipeText);
	mainLayout->addWidget(recipePreparationText);

	recipePresentationText = new QTextBrowser(inners);
		if(curretRecipe->presentationText.length() == 0){
			recipePresentationText->setHidden(true);
		}else{
			recipePresentationText->setText(curretRecipe->presentationText);
		}
	mainLayout->addWidget(recipePresentationText);

	inners->setLayout(mainLayout);
	setWidget(inners);
}

void RecipeViewTab::updateRecipe() {
  // This function just takes all value from currentRecipe and sets them to this tab
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

	recalculateValues();
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
