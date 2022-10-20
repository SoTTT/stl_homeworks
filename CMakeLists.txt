cmake_minimum_required(VERSION 3.23)
project(stl_homeworks)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(homework_4_lib)

include_directories(homework_4_lib/src)

# "link_directories" should be take before of "add_executable"
link_directories(./cmake-build-debug/homework_4_lib)

add_executable(hello main.cpp)

target_link_libraries(hello homework_4.a)


