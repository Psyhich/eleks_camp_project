project(server_output)

set(HEADERS
   include/server_output.h
)

set(SOURCES
    src/server_output.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)