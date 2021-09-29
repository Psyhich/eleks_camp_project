#include "local_exchange.h"

#include <utility>
#include <variant>

namespace server {
namespace localex {

void LocalExchange::start() {
    requests.start();
    responses.start();
}

void LocalExchange::stop() {
    requests.stop();
    requests.stop();
}

void LocalExchange::sendRequest(const requests::RequestVar& request) {
    requests.push(request);
}

responses::ResponseVar LocalExchange::getResponse() {
    responses.wait();
    if (!responses.empty()){
        return responses.popGet();
    } else {
        return responses::ResponseVar(std::in_place_type<responses::Error>, "", 0);
    }
}

requests::RequestVar LocalExchange::getRequest() {
    requests.wait();
    if (!requests.empty()){
        return requests.popGet();
    } else {
        return requests::RequestVar(std::in_place_type<requests::Error>, 0);
    }
}

void LocalExchange::sendResponse (const responses::ResponseVar& response) {
    responses.push(response);
}

} // namespace localex
} // namespace server