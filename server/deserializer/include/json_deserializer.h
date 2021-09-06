#ifndef JSON_DESERIALIZER
#define JSON_DESERIALIZER

#include "i_deserializer.h"

namespace server {
namespace deserializer {

class JsonDeserializer : public IDeserializer {
public:
    virtual ~JsonDeserializer() = default;

    virtual requests::RequestVar getRequest(const transfer::Pack& inPack) const override;
};

} // namespace deserializer
} // namespace server

#endif // JSON_DESERIALIZER