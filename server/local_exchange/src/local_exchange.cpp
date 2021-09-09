#include "local_exchange.h"

namespace server {
namespace localex {

void LocalExchange::sendRequest(const requests::RequestVar& request) {
    requests.push(request);
}

responses::ResponseVar LocalExchange::getResponse() {
    responses.wait();
    return responses.popGet();
}

requests::RequestVar LocalExchange::getRequest() {
    requests.wait();
    return requests.popGet();
}

void LocalExchange::sendResponse (const responses::ResponseVar& response) {
    responses.push(response);
}

} // namespace localex
} // namespace server