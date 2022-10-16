cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(gcc_lik_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

project(Filter_IP)

add_executable(ip_filter ip_filter.cpp functions.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


target_compile_options(ip_filter INTERFACE
    "$<${gcc_like_cxx}:-Wall -Wextra -pedantic -Werror>"
    "$<${msvc_cxx}:-W4"
)
