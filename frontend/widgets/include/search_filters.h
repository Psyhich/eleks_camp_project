#ifndef SEARCH_FILTERS_H
#define SEARCH_FILTERS_H

#include <QWidget>

#include "request_structs.h"
#include "search_widget.h"
#include "criteria_widget.h"

class SearchFilters : public QWidget {
	Q_OBJECT
private:
	MySearchWidget *searchBar;
	CriteriaWidget *searchCriterias;
public:
	SearchFilters(QWidget *parent = nullptr);

	BaseTypes::Query getFilters();
signals:
	void searchButtonClicked();
	void moreButtonClicked();
public slots:
	void updateValues(const BaseTypes::TagsHolder& valuesForUpdate);
};

#endif // SEARCHFILTERS_H
