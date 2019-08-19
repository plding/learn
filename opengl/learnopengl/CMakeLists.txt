cmake_minimum_required (VERSION 2.8)
project (LearnOpenGL)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# find the required packages
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(/usr/local/include)
include_directories(/usr/local/Cellar/glew/2.1.0/include)

link_directories(/usr/local/Cellar/glew/2.1.0/lib)
link_directories(/usr/local/Cellar/glfw/3.3/lib)

find_library(OpenGL_LIBRARY OpenGL)
set(LIBS ${OPENGL_LIBRARY} glew glfw)

set(CHAPTERS
    1.getting_started
)

set(1.getting_started
    1.1.hello_window
    1.2.hello_window_clear
    2.1.hello_triangle
    2.2.hello_triangle_indexed
)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

# first create relevant static libraries required for other projects
add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)

# then create a project file per tutorial
foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        file(GLOB SOURCE
            "src/${CHAPTER}/${DEMO}/*.h"
            "src/${CHAPTER}/${DEMO}/*.cpp"
        )
        set(NAME "${CHAPTER}__${DEMO}")
        add_executable(${NAME} ${SOURCE})
        target_link_libraries(${NAME} ${LIBS})
        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
        # copy shader files to build directory
        file(GLOB SHADERS
            "src/${CHAPTER}/${DEMO}/*.vs"
            "src/${CHAPTER}/${DEMO}/*.fs"
        )
        foreach(SHADER ${SHADERS})
            file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/${CHAPTER})
        endforeach(SHADER)
    endforeach(DEMO)
endforeach(CHAPTER)
