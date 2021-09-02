cmake_minimum_required(VERSION 3.14)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Lists.cmake)

add_library(EvoNDZ ${EvoNDZ_SRC})

target_include_directories(EvoNDZ PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_SOURCE_DIR}/third_party/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(EvoNDZ PUBLIC zGlad)

target_precompile_headers(EvoNDZ PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/pch.h")

set(INSTALLED_LIBS EvoNDZ zGlad)

install(TARGETS ${INSTALLED_LIBS}
    DESTINATION lib
    EXPORT EvoNDZTargets
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/EvoNDZ" DESTINATION include)