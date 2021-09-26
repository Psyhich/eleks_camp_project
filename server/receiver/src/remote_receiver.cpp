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

void RemoteReceiver::start() {
    transfer.start();
}

void RemoteReceiver::stop() {
    transfer.stop();
}

requests::RequestVar RemoteReceiver::getRequest() const {
    return deserializer.getRequest(transfer.getPack());
}

} // namespace receiver
} // namespace server