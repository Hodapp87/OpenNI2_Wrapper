cmake_minimum_required (VERSION 2.6)
# N.B. This needs to point at the root of the source and I'm not sure if this is
# a good way to accomplish that.
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/" ${CMAKE_MODULE_PATH})
message(${CMAKE_MODULE_PATH})

project (Surfactant)
add_executable(Viewer Viewer.cpp main.cpp)
add_executable(OpenCL_example opencl_test.c)
add_library(openni2_c_wrapper SHARED openni2_c_wrapper.cpp)
add_executable(openni2_c_wrapper_test openni2_c_test.c)

# helpful: cmake --help-module FindGLUT
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

find_path(OPENNI2_INCLUDE_DIR OpenNI.h
          HINTS /usr/include/OpenNI2 /usr/local/include/OpenNI2
          PATH_SUFFIXES openni include Include)
find_library(OPENNI2_LIBRARY 
             NAMES OpenNI2${OPENNI_SUFFIX}
             HINTS /usr/lib /usr/local/lib
             PATH_SUFFIXES lib Lib Lib64)

include_directories(SYSTEM ${OPENNI2_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(Viewer ${OPENNI2_LIBRARY} ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY})
target_link_libraries(OpenCL_example ${OPENCL_LIBRARY})
target_link_libraries(openni2_c_wrapper_test openni2_c_wrapper ${OPENNI2_LIBRARY})
