#ifndef SEARCH_FILTERS_H
#define SEARCH_FILTERS_H

#include <QWidget>

#include "types/requests.h"
#include "search_widget.h"
#include "criteria_widget.h"

class SearchFilters : public QWidget {
	Q_OBJECT
private:
	MySearchWidget *searchBar;
	CriteriaWidget *searchCriterias;
public:
	SearchFilters(QWidget *parent = nullptr);

	QSharedPointer<BaseTypes::Requests::SearchQuery> getFilters();
signals:
	void searchButtonClicked();
public slots:
	void fetchUpdates();
};

#endif // SEARCHFILTERS_H
