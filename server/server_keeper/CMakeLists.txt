project (server_keeper)

set(HEADERS
    ../database_api/include/database_api.h
    ../initializer/include/initializer.h
    ../searcher/include/searcher.h
    ../modifier/include/modifier.h
    ../requests/include/requests.h
    ../responses/include/responses.h
    ../handler/include/handler.h
    ../local_exchange/include/local_exchange.h
    ../transfer/include/tcp_transfer.h
    ../deserializer/include/json_deserializer.h
    ../serializer/include/json_serializer.h
    ../receiver/include/local_receiver.h
    ../receiver/include/remote_receiver.h
    ../sender/include/local_sender.h
    ../sender/include/remote_sender.h
    ../server/include/server.h
    ../local_exchange/include/i_frontend_exchange.h
    ../server/include/i_server.h
   include/local_server_keeper.h
   include/remote_server_keeper.h
)

set(SOURCES
   src/local_server_keeper.cpp
   src/remote_server_keeper.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../database_api/include/
   ../initializer/include/
   ../searcher/include/
   ../requests/include/
   ../responses/include/
   ../handler/include/
   ../local_exchange/include/
   ../transfer/include/
   ../deserializer/include/
   ../serializer/include/
   ../receiver/include/
   ../sender/include/
   ../server/include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    db_api
    initializer
    searcher
    modifier
    handler
    local_exchange
    transfer
    deserializer
    serializer
    receiver
    sender
    server
)