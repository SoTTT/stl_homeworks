cmake_minimum_required(VERSION 3.23)
project(stl_homeworks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(homework_7_lib)

include_directories(homework_7_lib/src)

# "link_directories" should be take before of "add_executable"
link_directories(./cmake-build-debug/homework_7_lib
        cmake-build-debug-visual-studio/homework_7_lib/Debug)

add_executable(hello main.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(hello homework_7.a)
else ()
    target_link_libraries(hello homework_7.lib)
endif ()

