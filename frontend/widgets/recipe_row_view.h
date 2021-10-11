#ifndef RECIPE_ROW_VIEW_H
#define RECIPE_ROW_VIEW_H

#include <QSharedPointer>
#include <QFrame>

#include "types/responses.h"

// Class that represents single row view for one recipe
class RecipeRowView : public QFrame {
  Q_OBJECT
	QSharedPointer<BaseTypes::Recipe> recipe;
private:
  inline void emitFavoriteClicked() { emit favoriteClicked(*recipe->getID()); }
  inline void emitEditClicked() { emit editClicked(recipe); }
  inline void emitOpenClicked() { emit openClicked(recipe); }

public:

  RecipeRowView(QSharedPointer<BaseTypes::Recipe> recipe, QWidget *parent);
  inline unsigned int getId() const { return *recipe->getID(); }
  signals:
	void favoriteClicked(unsigned int recipeID);
	void editClicked(QSharedPointer<BaseTypes::Recipe> recipe);
	void openClicked(QSharedPointer<BaseTypes::Recipe> recipe);
};

#endif // RECIPE_ROW_VIEW_H
