#include "remote_server_keeper.h"

namespace server {

    RemoteServerKeeper::~RemoteServerKeeper(){
        stop();
    }

    void RemoteServerKeeper::start(){
        try {
            transfer.start();
            server.start();
        } catch (std::exception& e){
            stop();
            throw;
        }
    }

    void RemoteServerKeeper::stop(){
        transfer.stop();
        server.stop();
    }

} // namespace server