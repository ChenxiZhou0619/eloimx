# texture
cmake_minimum_required(VERSION 3.13)

add_library(texture ./bitmap.cpp ./constmap.cpp)
target_include_directories(texture PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_directories(texture PUBLIC ${PROJECT_LIB_DIR})
target_link_libraries(texture core render)