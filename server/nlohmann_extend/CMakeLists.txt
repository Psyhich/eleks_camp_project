project(nlohmann_extend)

set(HEADERS
    ../initializer/include/data_containers.h    
    ../searcher/include/criteria.h
    ../searcher/include/results.h
    ../recipe/include/recipe.h
   lib/nlohmann/include/json.hpp
   include/nlohmann_extend.h
)

set(SOURCES
   src/nlohmann_extend.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../initializer/include/
   ../searcher/include/
   ../recipe/include/
   lib/nlohmann/include/
)