#include "local_server_keeper.h"

#include <exception>

namespace server {

LocalServerKeeper::LocalServerKeeper() {
    try {
        server.start();
    } catch (std::exception& e) {
        server.stop();
        throw;
    }
}

LocalServerKeeper::~LocalServerKeeper() {
    server.stop();  
}

} // namespace server