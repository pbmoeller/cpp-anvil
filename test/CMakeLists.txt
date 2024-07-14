enable_testing()
find_package(GTest REQUIRED)

add_executable(tests
    "test_main.cpp"
    "nbt/test_types.cpp"
    "nbt/test_endtag.cpp"
    "nbt/test_bytetag.cpp"
    "nbt/test_bytearraytag.cpp"
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
        cpp_anvil
        ${GTEST_LIBRARIES}
)

set_target_properties(tests 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

if(UNIX)
    target_link_libraries(tests pthread)
endif()