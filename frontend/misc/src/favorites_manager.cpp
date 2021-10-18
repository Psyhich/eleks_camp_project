#include "favorites_manager.h"

#define FAVORITE_IDS_SETTING "favorite_ids"

FavoritesManager::FavoritesManager() : settings("Crunchers", "Cookbook") {
}

FavoritesManager& FavoritesManager::getManager(){
	static FavoritesManager manager;
	return manager;
}

void FavoritesManager::writeFavoritesArray(QSet<unsigned int> arr){
	settings.beginWriteArray(FAVORITE_IDS_SETTING, arr.count());
	int index = 0;
	for(auto id : arr){
		settings.setArrayIndex(index);
		settings.setValue("id", id);
		index++;
	}
	settings.sync();
	settings.endArray();
}

QSet<unsigned int> FavoritesManager::readFavoritesArray(){
	QSet<unsigned int> favoritesArray;
	int size = settings.beginReadArray(FAVORITE_IDS_SETTING);

	for(int i = 0; i < size; i++){
	  settings.setArrayIndex(i);
	  favoritesArray.insert(settings.value("id").toUInt());
	}
	settings.endArray();

	return favoritesArray;
}

void FavoritesManager::removeFromFavorites(unsigned int idToRemove){
  auto favorites = readFavoritesArray();

  favorites.remove(idToRemove);

  writeFavoritesArray(favorites);
}


QSet<unsigned int> FavoritesManager::getFavorites(){
	QSet<unsigned int> favorites = readFavoritesArray();
	if(favorites.count() > 0){
	  return favorites;
	}
	writeFavoritesArray({});
	return {};
}

void FavoritesManager::toggleFavorite(unsigned int idToToggle){
  QSet<unsigned int> currentIDs = getFavorites();
  if(currentIDs.contains(idToToggle)){
	currentIDs.remove(idToToggle);
  }else{
	currentIDs.insert(idToToggle);
  }
  writeFavoritesArray(currentIDs);
}
