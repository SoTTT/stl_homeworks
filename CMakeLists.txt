cmake_minimum_required(VERSION 3.23)
project(stl_homeworks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(homework_5_lib)

include_directories(homework_5_lib/src)

# "link_directories" should be take before of "add_executable"
link_directories(./cmake-build-debug/homework_5_lib
        cmake-build-debug-visual-studio/homework_5_lib/Debug)

add_executable(hello main.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_link_libraries(hello homework_5.a)
else ()
    target_link_libraries(hello homework_5.lib)
endif ()

