####################################################################################################
### Project
cmake_minimum_required(VERSION 3.24)

project(CppAnvil
    VERSION     0.1.0
    LANGUAGES   CXX
)

# Options
option(CPPANVIL_BUILD_EXAMPLES  "Build examples for cpp-anvil"      TRUE)
option(CPPANVIL_BUILD_TESTS     "Build unit tests for cpp-anvil"    TRUE)
option(CPPANVIL_BUILD_GTEST     "Fetch googletest library"          FALSE)
option(CPPANVIL_BUILD_SHARED    "Build shared libraries"            TRUE)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

####################################################################################################
### Dependencies

find_package(ZLIB REQUIRED)

####################################################################################################
### Project Files

### Library
add_subdirectory("src")

### Examples
if(CPPANVIL_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

### Unit Tests
if(CPPANVIL_BUILD_TESTS)
    add_subdirectory("test")
endif()
