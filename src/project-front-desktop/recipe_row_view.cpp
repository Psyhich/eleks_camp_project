#include "recipe_row_view.h"
#include <QHBoxLayout>
#include <QLabel>

RecipeRowView::RecipeRowView(QSharedPointer<BaseTypes::Recipe> recipe, QWidget *parent) : QWidget(parent) {
  // Should create name of recipe, its first 3 tags and align items
  QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
  QLabel *nameLabel = new QLabel();
  nameLabel->setText(recipe->getName());
  QLabel *tagsLabel = new QLabel();
  tagsLabel->setText(recipe->getTags().join(" "));

  horizontalLayout->addWidget(nameLabel);
  horizontalLayout->addWidget(tagsLabel);

  setLayout(horizontalLayout);
}
