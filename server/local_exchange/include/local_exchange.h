#ifndef LOCAL_EXCHANGE
#define LOCAL_EXCHANGE

#include <atomic>

#include "data_queue.h"
#include "requests.h"
#include "responses.h"

#include "i_frontend_exchange.h"
#include "i_server_exchange.h"

namespace server {
namespace localex {

class LocalExchange : public virtual IFrontendExchange, public virtual IServerExchange {
    static constexpr int queueTimeoutMs = 1000;

    using RequestQueue = helpers::DataQueue<requests::RequestVar, queueTimeoutMs>;
    using ResponseQueue = helpers::DataQueue<responses::ResponseVar, queueTimeoutMs>;
protected:
    RequestQueue requests;
    ResponseQueue responses;
public:

    virtual void start() override;
    virtual void stop() override;

    virtual void sendRequest(const requests::RequestVar& request) override;
    virtual responses::ResponseVar getResponse() override;

    virtual requests::RequestVar getRequest() override;
    virtual void sendResponse (const responses::ResponseVar& response) override;
};

} // namespace localex
} // namespace server

#endif // LOCAL_EXCHANGE