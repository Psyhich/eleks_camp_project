#ifndef LOCAL_SERVER_KEEPER
#define LOCAL_SERVER_KEEPER

#include <string>

#include "database_api.h"
#include "handler.h"
#include "initializer.h"
#include "local_exchange.h"
#include "local_receiver.h"
#include "local_sender.h"
#include "modifier.h"
#include "searcher.h"
#include "server.h"

#include "i_frontend_exchange.h"

namespace server{

class LocalServerKeeper {
    dbAPI::Database dataBase;
    initializer::Initializer initializer;
    searcher::Searcher searcher;
    modifier::Modifier modifier;
    handler::Handler handler;
    localex::LocalExchange localExchange;
    receiver::LocalReceiver receiver;
    sender::LocalSender sender;
    server::Server server;
public:
    LocalServerKeeper();
    LocalServerKeeper(const std::string& dbPath);
    LocalServerKeeper(const LocalServerKeeper&) = delete;
    ~LocalServerKeeper();

    localex::IFrontendExchange& getLocalExchange() noexcept {return localExchange;}
};

} // namespace server

#endif // LOCAL_SERVER_KEEPER