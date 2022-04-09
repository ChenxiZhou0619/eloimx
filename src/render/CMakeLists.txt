# render
cmake_minimum_required(VERSION 3.13)

add_library(render ./common.cpp ./emitter.cpp ./integrator.cpp ./intersection.cpp ./perspective.cpp ./renderjob.cpp ./sampler.cpp ./scene.cpp ./shape.cpp)
target_include_directories(render PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(render PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(render core)