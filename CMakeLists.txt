cmake_minimum_required(VERSION 3.21)

project(HelloWorld VERSION 1.0.0 LANGUAGES CXX)

set(BUILD_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/commonlibsse-ng EXCLUDE_FROM_ALL)
include(lib/commonlibsse-ng/cmake/CommonLibSSE.cmake)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES plugin.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)

if(NOT DEFINED ENV{SKYRIM_MODS_DIR})
    message(FATAL_ERROR "SKYRIM_MODS_DIR environment variable is not set")
endif()

set(OUTPUT_DIR "$ENV{SKYRIM_MODS_DIR}/${PROJECT_NAME}/SKSE/Plugins")
add_custom_command(
    TARGET "${PROJECT_NAME}"
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${OUTPUT_DIR}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    VERBATIM
)
