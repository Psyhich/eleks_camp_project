#include "server.h"

#include <variant>

namespace server {

Server::Server(
    handler::IHandler& handler,
    receiver::IReceiver& receiver,
    sender::ISender& sender
    ) :
    handler{handler},
    receiver{receiver},
    sender{sender}
{}

void Server::operator()() {
    while (true){
        auto responseOpt = handleRequest(getRequest());
        if (responseOpt){
            sendResponse(*responseOpt);
        } else {
            break;
        }
    }
}

requests::RequestVar Server::getRequest() const {
    return receiver.getRequest();
}

std::optional<responses::ResponseVar> Server::handleRequest(const requests::RequestVar& request) const {
    return std::visit(handler, request);
}

void Server::sendResponse(const responses::ResponseVar& response) const {
    sender.sendResponse(response);
}

} // namespace server