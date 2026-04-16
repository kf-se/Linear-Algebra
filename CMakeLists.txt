cmake_minimum_required(VERSION 3.16)
project(Vector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(vector Vector.cc Matrix.cc)

# Testing
include(CTest)  # calls enable_testing() and adds BUILD_TESTING option

if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
  )
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  add_executable(vector_test Vector_test.cc)
  target_link_libraries(vector_test PRIVATE GTest::gtest_main)
  gtest_discover_tests(vector_test)

  add_executable(matrix_test Matrix_test.cc)
  target_link_libraries(matrix_test PRIVATE GTest::gtest_main)
  gtest_discover_tests(matrix_test)
endif()
