set(CMAKE_CXX_STANDART 17)

add_library(db_api STATIC src/database_api.cpp)
target_include_directories(db_api PUBLIC include)

add_subdirectory(lib/SQLiteCpp)
target_link_libraries(db_api PUBLIC SQLiteCpp)

target_include_directories(db_api PUBLIC initializer)
target_link_libraries(db_api PUBLIC initializer)

target_include_directories(db_api PUBLIC searcher)
target_link_libraries(db_api PUBLIC searcher)

target_include_directories(db_api PUBLIC ../recipe/include)