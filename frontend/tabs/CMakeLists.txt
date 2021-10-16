project(tabs)

set(HEADERS
    include/abstract_tab.h
    include/recipe_edit_tab.h
    include/recipe_view_tab.h
    include/search_tab.h
    include/tab_manager.h
)

set(SOURCES
    src/abstract_tab.cpp
    src/recipe_edit_tab.cpp
    src/recipe_view_tab.cpp
    src/search_tab.cpp
    src/tab_manager.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PRIVATE
    widgets
    types
    connections
    misc_utilities
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
