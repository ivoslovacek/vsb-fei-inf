cmake_minimum_required(VERSION 3.8)
project(tasks07)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

option(DISABLE_ASAN "Do not use Address sanitizer" OFF)


add_compile_options(-Wall -Wextra -pedantic)

# Use main.cpp to call and debug your functions
add_executable(tasks main.cpp tasks.cpp)

# Use the `tests` executable to run unit tests
add_executable(tests tests.cpp tasks.cpp)
