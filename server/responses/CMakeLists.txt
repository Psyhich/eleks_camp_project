project(responses)

set (HEADERS
    include/responses.h
)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        initializer
        searcher
)