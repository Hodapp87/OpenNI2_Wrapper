from cffi import FFI
from cffi import cparser
from cffi.cparser import pycparser
import re

class Device:
    def __init__(self):
        OpenNI2.check_cffi()
        self.dev = OpenNI2.lib.oni_new_Device()
    def delete(self):
        OpenNI2.lib.oni_delete_Device(self.dev)
    def close(self):
        OpenNI2.lib.oni_close(self.dev)

class OpenNI2:
    ffi, lib = None, None
    @staticmethod
    def init_cffi():
        OpenNI2.ffi = FFI()
        files = ["openni2_types_python.h", "openni2_types_c.h", "openni2_types.h", "openni2_wrapper.h"]
        allHeaders = loadHeaders(files)
        OpenNI2.ffi.cdef(allHeaders)
        libName = "../OpenNI2_Wrapper_build/libopenni2_c_wrapper.so"
        print("Reading library %s..." % libName)
        OpenNI2.lib = OpenNI2.ffi.dlopen(libName)
    @staticmethod
    def check_cffi():
        if (OpenNI2.ffi == None or OpenNI2.lib == None):
            OpenNI2.init_cffi()
    @staticmethod
    def getVersion():
        return Version(OpenNI2.lib.oni_getVersion())
    @staticmethod
    def initialize():
        return OpenNI2.lib.oni_initialize()
    @staticmethod
    def getExtendedError():
        return OpenNI2.ffi.string(OpenNI2.lib.oni_getExtendedError())
    @staticmethod
    def shutdown():
        OpenNI2.lib.oni_shutdown()

class Version:
    def __init__(self, oni_Version):
        self.build = oni_Version.build
        self.maintenance = oni_Version.maintenance
        self.major = oni_Version.major
        self.minor = oni_Version.minor

def stripDirectives(fileObj):
    """stripDirectives: A generator that strips out anything that reads from the
    given file and strips out lines that are what look like compiler directives."""
    for line in fileObj:
        stripped = line.strip()
        if not stripped.startswith("#") and not 'extern "C"' in stripped:
            yield line

def loadHeaders(filenames):
    """Iterate through a list of filename of C headers, concatenate them, and
    attempt to strip out compiler directives as well.  Return the combined
    string."""
    header = []
    for fname in filenames:
        print("Reading %s..." % fname)
        with open(fname) as f:
            header.append("".join(list(stripDirectives(f))))
    return comment_remover("\n".join(header))

# Courtesy of http://stackoverflow.com/questions/16836878/pycparser-failed-on-comments
def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ""
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

OpenNI2.check_cffi()
lib,ffi = OpenNI2.lib, OpenNI2.ffi
ver = OpenNI2.getVersion()
print("v%d.%d, build %d maintenance %d" % (ver.major, ver.minor, ver.build, ver.maintenance))
rc = OpenNI2.initialize()
print("Init OpenNI2: %s" % (ffi.string(lib.oni_getString_Status(rc))))

files = ["openni2_types_python.h", "openni2_types_c.h", "openni2_types.h", "openni2_wrapper.h"]
allHeaders = loadHeaders(files)
parser = pycparser.c_parser.CParser()
ast = parser.parse(allHeaders, filename='<none>')
for ext in ast.ext:
    if (type(ext.type) != pycparser.c_ast.FuncDecl): continue
    name = ext.name
    print("name: %s" % name)
    if (ext.type.args != None):
        for arg in ext.type.args.params:
            print("  arg: %s" % arg.name)
            argtype = arg.type
            if (type(argtype) == pycparser.c_ast.PtrDecl):
                print("    pointer to: ")
                argtype.type.show()
            else:
                print("    %s" % argtype.type.names)
                #argtype.show()
            #arg.show()
    #ext.show()
