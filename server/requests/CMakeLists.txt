project(requests)

set (HEADERS
    include/requests.h
)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include/
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        recipe
        searcher
)