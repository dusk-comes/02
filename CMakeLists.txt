cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(gcc_lik_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
set(RESOURCE_FILES ip_filter.tsv)

project(Filter_IP)

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
