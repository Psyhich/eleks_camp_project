project(local_exchange)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
   PUBLIC
      templates
      requests
      responses
)