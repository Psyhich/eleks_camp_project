#include "search_widget.h"
#include <QHBoxLayout>
#include <QDebug>

MySearchWidget::MySearchWidget(QWidget *parent) : QWidget(parent) {
	QHBoxLayout* hLayout = new QHBoxLayout(this);

	moreButton = new QToolButton(this);
	moreButton->setText(">");
	moreButton->setCheckable(true);
	QObject::connect(moreButton, &QToolButton::clicked, this, &MySearchWidget::moreButtonClicked);

	searchLine = new QLineEdit(this);

	searchButton = new QPushButton("Search", this);
	QObject::connect(searchButton, &QPushButton::toggled, this, &MySearchWidget::emitClickSearchButton);

	hLayout->addWidget(moreButton);
	hLayout->addWidget(searchLine, 1);
	hLayout->addWidget(searchButton);

	setLayout(hLayout);
}

void MySearchWidget::emitClickSearchButton(){
  emit searchButtonClicked(searchLine->text());
}
