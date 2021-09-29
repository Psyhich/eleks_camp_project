project(searcher)

set(HEADERS
    ../database_api/include/i_database_api.h
    ../recipe/include/recipe.h
   include/criteria.h
   include/results.h
   include/i_searcher.h
   include/searcher.h
)

set(SOURCES
   src/searcher.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../recipe/include/
   ../database_api/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    db_api
)