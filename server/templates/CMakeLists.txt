project(templates)

set (HEADERS
    include/data_queue.h
    include/indexed_container.h
)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include/
)