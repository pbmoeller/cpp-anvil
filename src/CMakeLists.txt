
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

configure_file(
    version.cpp.in
    version.cpp
    @ONLY
)

set(CPP_ANVIL_HEADER_PATH "${CPP_ANVIL_SOURCE_DIR}/include")
set(CPP_ANVIL_HEADERS
    # anvil
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/version.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/anvil.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/anvil/coordinates.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/anvil/chunk.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/anvil/region.hpp"
    # nbt
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/io.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/basic_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/collection_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/compound_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/list_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/primitive_tag.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/types.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/detail/floating_point.hpp"
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/nbt/detail/type_utilities.hpp"
    # util
    "${CPP_ANVIL_HEADER_PATH}/cpp-anvil/util/compression.hpp"
)

# lib
add_library(cppAnvil SHARED
    ${CPP_ANVIL_HEADERS}
    "anvil/chunk.cpp"
    "anvil/coordinates.cpp"
    "anvil/region.cpp"
    "anvil/region_header.cpp"
    "util/compression.cpp"
    "nbt/io.cpp"
    "nbt/list_tag.cpp"
    "nbt/compound_tag.cpp"
    "nbt/types.cpp"
    "version.cpp"
)

target_include_directories(cppAnvil
    PRIVATE 
        ${ZLIB_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CPP_ANVIL_HEADER_PATH}>
        $<INSTALL_INTERFACE:${cpp_nbt_INSTALL_INCLUDE_DIR}>
)
target_link_libraries(cppAnvil
    PRIVATE
        zlibstatic
)

set_target_properties(cppAnvil 
    PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

### Install
install(TARGETS cppAnvil 
    EXPORT cppAnvilTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(EXPORT cppAnvilTargets
    FILE cppAnvilTargets.cmake
    NAMESPACE cppAnvil::
    DESTINATION "lib/${cpp_nbt_VERSION}/${CMAKE_BUILD_TYPE}"
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "cppAnvilConfigVersion.cmake"
    VERSION ${cpp_nbt_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(DIRECTORY ${CPP_ANVIL_HEADER_PATH}/cpp-anvil
    DESTINATION include
)
install(FILES 
        "${PROJECT_SOURCE_DIR}/cmake/cppAnvilConfig.cmake"
        "${PROJECT_BINARY_DIR}/src/cppAnvilConfigVersion.cmake" 
    DESTINATION 
        "lib/${cpp_nbt_VERSION}/${CMAKE_BUILD_TYPE}"
)
