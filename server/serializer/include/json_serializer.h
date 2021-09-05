#ifndef JSON_SERIALIZER
#define JSON_SERIALIZER

#include "i_serializer.h"

namespace server {
namespace serializer {

class JsonSerializer : public ISerializer {
    struct Process;
public:
    virtual ~JsonSerializer() = default;

    virtual transfer::Pack getPack(const responses::ResponseVar& resp) const override;
};

} // namespace serializer
} // namespace server

#endif // JSON_SERIALIZER