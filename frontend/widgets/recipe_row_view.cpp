#include "recipe_row_view.h"
#include <QHBoxLayout>
#include <QLabel>

RecipeRowView::RecipeRowView(QSharedPointer<BaseTypes::Recipe> recipe, QWidget *parent) : QFrame(parent) {
	this->recipe = recipe;
	// Should create name of recipe, and add cusine + course
	QGridLayout *gridLayout = new QGridLayout(this);
	gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
	QLabel *nameLabel = new QLabel(recipe->name, this);

	QLabel *coursesLabel = new QLabel(recipe->courses.values().join(" "), this);
	QLabel *cusinesLabel = new QLabel(recipe->cusines.values().join(" "), this);

	//Creating interactive buttons and connecting their events to out own signals
	QToolButton* favoriteButton = new QToolButton(this);
	favoriteButton->setIcon(QIcon(":/icons/bookmarks.svg"));
	QObject::connect(favoriteButton, &QToolButton::clicked, this,  &RecipeRowView::emitFavoriteClicked);

	QToolButton* openButton = new QToolButton(this);
	openButton->setText("O");
	QObject::connect(openButton, &QToolButton::clicked, this, &RecipeRowView::emitOpenClicked);

	QToolButton* editButton = new QToolButton(this);
	editButton->setText("E");
	QObject::connect(editButton, &QToolButton::clicked, this, &RecipeRowView::emitEditClicked);

	gridLayout->addWidget(nameLabel, 0, 0);
	gridLayout->addWidget(coursesLabel, 0, 1);
	gridLayout->addWidget(cusinesLabel, 1, 1);

	gridLayout->addWidget(favoriteButton, 0, 2);
	gridLayout->addWidget(openButton, 0, 3);
	gridLayout->addWidget(editButton, 1, 3);

	setLayout(gridLayout);
}
