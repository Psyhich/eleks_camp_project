project(types)

set(HEADERS include/front_recipe.h include/request_structs.h include/response_structs.h)

set(SOURCES src/recipe.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

