#ifndef INITIALIZER
#define INITIALIZER

#include <optional>

#include "database_api.h"
#include "data_containers.h"

#include "i_initializer.h"

namespace server {
namespace initializer {

class Initializer : public IInitializer {
protected:
    dbAPI::IDatabase& db;
public:
    Initializer(dbAPI::IDatabase& db);
    virtual ~Initializer() = default;

    virtual std::optional<DataContainers> getInitData() const override;
};

} // initializer
} // server

#endif // INITIALIZER