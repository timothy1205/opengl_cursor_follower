cmake_minimum_required(VERSION 3.18)
project(opengl_cursor_follower)
set(CMAKE_CXX_STANDARD 17)

set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.cpp glad/glad.c WindowRenderer.cpp WindowRenderer.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw OpenGL::GL glm ${CMAKE_DL_LIBS})

add_definitions(-DDEBUG_AUTO_CLOSE)

