project(transfer)

set(HEADERS
   ../templates/include/data_queue.h
   ../templates/include/indexed_container.h
   lib/asio/include/asio.hpp
   include/pack.h
   include/i_transfer.h
   include/tcp_transfer.h
)

set(SOURCES
   src/tcp_transfer.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../templates/include/
   ../server_output/include/
   lib/asio/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
   server_output
)