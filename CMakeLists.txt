cmake_minimum_required(VERSION 3.10)
project(SortingProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(sorter 
    src/main.cpp 
    src/simple_sorts.cpp 
    src/efficient_sorts.cpp 
    src/advanced_sorts.cpp
)

target_compile_options(sorter PRIVATE -O3 -Wall -Wextra)
