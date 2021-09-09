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

Server::~Server() {
    stop();
}

void Server::start() {
    if (stopFlag.load()){
        stopFlag.store(false);
        threadPtr.reset(new std::thread([this](){run();}));
    }
}

void Server::stop() {
    if (!stopFlag.load()){
        stopFlag.store(true);
        threadPtr->join();
    }
}


void Server::run(){
    while (true){
        sendResponse(handleRequest(getRequest()));
        if (stopFlag.load()){
            break;
        }
    }
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