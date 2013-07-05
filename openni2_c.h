// ============================================================================
// openni2_c.h: Entry point to the C interface for OpenNI2
// (c) Chris Hodapp, 2013
// ============================================================================

/*
This is a C wrapper to the OpenNI2 library, which has a C++ interface.  You
should be able to use this from clean C as well (i.e. if you are building C
code with a C++ compiler).

openni2_wrapper.h contains all function prototypes of interest.
openni2_types.h and openni2_types_c.h contain types for the C interface.

Rather than duplicate all the OpenNI2 documentation, everything tries to mimic
the OpenNI2 C++ interface as closely as possible, so the OpenNI2 documentation
(e.g. http://www.openni.org/wp-content/doxygen/html/annotated.html) may remain
the definitive source.

Every function name, type name, and constant name should match the naming in
OpenNI2, except for a few things:
 - Using a prefix of "oni_" rather than the "openni" namespace
 - Using a suffix of "_new" and "_delete" for constructor and destructor,
respectively.
 - Overloaded functions and name conflicts (e.g. isValid) are resolved with a
suffix of the class name.
 - enums are wrapped as extern ints.

*/

#include "openni2_types_c.h"
#include "openni2_wrapper.h"
