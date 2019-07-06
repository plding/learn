cmake_minimum_required (VERSION 2.8)
project (OpenCV3-beginning)

# find the required packages
find_package(OpenCV REQUIRED)

set(CHAPTERS
    1.beginning
    3.highgui
    5.core
    6.proc
    7.transform
    8.contours
)

set(1.beginning
    1.image
    2.erode
    3.blur
    4.canny
    5.video
)

set(3.highgui
    1.write    
    2.mixed
    3.trackbar
)

set(5.core
    1.pointer
    2.iterator
    3.at
    4.roi
    5.linear
    6.roi_linear
    7.multi-channels
    8.contrast-bright
)

set(6.proc
    1.box-filter
    2.blur
    3.gaussian-blur
    4.linear-blur
    dilate-and-erode
    open-and-close
    resize
)

set(7.transform
    canny
)

set(8.contours
    findContours
)

include_directories(${OpenCV_INCLUDE_DIRS})

set(LIBS ${OpenCV_LIBS})

foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        set(TARGET_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
        file(GLOB SOURCE
            "src/${CHAPTER}/${DEMO}/*.h"
            "src/${CHAPTER}/${DEMO}/*.cpp"
        )
        add_executable(${DEMO} ${SOURCE})
        target_link_libraries(${DEMO} ${LIBS}) 
        set_target_properties(${DEMO} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR})
        file(GLOB RESOURCES
            "src/${CHAPTER}/${DEMO}/*.jpg"
            "src/${CHAPTER}/${DEMO}/*.png"
            "src/${CHAPTER}/${DEMO}/*.avi"
        )
        foreach(RESOURCE ${RESOURCES})
            file(COPY ${RESOURCE} DESTINATION ${TARGET_DIR})
        endforeach(RESOURCE)
    endforeach(DEMO)
endforeach(CHAPTER)
