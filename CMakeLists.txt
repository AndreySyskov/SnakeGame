cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 11)



add_executable(snake main.cpp)

target_link_libraries(snake ncurses)

