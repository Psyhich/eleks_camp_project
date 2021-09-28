project(thread_cycler)

set(HEADERS
   include/thread_cycler.h
)

set(SOURCES
   src/thread_cycler.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
   include/
)