project (server_keeper)

set(HEADERS
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