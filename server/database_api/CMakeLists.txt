project(db_api)

add_subdirectory(lib/SQLiteCpp)

set(HEADERS
    ../recipe/include/recipe.h
    ../initializer/include/data_containers.h
    ../searcher/include/criteria.h
    ../searcher/include/results.h
    include/i_database_api.h
    lib/SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h
    include/database_api.h
)

set(SOURCES
    src/database_api.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
    lib/SQLiteCpp/include/
    ../recipe/include/
    ../initializer/include/
    ../searcher/include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    SQLiteCpp
)