cmake_minimum_required(VERSION 3.30)
project(firmware_shell C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG        master # or use release tag, eg. v4.0
        # FIND_PACKAGE_ARGS # Recent CMake versions can integrate FetchContent with find_package
        # https://cmake.org/cmake/help/latest/module/FetchContent.html#integrating-with-find-package
)

# Either set CPPUTEST_PLATFORM to off and # provide a project-specific
# platform.cpp, assign # one of the provided platforms under
# src/Platforms/ # (as shown below), or let CppUTest
# select an appropriate default.
# set(CPPUTEST_PLATFORM Gcc STRING BOOL "Platform implementation")

FetchContent_MakeAvailable(CppUTest)

add_executable(firmware_shell
        main.c
        shell/shell.c
        shell_commands.c
        impl_pc.c
)

target_include_directories( firmware_shell PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/shell
)

add_executable(firmware_shell_tests
        shell_commands.c
        impl_pc.c
        tests/main.cpp
        tests/shell_commands_test.cpp
)

target_link_libraries(firmware_shell_tests
        PRIVATE
        CppUTest::CppUTest
        #or CppUTest::CppUTestExt
)

target_include_directories(firmware_shell_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/shell
)

include(CTest) # Enable testing

# automatically discover CppUTest tests
include(CppUTest)
cpputest_discover_tests(firmware_shell_tests)
