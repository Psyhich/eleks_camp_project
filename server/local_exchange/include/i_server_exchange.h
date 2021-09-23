#ifndef I_SERVER_EXCHANGE
#define I_SERVER_EXCHANGE

#include "requests.h"
#include "responses.h"

namespace server {
namespace localex {

class IServerExchange {
public:
    virtual ~IServerExchange() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual requests::RequestVar getRequest() = 0;
    virtual void sendResponse (const responses::ResponseVar& response) = 0;
};

} // namespace localex
} // namespace server

#endif // I_FRONTEND_EXCHANGE