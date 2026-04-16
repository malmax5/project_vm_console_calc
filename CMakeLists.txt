cmake_minimum_required(VERSION 3.14)
project(ConsoleCalc LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(SKIP_INSTALL_ALL ON)
set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
set(SPDLOG_INSTALL OFF CACHE BOOL "" FORCE)
set(JSON_INSTALL OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Для GTest
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

find_package(PostgreSQL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

find_program(_PROTOBUF_PROTOC protoc)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)

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

set(PROTO_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})
set(PROTO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proto/calculator.proto")
set(GENERATED_PROTO_SRCS "${PROTO_GEN_DIR}/calculator.pb.cc")
set(GENERATED_PROTO_HDRS "${PROTO_GEN_DIR}/calculator.pb.h")
set(GENERATED_GRPC_SRCS "${PROTO_GEN_DIR}/calculator.grpc.pb.cc")
set(GENERATED_GRPC_HDRS "${PROTO_GEN_DIR}/calculator.grpc.pb.h")

add_custom_command(
    OUTPUT ${GENERATED_PROTO_SRCS} ${GENERATED_PROTO_HDRS} ${GENERATED_GRPC_SRCS} ${GENERATED_GRPC_HDRS}
    COMMAND ${_PROTOBUF_PROTOC} --cpp_out=${PROTO_GEN_DIR} --grpc_out=${PROTO_GEN_DIR} --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE} -I ${CMAKE_CURRENT_SOURCE_DIR}/proto ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
    COMMENT "Generating protobuf and gRPC code from ${PROTO_FILE}"
)

add_library(calc_grpc_proto STATIC
    ${GENERATED_PROTO_SRCS}
    ${GENERATED_GRPC_SRCS}
)

target_include_directories(calc_grpc_proto PUBLIC
    ${PROTO_GEN_DIR}
    ${Protobuf_INCLUDE_DIRS}
    ${gRPC_INCLUDE_DIRS}
)
target_link_libraries(calc_grpc_proto PUBLIC
    gRPC::grpc++
    gRPC::grpc++_reflection
    protobuf::libprotobuf
)

add_library(app_logic STATIC
    src/logger/Logger.cpp
    src/parser/JsonParser.cpp
    src/checker/Checker.cpp
    src/calculator/Calculator.cpp
    src/calculator/CachedCalculator.cpp
    src/printer/Printer.cpp
    src/runner/ConsoleRunner.cpp
    src/runner/ServerRunner.cpp
    src/models/DbConfig.cpp
    src/infrastructure/ConfigLoader.cpp
    src/infrastructure/ComponentFactory.cpp
    src/database/DbResult.cpp
    src/database/PostgresConnection.cpp
    src/database/repositories/HistoryRepository.cpp
    src/database/repositories/CachedHistoryRepository.cpp
    src/network/CalculatorServiceImpl.cpp
    src/utils/OperationUtils.cpp
    src/application/CalculatorApp.cpp
)

target_include_directories(app_logic PUBLIC
    include
    ${PostgreSQL_INCLUDE_DIRS}
    ${pvm_math_lib_SOURCE_DIR}/include
)
target_link_libraries(app_logic PRIVATE
    pvm_math_lib
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    PostgreSQL::PostgreSQL
    fmt::fmt
    calc_grpc_proto
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

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
if(ENABLE_TSAN)
    add_compile_options("-fsanitize=thread")
    add_link_options("-fsanitize=thread")
    message(STATUS "ThreadSanitizer enabled")
endif()

include(GNUInstallDirs)
install(TARGETS calculator RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES config/config.json DESTINATION /etc/calculator)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/app-calculator.service DESTINATION /lib/systemd/system)
install(DIRECTORY DESTINATION var/log)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "app-calculator")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_RELEASE "1")
set(CPACK_PACKAGE_CONTACT "Author <pochta@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION "gRPC Calculator Service")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libgrpc++, libprotobuf32t64, libstdc++6")

set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "")

set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

include(CPack)
