cmake_minimum_required(VERSION 3.8)

set(EvoNDZ_VERSION_MAJOR 0)
set(EvoNDZ_VERSION_MINOR 1)

project(EvoNDZ VERSION ${EvoNDZ_VERSION_MAJOR}.${EvoNDZ_VERSION_MINOR} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(THIRDPARTY_LIBS_DIR "Debug")
else()
    set(THIRDPARTY_LIBS_DIR "Release")
endif()

file(GLOB THIRDPARTY_LIBS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/third_party/lib/${THIRDPARTY_LIBS_DIR}/*.lib")

add_subdirectory("third_party/zGlad")
add_subdirectory("EvoNDZ")
add_subdirectory("EvoNDZ Test")

install(EXPORT EvoNDZTargets
  FILE EvoNDZTargets.cmake
  DESTINATION lib/cmake/EvoNDZ
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/EvoNDZConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/EvoNDZ"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/EvoNDZConfigVersion.cmake"
  VERSION "${EvoNDZ_VERSION_MAJOR}.${EvoNDZ_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)


install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/EvoNDZConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/EvoNDZConfigVersion.cmake
  DESTINATION lib/cmake/EvoNDZ
  )

export(EXPORT EvoNDZTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/EvoNDZTargets.cmake"
)