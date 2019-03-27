cmake_minimum_required(VERSION 3.13)
project(6502_emulator)

set(CMAKE_CXX_STANDARD 14)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

file(GLOB_RECURSE test_src "test/**.h" "test/**.cpp" "src/**.h" "src/**.cpp")
list(FILTER test_src EXCLUDE REGEX ".*/6502-emulator/src/main.cpp$")
add_executable(6502_emulator_test ${test_src})
target_link_libraries(6502_emulator_test gtest_main)
add_test(NAME run_tests COMMAND 6502_emulator_test)

file(GLOB_RECURSE emulator_src "src/**.h" "src/**.cpp")
add_executable(6502_emulator ${emulator_src})
