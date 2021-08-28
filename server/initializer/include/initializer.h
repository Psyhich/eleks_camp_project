#ifndef INITIALIZER
#define INITIALIZER

#include <optional>

#include "data_base_api.h"
#include "data_containers.h"

namespace server {
namespace initializer {

class Initializer {
    dbAPI::IDataBase& db;
public:
    Initializer(dbAPI::IDataBase& db);
    std::optional<DataContainers> getInitData () const;
};

} // initializer
} // server



#endif // INITIALIZER