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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data/cookbook.db $<TARGET_FILE_DIR:${PROJECT_NAME}>
)