project(sender)

set(HEADERS
    ../responses/include/responses.h
    ../local_exchange/include/i_server_exchange.h
    ../transfer/include/i_transfer.h
    ../serializer/include/i_serializer.h
   include/i_sender.h
   include/local_sender.h
   include/remote_sender.h
)

set(SOURCES
   src/local_sender.cpp
   src/remote_sender.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../initializer/include/
   ../searcher/include/
   ../responses/include/
   ../local_exchange/include/
   ../transfer/include/
   ../serializer/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    local_exchange
    transfer
    serializer
)