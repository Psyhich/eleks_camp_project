#include "remote_server_keeper.h"

namespace server {

RemoteServerKeeper::~RemoteServerKeeper(){
    server.stop();
}

} // namespace server