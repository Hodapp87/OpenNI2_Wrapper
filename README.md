OpenNI2_Wrapper
===============

This - so far - is a C interface to the OpenNI2 libraries (also on github as https://github.com/OpenNI/OpenNI2).  It targets versions 2.1.  This should also be usable via clean C as well (i.e. if you are building C code with a C++ compiler).

Usage & documentation notes:
* openni2_wrapper.h contains all function prototypes of interest.
* openni2_types.h and openni2_types_c.h contain types for the C interface.
* openni2_c.h is what you should actually #include when using it.
* openni2_c_test.c includes some usage examples.  The CMake build will create an executable for this, in addition to the library itself.
* Rather than duplicate all the OpenNI2 documentation, everything tries to mimic the OpenNI2 C++ interface as closely as possible, so the OpenNI2 documentation (e.g. http://www.openni.org/wp-content/doxygen/html/annotated.html) may remain the definitive source.

Every function name, type name, and constant name should match the naming in OpenNI2, except for a few things:
* Using a prefix of "oni_" rather than the "openni" namespace
* Using a suffix of "_new" and "_delete" for constructor and destructor, respectively.
* Overloaded functions and name conflicts (e.g. isValid) are resolved with a suffix of the class name.
* enums are wrapped as extern ints.

As far as unfinished parts go, I still have on my TODO list:
* Making this compatible with version 2.2 of OpenNI.
* Better error-handling.  The OpenNI2 documentation has little to say on this matter.
* More complete testing of everything.
* Building on a configuration besides GCC & Linux.
* Checking const-correctness (or at least shut the compiler up).
* Checking memory-management the best I can given the sparse documentation on the matter.

The repository was copied over from another larger project that had some other goals in mind, so some of the history might be odd, at least until I clean parts of it up.
