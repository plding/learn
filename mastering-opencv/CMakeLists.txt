cmake_minimum_required (VERSION 2.8)
project (Mastering-OpenCV)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# find the required packages
find_package(OpenCV REQUIRED)

set(PROJECTS
    ANPR
)

include_directories(${OpenCV_INCLUDE_DIRS})

set(LIBS ${OpenCV_LIBS})

foreach(PROJECT ${PROJECTS})
    file(GLOB SOURCES ${PROJECT}/*.cpp ${PROJECT}/*.hpp ${PROJECT}/*.h)
    add_executable(${PROJECT} ${SOURCES})
    target_link_libraries(${PROJECT} ${LIBS})
    set_target_properties(${PROJECT}
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT}/data
         DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT})
endforeach(PROJECT)
