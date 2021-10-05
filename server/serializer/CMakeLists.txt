project(serializer)

set(HEADERS
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
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        transfer
        responses
        nlohmann_extend
)