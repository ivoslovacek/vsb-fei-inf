cmake_minimum_required(VERSION 3.8)
project(osy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_compile_options(-Wall -Wextra -pedantic)

# Use main.cpp to call and debug your functions
add_executable(generator generator.cpp)

# Use the `tests` executable to run unit tests
add_executable(scitacka scitacka.cpp)
