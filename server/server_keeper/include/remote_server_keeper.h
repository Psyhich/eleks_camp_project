#ifndef REMOTE_SERVER_KEEPER
#define REMOTE_SERVER_KEEPER

#include "database_api.h"
#include "handler.h"
#include "initializer.h"
#include "json_deserializer.h"
#include "json_serializer.h"
#include "modifier.h"
#include "remote_receiver.h"
#include "remote_sender.h"
#include "searcher.h"
#include "server.h"
#include "tcp_transfer.h"

namespace server{

class RemoteServerKeeper {
    static constexpr unsigned short port = 7777;

    dbAPI::Database dataBase;
    initializer::Initializer initializer{dataBase};
    searcher::Searcher searcher{dataBase};
    modifier::Modifier modifier{dataBase};
    handler::Handler handler{initializer, searcher, modifier};
    transfer::TCPTransfer transfer {port};
    deserializer::JsonDeserializer deserializer;
    receiver::RemoteReceiver receiver{transfer, deserializer};
    serializer::JsonSerializer serializer;
    sender::RemoteSender sender{transfer, serializer};
    server::Server server{handler, receiver, sender};
public:
    RemoteServerKeeper() = default;
    RemoteServerKeeper(const RemoteServerKeeper&) = delete; 
    ~RemoteServerKeeper();

    void start();
    void stop();
};

} // namespace server

#endif // REMOTE_SERVER_KEEPER