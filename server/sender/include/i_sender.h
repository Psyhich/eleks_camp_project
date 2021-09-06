#ifndef I_SENDER
#define I_SENDER

#include "responses.h"

namespace server {
namespace sender {

class ISender {
public:
    virtual ~ISender() = default;

    virtual void sendResponse(const responses::ResponseVar& response) const = 0;
};


} // namespace sender
} // namespace server

#endif // I_SENDER