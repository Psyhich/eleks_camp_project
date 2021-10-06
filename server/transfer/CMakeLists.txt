project(transfer)

add_subdirectory(lib/asio)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
   PUBLIC
      asio
      templates
      server_output
)