cmake_minimum_required(VERSION 3.16)
project(Vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(vector Vector.cc)

# Testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(vector_test Vector_test.cc)
target_link_libraries(vector_test GTest::gtest_main)

add_test(NAME vector_test COMMAND vector_test)
