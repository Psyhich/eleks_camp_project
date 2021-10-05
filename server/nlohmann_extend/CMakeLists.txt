project(nlohmann_extend)

add_subdirectory(lib/nlohmann)

set(HEADERS
   include/nlohmann_extend.h
)

set(SOURCES
   src/nlohmann_extend.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
)

target_link_libraries(${PROJECT_NAME}
   PUBLIC
      nlohmann
      recipe
      initializer
      searcher
)