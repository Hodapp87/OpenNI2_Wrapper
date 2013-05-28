# Courtesy of Michael Wild

set(CMAKE_FIND_FRAMEWORK FIRST)

find_path(OPENCL_INCLUDE_DIR NAMES OpenCL/cl.h CL/cl.h PATHS
   ENV OPENCLROOT
   PATH_SUFFIXES include include/nvidia-current)

find_library(OPENCL_LIBRARY OpenCL PATHS
   ENV OPENCLROOT
   PATH_SUFFIXES lib/x86_64 lib/x64 lib/x86)

#mark_as_advanced(OPENCL_INCLUDE_DIR OPENCL_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenCL OPENCL_INCLUDE_DIR 
OPENCL_LIBRARY)

set(OPENCL_INCLUDE_DIRS "${OPENCL_INCLUDE_DIR}")
set(OPENCL_LIBRARIES "${OPENCL_LIBRARY}")
