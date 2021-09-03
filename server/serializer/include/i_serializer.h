#ifndef I_SERIALIZER
#define I_SERIALIZER

#include "pack.h"
#include "responses.h"

namespace server {
namespace serializer {

class ISerializer {
public:
    virtual ~ISerializer() = default;

    virtual transfer::Pack getPack(const responses::ResponseVar& resp) const = 0;
};

} // serializer
} // server

#endif // I_SERIALIZER