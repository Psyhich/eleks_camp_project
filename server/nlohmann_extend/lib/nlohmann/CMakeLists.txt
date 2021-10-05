project(nlohmann)

set (HEADERS
    include/json.hpp
)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include/
)