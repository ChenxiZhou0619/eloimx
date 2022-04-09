# integrators
cmake_minimum_required(VERSION 3.13)

add_library(integrators ./path.cpp)
target_include_directories(integrators PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(integrators PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(integrators core render)