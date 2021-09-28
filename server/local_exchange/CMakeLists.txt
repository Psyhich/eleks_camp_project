project(local_exchange)

set(HEADERS
    ../requests/include/requests.h
    ../responses/include/responses.h
    ../templates/include/data_queue.h
   include/i_frontend_exchange.h
   include/i_server_exchange.h
   include/local_exchange.h
)

set(SOURCES
   src/local_exchange.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../initializer/include/
   ../searcher/include/
   ../recipe/include/
   ../requests/include/
   ../responses/include/
   ../templates/include/      
)