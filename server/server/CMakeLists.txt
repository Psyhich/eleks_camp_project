project(server)

set(HEADERS
    ../handler/include/i_handler.h
    ../receiver/include/i_receiver.h
    ../sender/include/i_sender.h
    ../requests/include/requests.h
    ../responses/include/responses.h
    ../thread_cycler/include/thread_cycler.h
   include/i_server.h
   include/server.h
)

set(SOURCES
   src/server.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../handler/include/
   ../receiver/include/
   ../sender/include/
   ../initializer/include/
   ../searcher/include/
   ../recipe/include/
   ../requests/include/
   ../responses/include/
   ../thread_cycler/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    handler
    receiver
    sender
    thread_cycler
)