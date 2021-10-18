#ifndef ABSTRACT_TAB_H
#define ABSTRACT_TAB_H

#include <QWidget>

#include "front_recipe.h"

class TabManager;

// Class that represents every tab that can be in tab manager
class AbstractTab : public QWidget {
	Q_OBJECT
protected:

public:
	AbstractTab(TabManager *parrentManager);

	TabManager* parentWidget() const;
public slots:
	virtual void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) = 0;
	virtual void closeRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen) = 0;
	virtual void updateRecipe(QSharedPointer<BaseTypes::Recipe> recipeToUpdate) = 0; // Slot to notify tab that recipe has been updated
	virtual QVector<QSharedPointer<BaseTypes::Recipe>> getRecipes() const = 0 ;

};

#endif // ABSTRACTTAB_H
