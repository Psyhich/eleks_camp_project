#include <QVBoxLayout>
#include <QSet>

#include "search_filters.h"
#include "favorites_manager.h"

SearchFilters::SearchFilters(QWidget *parent) : QWidget(parent) {
	QVBoxLayout* vLayout = new QVBoxLayout(this);

	searchBar = new MySearchWidget(this);
	vLayout->addWidget(searchBar);

	searchCriterias = new CriteriaWidget(this);
	searchCriterias->setHidden(true);
	vLayout->addWidget(searchCriterias);

	connect(searchBar, &MySearchWidget::moreButtonClicked, searchCriterias, &QWidget::setVisible);
	//connect(searchBar, &MySearchWidget::moreButtonClicked, this, &SearchFilters::fetchUpdates);
	connect(searchBar, &MySearchWidget::searchButtonClicked, this, &SearchFilters::searchButtonClicked);


	setLayout(vLayout);
}

BaseTypes::Query SearchFilters::getFilters(){
	BaseTypes::Query criterias;
	bool shouldUseFavorites = searchCriterias->partlyPopulateQuery(criterias);
	QString searchSubstring = searchBar->getSearchSubstring();
	QSet<unsigned int> favoriteIDs;
	if(shouldUseFavorites){
		for(unsigned int id : FavoritesManager::getManager().getFavorites()){
		  favoriteIDs.insert(id);
		}
	}

	return criterias;
}

void SearchFilters::updateValues(const BaseTypes::TagsHolder& valuesForUpdate){
	searchCriterias->updateTags(valuesForUpdate);
}
