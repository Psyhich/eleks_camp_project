#include "local_receiver.h"

namespace server{
namespace receiver{

LocalReceiver::LocalReceiver(localex::IServerExchange& localExchange)
    :
    localExchange{localExchange}
{}

requests::RequestVar LocalReceiver::getRequest() const {
    return localExchange.getRequest();
}

} // namespace receiver
} // namespace server