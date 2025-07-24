####################################################################################################
### Files

set(CPPANVIL_HEADER_PATH "${PROJECT_SOURCE_DIR}/include")
set(CPPANVIL_HEADERS
    # anvil
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/version.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/anvil.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/anvil/coordinates.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/anvil/chunk.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/anvil/region.hpp"
    # nbt
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/io.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/basic_tag.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/collection_tag.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/compound_tag.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/list_tag.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/primitive_tag.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/types.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/detail/floating_point.hpp"
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/nbt/detail/type_utilities.hpp"
    # util
    "${CPPANVIL_HEADER_PATH}/cpp-anvil/util/compression.hpp"
)

set(CPPANVIL_SOURCES
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

configure_file(
    version.cpp.in
    version.cpp
    @ONLY
)

####################################################################################################
### Library

if(CPPANVIL_BUILD_SHARED)
    add_library(CppAnvil SHARED
        ${CPPANVIL_SOURCES}
    )
else()
    add_library(CppAnvil STATIC
        ${CPPANVIL_SOURCES}
    )
endif()

add_library(CppAnvil::CppAnvil ALIAS CppAnvil)

target_include_directories(CppAnvil
    PUBLIC
        $<BUILD_INTERFACE:${CPPANVIL_HEADER_PATH}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${ZLIB_INCLUDE_DIRS}
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(CppAnvil
    PRIVATE
        ZLIB::ZLIB
)

set_target_properties(CppAnvil 
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME cppanvil
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}  # Execuatbles and DLL on windows
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}  # Shared libraries on non windows
)

target_sources(CppAnvil
    PUBLIC
        FILE_SET  public_headers
        TYPE      HEADERS
        BASE_DIRS ${CPPANVIL_HEADER_PATH}
        FILES     ${CPPANVIL_HEADERS}
)

####################################################################################################
### Install
include(GNUInstallDirs)

install(
    TARGETS     CppAnvil
    EXPORT      CppAnvilTargets
    LIBRARY     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE     DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME     DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET    public_headers
)

install(
    EXPORT      CppAnvilTargets
    FILE        CppAnvilTargets.cmake
    NAMESPACE   CppAnvil::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-anvil"
)

# Create Package Configuration File & Package Version File
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/CppAnvilConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CppAnvilConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-anvil"
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/CppAnvilConfigVersion.cmake"
    VERSION ${CppAnvil_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CppAnvilConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CppAnvilConfigVersion.cmake" 
    DESTINATION 
        "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-anvil"
)
