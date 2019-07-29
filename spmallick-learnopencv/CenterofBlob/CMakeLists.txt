cmake_minimum_required (VERSION 2.8)
project (CenterofBlob)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SOURCES *.cpp)
foreach(SOURCE ${SOURCES})
    get_filename_component(TARGET ${SOURCE} NAME_WE)
    add_executable(${TARGET} ${SOURCE})
    target_link_libraries(${TARGET} ${OpenCV_LIBS})
    set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endforeach(SOURCE)
