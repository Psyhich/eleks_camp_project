#ifndef INITIALIZER
#define INITIALIZER

#include <optional>

#include "database_api.h"
#include "data_containers.h"

namespace server {
namespace initializer {

class Initializer {
    dbAPI::IDatabase& db;
public:
    Initializer(dbAPI::IDatabase& db);
    std::optional<DataContainers> getInitData () const;
};

} // initializer
} // server



#endif // INITIALIZER