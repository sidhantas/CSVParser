cmake_minimum_required(VERSION 3.14)
project(csv)
set(SRC_DIR src)
set(TEST_DIR tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)

FetchContent_MakeAvailable(fmt)
include_directories(./include)

enable_testing()
file(GLOB TESTS "${SRC_DIR}/*.cpp" "${SRC_DIR}/*/*.cpp" "${TEST_DIR}/*.cpp")
configure_file(${TEST_DIR}/test1.csv test1.csv COPYONLY)
add_executable(csv_test ${TESTS})
target_link_libraries(csv_test 
  PRIVATE 
    gtest_main 
    fmt::fmt 
)
include(GoogleTest)
gtest_discover_tests(csv_test)