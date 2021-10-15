#ifndef CRITERIA_WIDGET_H
#define CRITERIA_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>

#include "response_structs.h"
#include "request_structs.h"
#include "ingredients_filter_widget.h"

class CriteriaWidget : public QWidget {
	Q_OBJECT
private:
	QComboBox *courseSetter;
	QComboBox *cusineSetter;
	QCheckBox *searchWithIngredients;
	QCheckBox *searchExact;
	QCheckBox *searchByFavorites;

	IngredientsFilterWidget* ingredientFilters;
public:
	struct NotFullRequest{
		QString course{""};
		QString cusine{""};
		QSet<QString> ingredients{};
		bool serchExact{false};
		bool searchByFavorites;
	};

	CriteriaWidget(QWidget *parent = nullptr);

	bool partlyPopulateQuery(BaseTypes::Query &queryToPopulate);

signals:

public slots:
	void updateTags(const BaseTypes::TagsHolder& tagsToUpdate);
};

#endif // CRITERIA_WIDGET_H
