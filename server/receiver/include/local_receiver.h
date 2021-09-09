#ifndef LOCAL_RECEIVER
#define LOCAL_RECEIVER

#include "i_server_exchange.h"

#include "i_receiver.h"

namespace server {
namespace receiver {

class LocalReceiver : public IReceiver {
protected:
    localex::IServerExchange& localExchange;
public:
    LocalReceiver(localex::IServerExchange& localExchange);
    virtual ~LocalReceiver() = default;

    virtual requests::RequestVar getRequest() const override;
};

} // namespace receiver
} // namespace server

#endif // LOCAL_RECEIVER