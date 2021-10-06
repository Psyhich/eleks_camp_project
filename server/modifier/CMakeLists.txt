project(modifier)

set(HEADERS
   include/i_modifier.h
   include/modifier.h
)

set(SOURCES
   src/modifier.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME}
   PUBLIC
      include/
)

target_link_libraries(${PROJECT_NAME}
   INTERFACE
      recipe
   PUBLIC
      db_api
)