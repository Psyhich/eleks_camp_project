project(server)

set(HEADERS
   include/i_server.h
   include/server.h
)

set(SOURCES
   src/server.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
)

target_link_libraries(${PROJECT_NAME}
   INTERFACE
      requests
      responses
   PUBLIC
      handler
      receiver
      sender
      thread_cycler
)