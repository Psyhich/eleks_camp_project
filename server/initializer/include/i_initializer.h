#ifndef I_INITIALIZER
#define I_INITIALIZER

#include <optional>

#include "data_containers.h"

namespace server {
namespace initializer {

class IInitializer {
public:
    virtual ~IInitializer() = default;

    virtual std::optional<DataContainers> getInitData() const = 0;
};

} // initializer
} // server

#endif // I_INITIALIZER