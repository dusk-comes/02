cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(gcc_lik_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(RESOURCE_FILES ip_filter.tsv)

project(ip_filter VERSION ${PROJECT_VERSION})

file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ip_filter ip_filter.cpp functions.cpp)

add_custom_target(test_hash
    COMMAND cat ${RESOURCE_FILES} | ./ip_filter | md5sum
    DEPENDS ${RESOURCE_FILES} ip_filter)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

target_compile_options(ip_filter INTERFACE
    "$<${gcc_like_cxx}:-Wall -Wextra -pedantic -Werror>"
    "$<${msvc_cxx}:-W4")

install(TARGETS ip_filter RUNTIME DESTINATION bin)

message(STATUS "version: ${PROJECT_VERSION}")

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT dusk-comes@email.com)
include(CPack)
