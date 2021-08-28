#include "initializer.h"

namespace server {
namespace initializer {

Initializer::Initializer(dbAPI::IDataBase& db) : db{db} {}

std::optional<DataContainers> Initializer::getInitData() const {
    return db.getInitData();
}

} // initializer   
} // server