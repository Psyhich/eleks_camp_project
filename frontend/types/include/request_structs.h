#ifndef REQUEST_STRUCTS_H
#define REQUEST_STRUCTS_H

#include <QSet>
#include <QString>
#include <QList>

namespace BaseTypes {
  struct Query {
	  QSet<unsigned int> favoriteIDs{};
	  QString searchSubtring{""};
	  QSet<QString> courses{};
	  QSet<QString> cusines{};
	  QList<QString> ingredients{};
	  bool searchExclusively{false};
  };

}


#endif // REQUEST_STRUCTS_H
