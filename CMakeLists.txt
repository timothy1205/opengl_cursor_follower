cmake_minimum_required(VERSION 3.18)
project(opengl_cursor_follower)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES main.cpp WindowRenderer.cpp WindowRenderer.h internal.h opengl.h config.h.in
  config.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

if (WIN32 OR MSVC)
    message(FATAL_ERROR "OS not supported...")
elseif (UNIX)
    # Currently only support x11
    message(STATUS "Compiling for UNIX x11")
    find_package(X11 REQUIRED)

    if (NOT X11_Xcomposite_FOUND)
        message(FATAL_ERROR "libXcomposite is required")
    elseif (NOT X11_Xext_FOUND)
        message(FATAL_ERROR "libXext is required")
    elseif (NOT X11_Xshape_FOUND)
        message(FATAL_ERROR "libXshape is required")
    endif()

    include_directories(SYSTEM ${X11_xcb_INCLUDE_PATH})
    include_directories(SYSTEM ${X11_Xfixes_INCLUDE_PATH})
    include_directories(SYSTEM ${X11_Xcomposite_INCLUDE_PATH})
    include_directories(SYSTEM ${X11_Xshape_INCLUDE_PATH})

    set(SOURCE_FILES ${SOURCE_FILES} x11_WindowRenderer.cpp x11_WindowRenderer.h)
    
    set(USE_X11 TRUE) # Later we should check the login-session for x11/wayland
endif()

configure_file(${CMAKE_CURRENT_LIST_DIR}/config.h.in 
    ${CMAKE_CURRENT_LIST_DIR}/config.h @ONLY)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

message(${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        OpenGL::GL
        glm
        ${CMAKE_DL_LIBS})

if (USE_X11)
  message(STATUS "Linking x11 libraries")
  target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
        ${X11_LIBRARIES}
        ${X11_Xfixes_LIB}
        ${X11_Xcomposite_LIB})
endif()

