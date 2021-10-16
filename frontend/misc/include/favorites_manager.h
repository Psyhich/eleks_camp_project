#ifndef FAVORITES_MANAGER_H
#define FAVORITES_MANAGER_H

#include <QSettings>
#include <QSet>

// Singleton class that responds for saving all favorite recipe IDs
class FavoritesManager {
private:
	QSettings settings;
	FavoritesManager();

	void writeFavoritesArray(QSet<unsigned int> arr);
	QSet<unsigned int> readFavoritesArray();
public:
	FavoritesManager(const FavoritesManager& copy) = delete;
	void operator=(const FavoritesManager& assign) = delete;

	static FavoritesManager& getManager();

	QSet<unsigned int> getFavorites();
	void toggleFavorite(unsigned int idToToggle);
};

#endif // FAVORITESMANAGER_H
