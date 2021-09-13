#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include "recipes_list_view.h"

class SearchWidget : public QWidget
{
	RecipesListView recipesList;

	Q_OBJECT
  public:
	explicit SearchWidget(QWidget *parent = nullptr);

  signals:

};

#endif // SEARCHWIDGET_H
