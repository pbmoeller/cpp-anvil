cmake_minimum_required(VERSION 3.24)

project(cpp_nbt
    VERSION     0.1.0
    LANGUAGES   C CXX
)

option(BUILD_TESTS "Build unit tests for cpp-anvil" TRUE)

### Additional flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ZLIB REQUIRED)

set(CPP_ANVIL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("src")

### Build Unit Tests
if(BUILD_TESTS)
    add_subdirectory("test")
endif()