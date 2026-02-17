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

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
    message(STATUS "clang-tidy found.")
else()
    message(WARNING "clang-tidy not found.")
endif()

add_executable(calculator
    src/main.cpp
    src/checker.cpp
    src/parser.cpp
    src/printer.cpp
    src/runner.cpp
)

target_include_directories(calculator PRIVATE include)
target_link_libraries(calculator PRIVATE pvm_math_lib)

find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "src/*.cpp"
        "include/*.hpp"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCE_FILES}
        COMMENT "Formatting code with clang-format..."
    )
    message(STATUS "clang-format found.")
else()
    message(WARNING "clang-format not found.")
endif()
