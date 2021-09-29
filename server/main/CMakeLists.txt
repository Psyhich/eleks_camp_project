project (eleks_chef_server)

set(HEADERS
    ../server/include/i_server.h
    ../server_keeper/include/remote_server_keeper.h
)

set(SOURCES
    main.cpp
)

add_executable (${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ../server/include/
    ../server_keeper/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    server_keeper
)