# bsdfs
cmake_minimum_required(VERSION 3.13)

add_library(bsdfs ./conductor.cpp ./dielectric.cpp ./diffuse.cpp ./mirror.cpp)
target_include_directories(bsdfs PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(bsdfs PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(bsdfs core render)