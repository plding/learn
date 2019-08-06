cmake_minimum_required (VERSION 2.8)
project (FaceSwap)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(faceSwap faceSwap.cpp)
target_link_libraries(faceSwap ${OpenCV_LIBS})
set_target_properties(faceSwap PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
