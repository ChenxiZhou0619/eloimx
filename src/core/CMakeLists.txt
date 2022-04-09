# core
cmake_minimum_required(VERSION 3.13)
add_library(core ./frame.cpp ./math.cpp ./ray.cpp ./spectrum.cpp ./util.cpp warp.cpp)
target_include_directories(core PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(core PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(core embree3 fmt)