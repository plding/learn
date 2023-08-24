cmake_minimum_required(VERSION 3.0)
project(LearnOpenGL)

include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(/usr/local/include)

link_directories(/usr/local/Cellar/glfw/3.3.2/lib)

set(LIBS glfw)

set(CHAPTERS
    1.getting_started
)

set(1.getting_started
    1.1.hello_window
    1.2.hello_window_clear
    2.1.hello_triangle
    2.2.hello_triangle_indexed
    2.3.hello_triangle_exercise1
    2.4.hello_triangle_exercise2
    2.5.hello_triangle_exercise3
)

# first create relevant static libraries required for other projects
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
    endforeach(DEMO)
endforeach(CHAPTER)
