#include "local_sender.h"

namespace server {
namespace sender {

LocalSender::LocalSender(localex::IServerExchange& localExchange)
    :
    localExchange{localExchange}
{}

void LocalSender::start() {
    localExchange.start();
}

void LocalSender::stop() {
    localExchange.stop();
};

void LocalSender::sendResponse(const responses::ResponseVar& response) const {
    localExchange.sendResponse(response);
}

} // namespace sender
} // namespace server
