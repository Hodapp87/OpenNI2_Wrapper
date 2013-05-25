cmake_minimum_required (VERSION 2.6)
project (KinfuReplacementNeedsRenaming)
add_executable(Viewer Viewer.cpp main.cpp)

# helpful: cmake --help-module FindGLUT
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

find_path(OPENNI2_INCLUDE_DIR OpenNI.h
          HINTS /usr/include/OpenNI2 /usr/local/include/OpenNI2
          PATH_SUFFIXES openni include Include)
find_library(OPENNI2_LIBRARY 
             NAMES OpenNI2${OPENNI_SUFFIX}
             HINTS /usr/lib /usr/local/lib
             PATH_SUFFIXES lib Lib Lib64)

include_directories(SYSTEM ${OPENNI2_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(Viewer ${OPENNI2_LIBRARY} ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY})

#	CFLAGS += -DUNIX -DGLX_GLXEXT_LEGACY
#	USED_LIBS += glut GL
#endif

#USED_LIBS += OpenNI2
