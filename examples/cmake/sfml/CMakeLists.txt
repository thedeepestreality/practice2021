cmake_minimum_required(VERSION 3.1)
project(SFMLTest)

find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
add_executable(sfml-test main.cpp)
target_link_libraries(sfml-test sfml-graphics)

add_executable(sfml-image image.cpp)
target_link_libraries(sfml-image sfml-graphics)


add_executable(sfml-pixel set_pixel.cpp)
target_link_libraries(sfml-pixel sfml-graphics)
