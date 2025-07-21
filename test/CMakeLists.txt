####################################################################################################
### Tests
enable_testing()

####################################################################################################
### Dependencies

if(CPPANVIL_BUILD_GTEST)
    message(CHECK_START "Fetching GTest")
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF)
    set(GTEST_HAS_ABSL OFF)
    FetchContent_MakeAvailable(googletest)
else()
    find_package(GTest REQUIRED)
endif()

####################################################################################################
### Test Executable

add_executable(tests
    "test_main.cpp"
    "nbt/test_types.cpp"
    "nbt/test_endtag.cpp"
    "nbt/test_bytetag.cpp"
    "nbt/test_bytearraytag.cpp"
    "nbt/test_listtag.cpp"
    "nbt/test_io.cpp"
    "util/test_compression.cpp"
)

target_include_directories(tests
    PRIVATE
        "${CPP_ANVIL_SOURCE_DIR}/include"
        "${CPP_ANVIL_SOURCE_DIR}/test"
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIRS}
)

target_link_libraries(tests 
    PRIVATE
        cppAnvil
        gtest
        gmock
)

set_target_properties(tests 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

if(UNIX)
    target_link_libraries(tests pthread)
endif()