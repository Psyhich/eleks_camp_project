project(connections)

set(HEADERS include/connection_manager.h  include/connectors.h  include/i_connector.h  include/front_requests.h  include/front_responses.h)

set(SOURCES src/connection_manager.cpp  src/local_connector.cpp  src/remote_connector.cpp  src/front_requests.cpp  src/front_responses.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PRIVATE types)

target_link_libraries(${PROJECT_NAME} PUBLIC server_keeper)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)
