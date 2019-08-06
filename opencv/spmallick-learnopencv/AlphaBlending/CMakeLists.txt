cmake_minimum_required (VERSION 2.8)
project (AlphaBlending)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(AlphaBlending AlphaBlend.cpp)
target_link_libraries(AlphaBlending ${OpenCV_LIBS})
set_target_properties(AlphaBlending PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
