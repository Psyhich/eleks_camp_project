#ifndef FAVORITES_MANAGER_H
#define FAVORITES_MANAGER_H

#include <QSettings>
#include <QSet>


Q_DECLARE_METATYPE(QList<unsigned int>)

// Singleton class that responds for saving all favorite recipe IDs
class FavoritesManager {
private:
	QSettings settings;
	FavoritesManager();
public:
	FavoritesManager(const FavoritesManager& copy) = delete;
	void operator=(const FavoritesManager& assign) = delete;

	static FavoritesManager& getManager();

	QList<unsigned int> getFavorites();
	void addToFavorites(unsigned int idToAdd);
	void removeFromFavorites(unsigned int idToRemove);
};

#endif // FAVORITESMANAGER_H
