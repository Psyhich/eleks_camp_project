project(searcher)

set(HEADERS
   include/criteria.h
   include/results.h
   include/i_searcher.h
   include/searcher.h
)

set(SOURCES
   src/searcher.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME}
   INTERFACE
      recipe
   PUBLIC
      include/
)

target_link_libraries(${PROJECT_NAME}
   INTERFACE
      recipe
   PUBLIC
      db_api
)