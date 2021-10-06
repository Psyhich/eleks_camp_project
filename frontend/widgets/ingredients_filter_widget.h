#ifndef INGREDIENTS_FILTER_WIDGET_H
#define INGREDIENTS_FILTER_WIDGET_H

#include <QScrollArea>
#include <QSet>
#include <QComboBox>
#include <QPushButton>
#include <QSharedPointer>

class IngredientRowFilter : public QWidget {
	Q_OBJECT
private:
	QComboBox *ingredientFilter;
	void emitDeletePressed();
public:
	IngredientRowFilter(QSharedPointer<QSet<QString>> availableVariants, QWidget *parrent=nullptr);
	QString getFilter();
	void updateVariants(QSharedPointer<QSet<QString>> newVariants);
signals:
	void deletePressed(IngredientRowFilter *current);
};

class IngredientsFilterWidget : public QScrollArea {
	Q_OBJECT
private:

	QPushButton* addButton;
	QVector<IngredientRowFilter *> rows;
	QSharedPointer<QSet<QString>> filterVariants;

private slots:
	// This object will bind itself with RowFilters and when their delete button is clicked,
	// they will be deleted
	void deleteFilter(IngredientRowFilter *filterToDelete);
	void addRow();
public slots:
	void updateFilters(QSharedPointer<QSet<QString>> newVariants);

public:
	IngredientsFilterWidget(QSharedPointer<QSet<QString>> variants, QWidget *parrent = nullptr);

	QSet<QString> getIngredientFilter();
};

#endif // INGREDIENTS_FILTER_WIDGET_H
