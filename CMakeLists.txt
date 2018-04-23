cmake_minimum_required(VERSION 2.8)

project(octree)

add_subdirectory(lib/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

FILE(GLOB TEST_SRC tests/*.*)

add_executable(octreetests ${TEST_SRC})

target_link_libraries(octreetests gtest gtest_main)

add_test(NAME octreetests
         COMMAND octreetests)

