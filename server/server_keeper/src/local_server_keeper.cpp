#include "local_server_keeper.h"

#include <exception>

namespace server {

LocalServerKeeper::LocalServerKeeper() {
    try {
        localExchange.start();
        server.start();
    } catch (std::exception& e) {
        localExchange.stop();
        server.stop();
        throw;
    }
}

LocalServerKeeper::~LocalServerKeeper() {
    localExchange.stop();
    server.stop();  
}
    
void LocalServerKeeper::sendRequest(const requests::RequestVar& request){
    localExchange.sendRequest(request);
}

responses::ResponseVar LocalServerKeeper::getResponse() {
    return localExchange.getResponse();
}

} // namespace server