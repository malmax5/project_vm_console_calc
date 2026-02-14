cmake_minimum_required(VERSION 3.14)
project(ConsoleCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    pvm_math_lib
    GIT_REPOSITORY https://github.com/malmax5/project_vm_math_lib
    GIT_TAG dev
)
FetchContent_MakeAvailable(pvm_math_lib)

add_executable(calculator
    src/main.cpp
)

target_include_directories(calculator PRIVATE include)
target_link_libraries(calculator PRIVATE pvm_math_lib)
