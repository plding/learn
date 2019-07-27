cmake_minimum_required (VERSION 2.8)
project (Delaunay)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(delaunay delaunay.cpp)
target_link_libraries(delaunay ${OpenCV_LIBS})
set_target_properties(delaunay PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
