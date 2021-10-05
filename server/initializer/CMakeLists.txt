project(initializer)

set(HEADERS
   include/data_containers.h
   include/i_initializer.h
   include/initializer.h
)

set(SOURCES
   src/initializer.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    db_api
)