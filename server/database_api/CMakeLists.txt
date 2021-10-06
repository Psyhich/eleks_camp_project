project(db_api)

add_subdirectory(lib/SQLiteCpp)

set(HEADERS
    ../initializer/include/data_containers.h
    ../searcher/include/criteria.h
    ../searcher/include/results.h
    include/i_database_api.h
    include/database_api.h
)

set(SOURCES
    src/database_api.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include/
        ../initializer/include/
        ../searcher/include/
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC    
        recipe
        SQLiteCpp
)