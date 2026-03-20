cmake_minimum_required(VERSION 3.14)
project(ConsoleCalc LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

find_package(PostgreSQL REQUIRED)

FetchContent_Declare(
    pvm_math_lib
    GIT_REPOSITORY https://github.com/malmax5/project_vm_math_lib
    GIT_TAG dev
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.0
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(pvm_math_lib spdlog json fmt googletest)

add_library(app_logic STATIC
    src/logger/Logger.cpp
    src/parser/JsonParser.cpp
    src/checker/Checker.cpp
    src/calculator/Calculator.cpp
    src/printer/Printer.cpp
    src/runner/Runner.cpp
    src/models/DbConfig.cpp
    src/infrastructure/ConfigLoader.cpp
    src/database/DbResult.cpp
    src/database/PostgresConnection.cpp
    src/database/repositories/DbRepository.cpp
)

target_include_directories(app_logic PRIVATE
    include
    ${PostgreSQL_INCLUDE_DIRS}
)
target_link_libraries(app_logic PRIVATE
    pvm_math_lib
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    PostgreSQL::PostgreSQL
    fmt::fmt
)

add_executable(calculator src/main.cpp)
target_include_directories(calculator PRIVATE include)
target_link_libraries(calculator PRIVATE app_logic)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CLANG_TIDY_ARGS 
        "${CLANG_TIDY_EXE}"
        "--config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy"
        "--header-filter=${CMAKE_CURRENT_SOURCE_DIR}/(include|src)/.*"
        "--extra-arg=-Wno-unknown-warning-option"
    )

    set_target_properties(calculator PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_ARGS}")
    
    set_target_properties(app_logic PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_ARGS}")

    if(TARGET unit_tests)
        set_target_properties(unit_tests PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_ARGS}")
    endif()

    message(STATUS "clang-tidy found and configured for all targets.")
else()
    message(WARNING "clang-tidy not found.")
endif()

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    enable_testing()
    add_executable(unit_tests
        tests/test_main.cpp
        tests/test_checker.cpp
        tests/test_parser.cpp
        tests/test_calculator.cpp
    )

    target_include_directories(unit_tests PRIVATE include)
    target_link_libraries(unit_tests PRIVATE
        app_logic
        pvm_math_lib
        GTest::gtest
    )

    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        "src/*.cpp"
        "include/*.hpp"
        "tests/*.cpp"
    )

    if (NOT TARGET format_app)
        add_custom_target(format_app
            COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCE_FILES}
            COMMENT "Formatting code with clang-format..."
        )
    endif()
    message(STATUS "clang-format found.")
else()
    message(WARNING "clang-format not found.")
endif()

include(GNUInstallDirs)
install(TARGETS calculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
