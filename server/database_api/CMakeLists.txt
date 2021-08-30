cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDART 17)

add_library(db_api STATIC src/database_api.cpp)

add_subdirectory(lib/SQLiteCpp)

target_link_libraries(db_api SQLiteCpp)