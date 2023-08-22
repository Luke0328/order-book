# Main CMakeLists
cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(OrderBook)

# DEPENDENCIES
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include_directories(include)

# LIBRARY

file(GLOB_RECURSE SOURCES "src/*.cpp")

list(REMOVE_ITEM SOURCES "src/main.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME}
  PRIVATE -Wall -Wextra -pedantic -g #-Werror
  )

target_compile_features(${PROJECT_NAME}
  PRIVATE cxx_std_17)

# EXECUTABLE

add_executable(${PROJECT_NAME}-exec "src/main.cpp")
target_link_libraries(${PROJECT_NAME}-exec PUBLIC ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME}-exec
  PRIVATE -Wall -Wextra -pedantic -g #-Werror
  )

target_compile_features(${PROJECT_NAME}-exec
  PRIVATE cxx_std_17)

# TESTS
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain ${PROJECT_NAME})

target_compile_options(tests
  PRIVATE -Wall -Wextra -pedantic -g #-Werror
  )

target_compile_features(tests
  PRIVATE cxx_std_17)