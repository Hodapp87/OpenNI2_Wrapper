cmake_minimum_required (VERSION 2.6)
# N.B. This needs to point at the root of the source and I'm not sure if this is
# a good way to accomplish that.

project (OpenNI2_Wrapper)
add_library(openni2_c_wrapper SHARED openni2_wrapper.cxx)
add_executable(openni2_c_wrapper_test openni2_c_test.c)

find_path(OPENNI2_INCLUDE_DIR OpenNI.h
          HINTS /usr/include/OpenNI2 /usr/local/include/OpenNI2
          PATH_SUFFIXES openni include Include)
find_library(OPENNI2_LIBRARY 
             NAMES OpenNI2${OPENNI_SUFFIX}
             HINTS /usr/lib /usr/local/lib
             PATH_SUFFIXES lib Lib Lib64)

# We output some paths here for the Python:
set(PYTHON_GENERATED "openni2_paths.py")
file(WRITE openni2_paths.py "#!/usr/bin/env python\n")
# Do I need library path if the user installs this library to a standard place
# like /usr/local/lib?  ffi.dlopen might handle it okay there.
#file(APPEND "library_path = 

include_directories(SYSTEM ${OPENNI2_INCLUDE_DIR})
target_link_libraries(openni2_c_wrapper ${OPENNI2_LIBRARY})
target_link_libraries(openni2_c_wrapper_test openni2_c_wrapper ${OPENNI2_LIBRARY})
