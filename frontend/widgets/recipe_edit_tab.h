#ifndef RECIPE_EDIT_TAB_H
#define RECIPE_EDIT_TAB_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDoubleSpinBox>

#include "types/recipe.h"

class RecipeEditTab : public QWidget {
	Q_OBJECT
private:
	QLineEdit *nameEdit;

	QComboBox *courseEdit;
	QComboBox *cusineEdit;

	QDoubleSpinBox *caloriesEdit;
	QDoubleSpinBox *weightEdit;
	QSpinBox *portionsEdit;

	QTextEdit *preparationEdit;
	QTextEdit *presentationEdit;
	QTextEdit *remarksEdit;

public:
	RecipeEditTab(QWidget *parent = nullptr);

signals:

};

#endif // RECIPE_EDIT_TAB_H
