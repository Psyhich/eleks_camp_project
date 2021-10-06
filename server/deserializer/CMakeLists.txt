project(deserializer)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        transfer
        requests
        nlohmann_extend
)