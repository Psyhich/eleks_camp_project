project(serializer)

set(HEADERS
    ../responses/include/responses.h
    ../transfer/include/pack.h
    ../nlohmann_extend/include/nlohmann_extend.h
   include/response_tag.h
   include/i_serializer.h
   include/json_serializer.h
)

set(SOURCES
   src/json_serializer.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../initializer/include/
   ../searcher/include/
   ../responses/include/
   ../transfer/include/
   ../nlohmann_extend/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_extend
)