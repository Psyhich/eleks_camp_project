#ifndef I_FRONTEND_EXCHANGE
#define I_FRONTEND_EXCHANGE

#include "requests.h"
#include "responses.h"

namespace server {
namespace localex {

class IFrontendExchange {
public:
    virtual ~IFrontendExchange() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void sendRequest(const requests::RequestVar& request) = 0;
    virtual responses::ResponseVar getResponse() = 0;
};

} // namespace localex
} // namespace server

#endif // I_FRONTEND_EXCHANGE