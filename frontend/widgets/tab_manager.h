#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QTabWidget>
#include <QWidget>
#include <QSharedPointer>
#include "types/requests.h"
#include "types/responses.h"

class TabManager : public QTabWidget {
private:

	//QMap<unsigned int, QSharedPointer<BaseTypes::Recipe>> openedCache; // TODO implement recipe cache that will update all widgets that contain opened recipes
public:
	TabManager(QWidget *parrent=nullptr);
signals:

public slots:
	void openRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void editRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);
	void toggleFavoriteRecipe(QSharedPointer<BaseTypes::Recipe> recipeToOpen);

};

#endif // TABMANAGER_H
