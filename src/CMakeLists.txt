# src
cmake_minimum_required(VERSION 3.23)

#add_library(libcore ./libcore/math.cpp ./libcore/ray.cpp ./libcore/frame.cpp)
#target_include_directories(libcore PUBLIC "..\\include")
#target_link_directories(libcore PUBLIC "..\\lib")
#target_link_libraries(libcore fmt)

#add_library(librender ./librender/perspective.cpp ./librender/shape.cpp ./librender/integrator.cpp ./librender/renderjob.cpp ./libcore/ray.cpp)
#target_include_directories(librender PUBLIC "..\\include")
#target_link_directories(librender PUBLIC "..\\lib")
#target_link_libraries(librender fmt embree3 libcore)

add_library(liball ./integrators/path.cpp ./libcore/frame.cpp ./libcore/math.cpp ./libcore/ray.cpp ./librender/integrator.cpp ./librender/perspective.cpp ./librender/renderjob.cpp ./librender/shape.cpp ./librender/intersection.cpp ./bsdfs/diffuse.cpp ./librender/emitter.cpp ./libcore/spectrum.cpp ./librender/common.cpp ./librender/sampler.cpp ./librender/scene.cpp ./libcore/warp.cpp ./libcore/util.cpp ./bsdfs/dielectric.cpp ./bsdfs/mirror.cpp ./bsdfs/conductor.cpp)
target_include_directories(liball PUBLIC "..\\include")
target_link_directories(liball PUBLIC "..\\lib")
target_link_libraries(liball fmt embree3)


add_library(demoJob demoJob.cpp)
target_include_directories(demoJob PUBLIC "..\\include")
target_link_directories(demoJob PUBLIC "..\\lib")
target_link_libraries(demoJob liball)

#add_library(demo_embree demo_embree.cpp)
#target_include_directories(demo_embree PUBLIC "..\\include")
#target_link_directories(demo_embree PUBLIC "..\\lib")
#target_link_libraries(demo_embree liball)

add_executable(eloimx main.cpp)
target_include_directories(eloimx PUBLIC "..\\include")
target_link_libraries(eloimx demoJob)
