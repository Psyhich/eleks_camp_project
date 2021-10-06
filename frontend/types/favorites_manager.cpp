#include "favorites_manager.h"

#define FAVORITE_IDS_SETTING "favorite_ids"

FavoritesManager::FavoritesManager() : settings("Crunchers", "Cookbook") {
}

FavoritesManager& FavoritesManager::getManager(){
	static FavoritesManager manager;
	return manager;
}

QList<unsigned int> FavoritesManager::getFavorites(){
	QVariant readSettings = settings.value(FAVORITE_IDS_SETTING);
	if(!readSettings.isNull()){
	  return readSettings.value<QList<unsigned int>>();
	}
	settings.setValue(FAVORITE_IDS_SETTING, QVariant::fromValue(QList<unsigned int>()));
	return {};
}

void FavoritesManager::addToFavorites(unsigned int idToAdd){
	QList<unsigned int> currentIDs = getFavorites();
	currentIDs.push_back(idToAdd);
	settings.setValue(FAVORITE_IDS_SETTING, QVariant::fromValue(currentIDs));
}
void FavoritesManager::removeFromFavorites(unsigned int idToRemove){
	QList<unsigned int> currentIDs = getFavorites();
	currentIDs.removeAll(idToRemove);
	settings.setValue(FAVORITE_IDS_SETTING, QVariant::fromValue(currentIDs));
}
