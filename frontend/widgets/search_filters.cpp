#include <QVBoxLayout>
#include <QSet>

#include "search_filters.h"
#include "types/favorites_manager.h"
#include "connections/connection_manager.h"

SearchFilters::SearchFilters(QWidget *parent) : QWidget(parent) {
	QVBoxLayout* vLayout = new QVBoxLayout(this);

	searchBar = new MySearchWidget(this);
	vLayout->addWidget(searchBar);

	searchCriterias = new CriteriaWidget(this);
	searchCriterias->setHidden(true);
	vLayout->addWidget(searchCriterias);

	connect(searchBar, &MySearchWidget::moreButtonClicked, searchCriterias, &QWidget::setVisible);
	connect(searchBar, &MySearchWidget::moreButtonClicked, this, &SearchFilters::fetchUpdates);
	connect(searchBar, &MySearchWidget::searchButtonClicked, this, &SearchFilters::searchButtonClicked);


	setLayout(vLayout);
}

QSharedPointer<BaseTypes::Requests::SearchQuery> SearchFilters::getFilters(){
	CriteriaWidget::NotFullRequest notFull = searchCriterias->getNotFullRequest();
	QString searchSubstring = searchBar->getSearchSubstring();
	QSet<unsigned int> favoriteIDs;
	if(notFull.searchByFavorites){
		for(unsigned int id : FavoritesManager::getManager().getFavorites()){
		  favoriteIDs.insert(id);
		}
	}

	return QSharedPointer<BaseTypes::Requests::SearchQuery>(
		  new BaseTypes::Requests::SearchQuery(
			favoriteIDs,
			searchSubstring,
			{notFull.course},
			{notFull.cusine},
			notFull.ingredients.values(),
			notFull.serchExact
			));
}

void SearchFilters::fetchUpdates(){
	auto response = Connections::ConnectionManager::getManager().getTags();
	searchCriterias->updateTags(response);

}
