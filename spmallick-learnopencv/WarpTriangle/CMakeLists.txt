cmake_minimum_required (VERSION 2.8)
project (WarpTriangle)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(warpTriangle warpTriangle.cpp)
target_link_libraries(warpTriangle ${OpenCV_LIBS})
set_target_properties(warpTriangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
