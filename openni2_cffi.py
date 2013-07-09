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

class WalkAST(object):
    def __init__(self, files, prefix, classNames):
        self.files = files
        self.allHeaders = loadHeaders(files)
        self.prefix = prefix
        self.classNames = classNames
        self.parser = pycparser.c_parser.CParser()
        self.ast = self.parser.parse(self.allHeaders, filename='<none>')
    def resolvePtr(self, decl):
        if type(decl) == pycparser.c_ast.PtrDecl:
            return "*" + self.resolvePtr(decl.type)
        elif type(decl) == pycparser.c_ast.TypeDecl:
            return self.resolvePtr(decl.type)
        elif type(decl) == pycparser.c_ast.IdentifierType:
            if len(decl.names) != 1:
                raise Exception("Expected only one name for type!")
            return "%s" % (decl.names[0],)
        else:
            print("Unknown type:")
            decl.show()
    def genFunction(self):
        for ext in self.ast.ext:
            fn = CFunction()
            if (type(ext.type) != pycparser.c_ast.FuncDecl): continue
            fnType = ext.type
            fn.name = ext.name
            fn.returnType = self.resolvePtr(fnType.type.type)
            #print("  returns: %s" % self.resolvePtr(returnTypes))
            fn.argNames = []
            fn.argTypes = []
            if (fnType.args != None):
                for arg in fnType.args.params:
                    fn.argNames.append(arg.name)
                    fn.argTypes.append(self.resolvePtr(arg.type))
            yield fn
    def walk(self):
        for fn in self.genFunction():
            if not fn.name.startswith(self.prefix):
                continue
            newName = fn.name[len(self.prefix):]
            target = []
            #if newName.startswith("new"):
            #    good = True
            #if newName.startswith("delete"):
            #    good = True
            # First check is by function suffix.
            for class_ in self.classNames:
                suffix = "_" + class_
                if newName.endswith(suffix):
                    newName = fn.name[:-len(suffix)]
                    print(" * match %s by function suffix" % (fn.name,))
                    target.append(class_)
                    good = True
                    break
            # Next check is by first argument.
            if len(fn.argNames) > 0:
                target.append(fn.argTypes[0])
            if len(target) == 0:
                print(" - unknown function %s" % (newName,))
                parts = newName.split("_")
                if len(parts) > 1:
                    print(" - possible targets - %s?" % (parts[1:],))
            else:
                print("Found function %s for %s" % (newName, target))

class CFunction(object):
    def __init__(self):
        self.name = None
        self.argNames = None
        self.argTypes = None
        self.returnType = None

files = ["openni2_types_python.h", "openni2_types_c.h", "openni2_types.h", "openni2_wrapper.h"]
walk = WalkAST(files, "oni_", ["DeviceInfoArray", "VideoStream", "Device", "VideoModeArray", "Recorder", "VideoMode", "VideoFrameRef", "DeviceState", "ImageRegistrationMode", "SensorType", "PixelFormat", "Status", "PlaybackControl", "CameraSettings"])
walk.walk()
