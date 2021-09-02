add_library(initializer STATIC src/initializer.cpp)
target_include_directories(initializer PUBLIC include)

target_include_directories(initializer PUBLIC db_api)
target_link_libraries(initializer PRIVATE db_api)