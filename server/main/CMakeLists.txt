project (eleks_chef_server)

set(SOURCES
    main.cpp
)

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        server
        server_keeper
        server_output
)