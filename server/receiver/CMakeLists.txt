project(receiver)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
   INTERFACE
      requests
   PUBLIC
      local_exchange
      transfer
      deserializer
)