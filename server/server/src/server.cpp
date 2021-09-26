#include "server.h"

#include <iostream>
#include <stdexcept>
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

void Server::start() {
    receiver.start();
    ThreadCycler::start();
}

void Server::stop() {
    receiver.stop();
    ThreadCycler::stop();
}

void Server::work() {
    sendResponse(handleRequest(getRequest()));
}

void Server::handleFatalThreadException(std::exception& e) {
    receiver.stop();
    ThreadCycler::handleFatalThreadException(e);
}

requests::RequestVar Server::getRequest() const {
    return receiver.getRequest();
}

responses::ResponseVar Server::handleRequest(const requests::RequestVar& request) const {
    return std::visit(handler, request);
}

void Server::sendResponse(const responses::ResponseVar& response) const {
    sender.sendResponse(response);
}

} // namespace server