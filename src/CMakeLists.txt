# src
cmake_minimum_required(VERSION 3.13)

#add_library(liball ./integrators/path.cpp ./libcore/frame.cpp ./libcore/math.cpp ./libcore/ray.cpp ./librender/integrator.cpp ./librender/perspective.cpp ./librender/renderjob.cpp ./librender/shape.cpp ./librender/intersection.cpp ./bsdfs/diffuse.cpp ./librender/emitter.cpp ./libcore/spectrum.cpp ./librender/common.cpp ./librender/sampler.cpp ./librender/scene.cpp ./libcore/warp.cpp ./libcore/util.cpp ./bsdfs/dielectric.cpp ./bsdfs/mirror.cpp ./bsdfs/conductor.cpp ./texture/bitmap.cpp ./texture/constmap.cpp)
#target_include_directories(liball PUBLIC "..\\include")
#target_link_directories(liball PUBLIC ${PROJECT_LIB_DIR})
#target_link_libraries(liball fmt embree3)

add_subdirectory(core)

add_subdirectory(render)

add_subdirectory(bsdfs)

add_subdirectory(integrators)

add_subdirectory(texture)

add_library(demoJob demoJob.cpp)
target_include_directories(demoJob PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(demoJob PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(demoJob core render bsdfs integrators texture)

add_executable(eloimx main.cpp)
target_include_directories(eloimx PUBLIC ${PROJEC_INCLUDE_DIR})
target_link_libraries(eloimx demoJob)
