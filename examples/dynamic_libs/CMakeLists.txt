project(dynamic_libs)

add_library(functions SHARED functions.cpp)

add_executable(main main.cpp)
target_link_libraries(main functions)