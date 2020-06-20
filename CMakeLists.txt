cmake_minimum_required(VERSION 3.16)
project(shadow_map)

set(CMAKE_MODULE_PATH /home/user/Libs/cmake)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)

include_directories(src ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDES_DIRS})

add_executable(shadow_map src/main.cpp src/glutils/shader.cc src/glutils/program.cc src/glutils/object.cc
                            src/error/marcherror.cc src/utils/matrix3.cc src/utils/vector3.cc src/utils/camera.cc
        src/utils/parser/parser.cc src/vertices.cc)

target_link_libraries(shadow_map ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLFW_STATIC_LIBRARIES} ${GLEW_LIBRARIES})