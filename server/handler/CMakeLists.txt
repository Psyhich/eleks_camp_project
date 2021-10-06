project(handler)

set(HEADERS
   include/i_handler.h
   include/handler.h
)

set(SOURCES
   src/handler.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
)

target_link_libraries(${PROJECT_NAME}
   PUBLIC
      requests
      responses
      initializer
      searcher
      modifier
)