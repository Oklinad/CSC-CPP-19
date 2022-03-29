cmake_minimum_required(VERSION 3.15)
project(hasher)

#set(CMAKE_CXX_STANDARD 14)

#add_executable(hasher src/main.cpp src/hash/crc32.cpp src/hash/crc32.h src/hash/sum32.cpp src/hash/sum32.h src/tests/hash_unittest.cpp)

#
# library with common functions for tests and exe
#
add_library(hash
        src/hash/crc32.cpp
        src/hash/crc32.h
        src/hash/sum32.cpp
        src/hash/sum32.h)

set_target_properties(hash PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS ON)
#
# project itself
#
add_executable(hasher src/main.cpp)

set_target_properties(hasher PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS ON)

add_dependencies(hasher hash)
target_link_libraries(hasher hash)

#
# unit tests
#

# download googletest
configure_file(CMakeLists.txt.gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# prevent overriding the parent project's compiler/linker on windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# add googletest to build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_executable(hash_unittests
        src/tests/hash_unittest.cpp)

set_target_properties(hash_unittests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS ON)

target_include_directories(hash_unittests PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src/include")

add_dependencies(hash_unittests hash)
target_link_libraries(hash_unittests hash gtest_main)