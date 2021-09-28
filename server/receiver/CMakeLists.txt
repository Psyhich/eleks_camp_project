project(receiver)

set(HEADERS
    ../requests/include/requests.h
    ../local_exchange/include/i_server_exchange.h
    ../transfer/include/i_transfer.h
    ../deserializer/include/i_deserializer.h
   include/i_receiver.h
   include/local_receiver.h
   include/remote_receiver.h
)

set(SOURCES
   src/local_receiver.cpp
   src/remote_receiver.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../searcher/include/
   ../recipe/include/
   ../requests/include/
   ../transfer/include/
   ../deserializer/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    local_exchange
    transfer
    deserializer
)