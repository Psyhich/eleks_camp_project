#include "local_server_keeper.h"

namespace server {

LocalServerKeeper::LocalServerKeeper() {
    localExchange.start();
    server.start();
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