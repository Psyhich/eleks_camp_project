project(handler)

set(HEADERS
    ../requests/include/requests.h
    ../responses/include/responses.h
    ../initializer/include/i_initializer.h
    ../searcher/include/i_searcher.h
    ../modifier/include/i_modifier.h
   include/i_handler.h
   include/handler.h
)

set(SOURCES
   src/handler.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
   ../requests/include/
   ../responses/include/
   ../initializer/include/
   ../searcher/include/
   ../modifier/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    initializer
    searcher
    modifier
)