project(sender)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
   INTERFACE
      responses
   PUBLIC
      local_exchange
      transfer
      serializer
)