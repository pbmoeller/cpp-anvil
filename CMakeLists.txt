cmake_minimum_required(VERSION 3.24)

project(cpp_nbt
    VERSION     0.1.0
    LANGUAGES   C CXX
)

option(BUILD_EXAMPLES   "Build examples for cpp-anvil"      TRUE)
option(BUILD_TESTS      "Build unit tests for cpp-anvil"    TRUE)

### Version
set(CPPANVIL_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPPANVIL_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPPANVIL_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPPANVIL_VERSION ${CPPANVIL_VERSION_MAJOR}.${CPPANVIL_VERSION_MINOR}.${CPPANVIL_VERSION_PATCH})

### Additional flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ZLIB REQUIRED)

set(CPP_ANVIL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory("src")

### Build Examples
if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

### Build Unit Tests
if(BUILD_TESTS)
    add_subdirectory("test")
endif()
