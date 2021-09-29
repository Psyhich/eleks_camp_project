project(deserializer)

set(HEADERS
    ../requests/include/requests.h
    ../transfer/include/pack.h
    ../nlohmann_extend/include/nlohmann_extend.h
    include/request_tag.h
    include/i_deserializer.h
    include/json_deserializer.h
)

set(SOURCES
    src/json_deserializer.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
    ../searcher/include/
    ../recipe/include/
    ../requests/include/
    ../transfer/include/
    ../nlohmann_extend/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    nlohmann_extend
)