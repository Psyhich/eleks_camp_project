#include "local_server_keeper.h"

#include <exception>

namespace server {

LocalServerKeeper::LocalServerKeeper()
    :
    dataBase{},
    initializer{dataBase},
    searcher{dataBase},
    modifier{dataBase},
    handler{initializer, searcher, modifier},
    localExchange{},
    receiver{localExchange},
    sender{localExchange},
    server{handler, receiver, sender}
{
    try {
        server.start();
    } catch (std::exception& e) {
        server.stop();
        throw;
    }
}

LocalServerKeeper::LocalServerKeeper(const std::string& dbPath)
    :
    dataBase{dbPath},
    initializer{dataBase},
    searcher{dataBase},
    modifier{dataBase},
    handler{initializer, searcher, modifier},
    localExchange{},
    receiver{localExchange},
    sender{localExchange},
    server{handler, receiver, sender}
{
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