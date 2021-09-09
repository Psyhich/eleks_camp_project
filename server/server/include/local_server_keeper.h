#ifndef LOCAL_SERVER_KEEPER
#define LOCAL_SERVER_KEEPER

#include "database_api.h"
#include "initializer.h"
#include "searcher.h"
#include "modifier.h"
#include "handler.h"
#include "local_exchange.h"
#include "local_receiver.h"
#include "local_sender.h"
#include "server.h"

namespace server{

class LocalServerKeeper {
    dbAPI::Database dataBase;
    initializer::Initializer initializer{dataBase};
    searcher::Searcher searcher{dataBase};
    modifier::Modifier modifier{dataBase};
    handler::Handler handler{initializer, searcher, modifier};
    localex::LocalExchange localExchange;
    receiver::LocalReceiver receiver{localExchange};
    sender::LocalSender sender{localExchange};
    server::Server server{handler, receiver, sender};
public:
    server::Server& getServer() {return server;}
    localex::IFrontendExchange& getFrontendExchange() {return localExchange;}
};

} // namespace server

#endif // LOCAL_SERVER_KEEPER