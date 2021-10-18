#ifndef INGREDIENTS_FILTER_WIDGET_H
#define INGREDIENTS_FILTER_WIDGET_H

#include "row_holder.h"

#include <QSet>
#include <QComboBox>
#include <QPushButton>
#include <QSharedPointer>

class IngredientRowFilter : public RowDisplay {
	Q_OBJECT
private:
	QComboBox *ingredientFilter;
public:
	void updateVariants(const QSet<QString>& newVariants);
	QVector<QString> getStrings() override;
	IngredientRowFilter(const QSet<QString>& variants, QWidget *parrent=nullptr);
signals:
};

class IngredientsFilterWidget : public RowHolder {
Q_OBJECT
private:
	QSet<QString> filterVariants;
public slots:
	void updateFilters(const QSet<QString>& newVariants);

public:
	IngredientsFilterWidget(const QSet<QString>& variants, QWidget *parrent = nullptr);

	RowDisplay *createRow() override;

	QSet<QString> getIngredientFilter();
};
#endif // INGREDIENTS_FILTER_WIDGET_H
