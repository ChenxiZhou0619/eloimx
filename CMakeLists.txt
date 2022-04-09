cmake_minimum_required(VERSION 3.13)

project(Eloimx LANGUAGES CXX)

set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/Linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/MacOS")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/Windows")
endif()

add_subdirectory(src ./out)
