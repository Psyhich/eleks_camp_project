#ifndef CRITERIA_WIDGET_H
#define CRITERIA_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>

#include "types/requests.h"
#include "ingredients_filter_widget.h"

class CriteriaWidget : public QWidget {
	Q_OBJECT
private:
	QComboBox *courseSetter;
	QComboBox *cusineSetter;
	QCheckBox *searchWithIngredients;
	QCheckBox *searchExact;

	IngredientsFilterWidget* ingredientFilters;
public:
	struct NotFullRequest{
		QString course{""};
		QString cusine{""};
		QSet<QString> ingredients{};
		bool serchExact{false};
	};

	CriteriaWidget(QWidget *parent = nullptr);

	NotFullRequest getNotFullRequest();

signals:

public slots:
	void updateTags(BaseTypes::Responses::TagsResponse tagsToUpdate);
};

#endif // CRITERIA_WIDGET_H
