cmake_minimum_required (VERSION 2.8)
project (OpenCV3-beginning)

# find the required packages
find_package(OpenCV REQUIRED)

set(CHAPTERS
    ch01
    ch03
    ch05
    ch06
    ch07
    ch08
    ch09
)

include_directories(${OpenCV_INCLUDE_DIRS})

set(LIBS ${OpenCV_LIBS})

foreach(CHAPTER ${CHAPTERS})
    file(GLOB SOURCES ${CHAPTER}/*.cpp)
    foreach(SOURCE ${SOURCES})
        get_filename_component(TARGET ${SOURCE} NAME_WE)
        add_executable(${TARGET} ${SOURCE})
        target_link_libraries(${TARGET} ${LIBS}) 
        set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CHAPTER})
    endforeach(SOURCE)
endforeach(CHAPTER)
