#ifndef LOCAL_SERVER_KEEPER
#define LOCAL_SERVER_KEEPER

#include "database_api.h"
#include "handler.h"
#include "initializer.h"
#include "local_exchange.h"
#include "local_receiver.h"
#include "local_sender.h"
#include "modifier.h"
#include "requests.h"
#include "responses.h"
#include "searcher.h"
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
    LocalServerKeeper();
    LocalServerKeeper(const LocalServerKeeper&) = delete;
    ~LocalServerKeeper();
    
    void sendRequest(const requests::RequestVar& request) const;
    responses::ResponseVar getResponse() const;
};

} // namespace server

#endif // LOCAL_SERVER_KEEPER