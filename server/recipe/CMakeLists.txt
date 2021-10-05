project(recipe)

set (HEADERS
    include/recipe.h
)

add_library(${PROJECT_NAME} INTERFACE ${HEADERS})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include/
)