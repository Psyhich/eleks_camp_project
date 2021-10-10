cmake_minimum_required(VERSION 3.16)

project(project-front-desktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(PROJECT_SOURCES
        # Project sources
	main.cpp
	# Widgets
	widgets/mainwindow.ui

	widgets/mainwindow.h
	widgets/mainwindow.cpp

	widgets/tab_manager.h
	widgets/tab_manager.cpp

	widgets/recipe_view_tab.h
	widgets/recipe_view_tab.cpp

	widgets/search_tab.h
	widgets/search_tab.cpp

	widgets/recipes_list_view.h
	widgets/recipes_list_view.cpp

	widgets/recipe_row_view.h
	widgets/recipe_row_view.cpp

	widgets/search_filters.h
	widgets/search_filters.cpp

	widgets/search_widget.h
	widgets/search_widget.cpp

	widgets/criteria_widget.h
	widgets/criteria_widget.cpp

	widgets/ingredients_filter_widget.h
	widgets/ingredients_filter_widget.cpp

	widgets/recipe_edit_tab.h
	widgets/recipe_edit_tab.cpp

	widgets/ingredients_edit_widget.h
	widgets/ingredients_edit_widget.cpp

	widgets/row_holder.h
	widgets/row_holder.cpp
	# Base data types
	types/recipe.h
	types/recipe.cpp

	types/requests.h
	types/requests.cpp

	types/responses.h
	types/responses.cpp

	types/favorites_manager.h
	types/favorites_manager.cpp
	# Connection and network
	connections/connection_manager.h
	connections/connection_manager.cpp

	connections/i_connector.h

	connections/connectors.h
	connections/local_connector.cpp
	connections/remote_connector.cpp
	# Resources
	icon_favorite.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(project-front-desktop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(project-front-desktop SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(project-front-desktop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(project-front-desktop PUBLIC ${SERVER_KEEPER_INCLUDE_DIRECTORIES})
target_link_libraries(project-front-desktop PUBLIC server_keeper)

target_link_libraries(project-front-desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(project-front-desktop PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(project-front-desktop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(project-front-desktop)
endif()
