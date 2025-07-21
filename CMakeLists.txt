####################################################################################################
### Project
cmake_minimum_required(VERSION 3.24)

project(cpp_anvil
    VERSION     0.1.0
    LANGUAGES   C CXX
)

# Options
option(BUILD_EXAMPLES       "Build examples for cpp-anvil"      TRUE)
option(BUILD_TESTS          "Build unit tests for cpp-anvil"    TRUE)
option(CPPANVIL_BUILD_ZLIB  "Fetch ZLIB library"                TRUE)
option(CPPANVIL_BUILD_GTEST "Fetch googletest library"          TRUE)

# Version
set(CPPANVIL_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPPANVIL_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPPANVIL_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPPANVIL_VERSION ${CPPANVIL_VERSION_MAJOR}.${CPPANVIL_VERSION_MINOR}.${CPPANVIL_VERSION_PATCH})

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################################################################################
### Dependencies

include(FetchContent)
set(BUILD_TESTING OFF)

if(CPPANVIL_BUILD_ZLIB)
    message(CHECK_START "Fetching ZLIB")
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/ZLIB.git
        GIT_TAG "v1.3.1"
        GIT_SHALLOW TRUE
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(zlib)
else()
    find_package(ZLIB REQUIRED)
endif()

set(CPP_ANVIL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

####################################################################################################
### Project Files

add_subdirectory("src")

### Examples
if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

### Unit Tests
if(BUILD_TESTS)
    add_subdirectory("test")
endif()
