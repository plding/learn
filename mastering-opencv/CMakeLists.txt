cmake_minimum_required (VERSION 2.8)
project (Mastering-OpenCV)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# find the required packages
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(LIBS ${OpenCV_LIBS})

# ANPR
add_executable(ANPR ANPR/main.cpp ANPR/Plate.cpp ANPR/Plate.h ANPR/DetectRegions.cpp ANPR/DetectRegions.h
                    ANPR/OCR.cpp ANPR/OCR.h)
add_executable(trainSVM ANPR/trainSVM.cpp)
target_link_libraries(ANPR ${LIBS})
target_link_libraries(trainSVM ${LIBS})
set_target_properties(ANPR trainSVM PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ANPR)
