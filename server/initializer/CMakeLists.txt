project(initializer)

set(HEADERS
    ../database_api/include/i_database_api.h
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
   ../database_api/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    db_api
)