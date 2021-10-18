project(widgets)

set(HEADERS
    include/criteria_widget.h
    include/ingredients_filter_widget.h
    include/recipes_list_view.h
    include/search_filters.h
    include/ingredients_edit_widget.h
    include/recipe_row_view.h
    include/row_holder.h
    include/search_widget.h
)

set(SOURCES
    src/criteria_widget.cpp
    src/ingredients_filter_widget.cpp
    src/recipes_list_view.cpp
    src/search_filters.cpp
    src/ingredients_edit_widget.cpp
    src/recipe_row_view.cpp
    src/row_holder.cpp
    src/search_widget.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PRIVATE
    types
    misc_utilities
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
