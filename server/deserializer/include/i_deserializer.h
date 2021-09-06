#ifndef I_DESERIALIZER
#define I_DESERIALIZER

#include "requests.h"
#include "pack.h"

namespace server {
namespace deserializer {

class IDeserializer {
public:
    ~IDeserializer() = default;

    virtual requests::RequestVar getRequest(const transfer::Pack& inPack) const = 0; 
};

} // deserializer
} // server

#endif // I_DESERIALIZER