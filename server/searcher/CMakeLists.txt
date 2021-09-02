add_library(searcher STATIC src/searcher.cpp)
target_include_directories(searcher PUBLIC include)

target_include_directories(searcher PUBLIC db_api)
target_link_libraries(searcher PRIVATE db_api)