#include "remote_receiver.h"

namespace server {
namespace receiver {

RemoteReceiver::RemoteReceiver(
    transfer::ITransfer& transfer,
    deserializer::IDeserializer& deserializer
    ) :
    transfer{transfer},
    deserializer{deserializer}
{}

requests::RequestVar RemoteReceiver::getRequest() const {
    return deserializer.getRequest(transfer.getPack());
}

} // namespace receiver
} // namespace server