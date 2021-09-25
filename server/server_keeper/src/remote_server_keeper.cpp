#include "remote_server_keeper.h"

namespace server {

    RemoteServerKeeper::~RemoteServerKeeper(){
        stop();
    }

    void RemoteServerKeeper::start(){
        transfer.start();
        server.start();
    }

    void RemoteServerKeeper::stop(){
        transfer.stop();
        server.stop();
    }

} // namespace server