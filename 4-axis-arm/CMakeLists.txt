cmake_minimum_required(VERSION 3.0)
project(processing-cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(
  include
)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

add_executable(processing-cpp src/main.cpp src/sketch.cpp src/psketch.cpp src/FourAxisArm.cpp)
target_link_libraries(processing-cpp glfw OpenGL::GL)
