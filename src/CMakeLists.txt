
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CPP_ANVIL_HEADER_PATH "${CPP_ANVIL_SOURCE_DIR}/include")
set(CPP_ANVIL_HEADERS
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/io/io.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/io/compression.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/io/nbt_byte_stream.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/basic_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/collection_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/compound_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/list_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/primitive_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/types.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/detail/floating_point.hpp"
)

# lib
add_library(cpp_anvil SHARED
    ${CPP_ANVIL_HEADERS}
    "io/compression.cpp"
    "io/io.cpp"
    "nbt/list_tag.cpp"
    "nbt/types.cpp"
)

target_include_directories(cpp_anvil
    PRIVATE ${ZLIB_INCLUDE_DIRS}
    PUBLIC $<BUILD_INTERFACE:${CPP_ANVIL_HEADER_PATH}>
           # $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
           # $<INSTALL_INTERFACE:${AwesomeMC_INSTALL_INCLUDE_DIR}>
)
target_link_libraries(cpp_anvil
    PRIVATE
        ${ZLIB_LIBRARIES}
)

set_target_properties(cpp_anvil 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)