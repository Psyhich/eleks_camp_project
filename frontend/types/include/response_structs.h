#ifndef RESPONSE_STRUCTS_H
#define RESPONSE_STRUCTS_H

#include <QSet>
#include <QString>
#include <QSharedPointer>

namespace BaseTypes {

	struct TagsHolder {
		QSet<QString> courses;
		QSet<QString> cusines;
		QSet<QString> ingredients;
		QSet<QString> units;
	};
}


#endif // RESPONSE_STRUCTS_H
