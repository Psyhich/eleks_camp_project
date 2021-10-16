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
find_package(Qt${QT_VERSION_MAJOR}Network REQUIRED)

add_subdirectory(widgets/)
add_subdirectory(types/)
add_subdirectory(connections/)
add_subdirectory(tabs/)
add_subdirectory(misc/)

set(PROJECT_SOURCES
        # Project sources
	main.cpp

	mainwindow.h
	mainwindow.cpp

	# Resources
	resources.qrc
	mainwindow.ui
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

target_link_libraries(project-front-desktop PUBLIC
    types
    connections
    tabs
    widgets
)

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
