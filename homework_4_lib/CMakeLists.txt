project(HOMEWORK_4_LIB)
set(CMAKE_CXX_STANDARD 11)

set(SHARED_TARGET "homework_4_shared")
set(STATIC_TARGET "homework_4_static")

add_library(${STATIC_TARGET} STATIC
        src/Student.cpp src/extern_function.cpp src/extern_function.h src/Student.h)
add_library(${SHARED_TARGET} SHARED
        src/Student.cpp src/extern_function.cpp src/extern_function.h src/Student.h)

set_target_properties(${STATIC_TARGET}
        PROPERTIES OUTPUT_NAME "homework_4")
set_target_properties(${SHARED_TARGET}
        PROPERTIES OUTPUT_NAME "homework_4")

get_target_property(shared_lib_name ${SHARED_TARGET} OUTPUT_NAME)
message(STATUS "the ${PROJECT_NAME} shared library name is ${shared_lib_name}")

get_target_property(static_lib_name ${STATIC_TARGET} OUTPUT_NAME)
message(STATUS "the ${PROJECT_NAME} static library name is ${static_lib_name}")

include_directories(../include)