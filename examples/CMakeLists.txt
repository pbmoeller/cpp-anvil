add_executable(loadfile_example
    "loadfile.cpp"
)

target_link_libraries(loadfile_example 
    PRIVATE
        cpp_anvil
        ${GTEST_LIBRARIES}
)

set_target_properties(loadfile_example 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_executable(test_stuff
    "teststuff.cpp"
)

target_link_libraries(test_stuff 
    PRIVATE
        cpp_anvil
        ${GTEST_LIBRARIES}
)

set_target_properties(test_stuff 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)