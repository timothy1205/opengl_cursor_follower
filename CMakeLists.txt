# TODO: Restructure to allow for more than just X11

cmake_minimum_required(VERSION 3.18)
project(opengl_cursor_follower)
set(CMAKE_CXX_STANDARD 17)

set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.cpp WindowRenderer.cpp WindowRenderer.h x11_WindowRenderer.cpp x11_WindowRenderer.h internal.h opengl.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(X11 REQUIRED)

if (NOT X11_Xcomposite_FOUND)
    message(FATAL_ERROR "libXcomposite is required")
elseif (NOT X11_Xext_FOUND)
    message(FATAL_ERROR "libXext is required")
elseif (NOT X11_Xshape_FOUND)
    message(FATAL_ERROR "libXshape is required")
endif ()

message(${X11_Xfixes_INCLUDE_PATH})
message(${X11_xcb_xfixes_LIB})

include_directories(SYSTEM ${X11_xcb_INCLUDE_PATH})
include_directories(SYSTEM ${X11_Xfixes_INCLUDE_PATH})
include_directories(SYSTEM ${X11_Xcomposite_INCLUDE_PATH})
include_directories(SYSTEM ${X11_Xshape_INCLUDE_PATH})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        OpenGL::GL
        glm
        ${X11_LIBRARIES}
        ${X11_Xfixes_LIB}
        ${X11_Xcomposite_LIB}
        ${CMAKE_DL_LIBS})

set(_USE_X11 TRUE)

add_definitions(-D_USE_X11)
add_definitions(-DDEBUG_AUTO_CLOSE)

