from cffi import FFI

def stripDirectives(fileObj):
    """stripDirectives: A generator that strips out anything that reads from the
    given file and strips out lines that are what look like compiler directives."""
    for line in fileObj:
        stripped = line.strip()
        if not stripped.startswith("#") and not 'extern "C"' in stripped:
            yield line

def loadHeaders(ffi, filenames):
    """Iterate through a list of filename of C headers and load them with the 
    given cffi.FFI instance.
    This will attempt to strip out compiler directives too."""
    header = []
    for fname in filenames:
        print("Reading %s..." % fname)
        with open(fname) as f:
            header.append("".join(list(stripDirectives(f))))
    allHeaders = "\n".join(header)
    ffi.cdef(allHeaders)

def init_openni2():
    ffi = FFI()
    files = ["openni2_types_c.h", "openni2_types.h", "openni2_wrapper.h"]
    loadHeaders(ffi, files)
    libName = "../OpenNI2_Wrapper_build/libopenni2_c_wrapper.so"
    print("Reading library %s..." % libName)
    lib = ffi.dlopen(libName)
    return lib,ffi

lib,ffi = init_openni2()
ver = lib.oni_getVersion()
print("v%d.%d, build %d maintenance %d" % (ver.major, ver.minor, ver.build, ver.maintenance))
rc = lib.oni_initialize()
print("Init OpenNI2: %s" % (ffi.string(lib.oni_getString_Status(rc))))
