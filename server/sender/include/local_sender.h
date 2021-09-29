#ifndef LOCAL_SENDER
#define LOCAL_SENDER

#include "i_server_exchange.h"

#include "i_sender.h"

namespace server {
namespace sender {
class LocalSender: public ISender {
protected:
    localex::IServerExchange& localExchange;
public:
    LocalSender(localex::IServerExchange& localExchange);
    virtual ~LocalSender() = default;

    virtual void start() override;
    virtual void stop() override;

    virtual void sendResponse(const responses::ResponseVar& response) const override;
};

} // sender
} // server

#endif // LOCAL_SENDER