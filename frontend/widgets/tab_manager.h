#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QTabWidget>
#include <QWidget>
#include <QSharedPointer>
#include "types/requests.h"
#include "types/responses.h"

class TabManager : public QTabWidget
{
  public:
	TabManager(QWidget *parrent=nullptr);

  public slots:
	void requestRecipes(BaseTypes::Requests::SearchQuery request);

	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void toggleFavoriteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);

};

#endif // TABMANAGER_H
