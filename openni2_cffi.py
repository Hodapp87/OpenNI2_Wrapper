from cffi import FFI
from cffi import cparser
from cffi.cparser import pycparser
import re

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

class CFunction(object):
    """A class storing some information about a C function:
    name -- Its name (as C sees it)
    argNames -- List of names of its arguments
    argTypes -- List of CType objects which are argument types for 'argNames'
    returnType -- Return type as a single CType object
    call -- The function object representing this call (e.g. for cffi)"""
    def __init__(self):
        self.name = None
        self.argNames = None
        self.argTypes = None
        self.returnType = None
        self.call = None

class CType(object):
    """A class representing - in a very simplistic way - a type in C. The field
    'baseType' stores a string containing the base type's name (i.e. ignoring
    any pointers), and 'pointers' is a non-negative integer which gives the
    number of pointer references; e.g. for int** it would be 2."""
    def __init__(self, baseType):
        self.baseType = baseType
        self.pointers = 0
    def pointerTo(self):
        """Return a new CType that corresponds with a pointer to the given type.
        e.g. For cint = CType("int"), cint.pointerTo() is an int*."""
        ptr = CType(self.baseType)
        ptr.pointers = self.pointers + 1
        return ptr
    def __str__(self):
        # TODO Make __unicode__ . . . 
        return self.baseType + ("*"*self.pointers)

# Courtesy of http://stackoverflow.com/questions/16836878/pycparser-failed-on-comments
def comment_remover(text):
    """Process C/C++/Java source code given as a string in 'text', and return
    a string which has the same text after removing all comments formed with //
    or /*...*/."""
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

class WalkAST(object):
    """The point of this class is to walk through the declarations in C headers,
    and get sufficient information to generate a wrapper from the names and
    signatures. It assumes that the C declarations follow a pattern that is
    something like:
    some_type prefix_functionName_classType(prefix_classType * self, arg1, ...);
    for a call that translates to something in Python like:
    self.functionName(arg1, ...).
    The call 'generateClasses' actually generates these wrappers, given a CFFI
    object which wraps the library from a dlopen call."""
    # TODO Explain more about 'classNames'.
    def __init__(self, files, prefix, classNames):
        """'files' is a list of filenames of C headers; they will be immediately
        parsed. 'prefix' is a string that gives the prefix all of the declared
        functions contain, as some sort of half-assed namespacing strategy.
        'classNames' is a list of class names that this will seek out in some
        other functions."""
        # TODO Better example here
        self.files = files
        self.allHeaders = loadHeaders(files)
        self.prefix = prefix
        self.classNames = classNames
        self.parser = pycparser.c_parser.CParser()
        self.ast = self.parser.parse(self.allHeaders, filename='<none>')
    def resolvePtr(self, decl):
        """Attempt to resolve, into a CType instance, the C type that the given
        Decl/Type node from pycparser represents."""
        # TODO Be more specific about what you pass in.
        if type(decl) == pycparser.c_ast.PtrDecl:
            return self.resolvePtr(decl.type).pointerTo()
        elif type(decl) == pycparser.c_ast.TypeDecl:
            return self.resolvePtr(decl.type)
        elif type(decl) == pycparser.c_ast.IdentifierType:
            if len(decl.names) != 1:
                raise Exception("Expected only one name for type!")
            return CType(decl.names[0])
        else:
            decl.show()
            raise Exception("Unknown type")
    def genFunction(self, ignore = False):
        """This is an internal function (a generator, in specific) which yields
        a CFunction object for every function it finds declared in the files you
        instantiated the class with."""
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
    def generateClasses(self, ffiLib):
        """This walks through the syntax tree for the files you've provided, and
        attempts to generate a list of classes that wrap it.
        ffiLib is the result of a 'ffi.dlopen' call. It is expected to contain
        every function declared in the files you instantiated this class with."""
        newClass = object()
        for fn in self.genFunction():
            if not fn.name.startswith(self.prefix):
                raise Exception("Call %s has unknown prefix!" % (fn.name,))
            try:
                fn.call = getattr(ffiLib, fn.name)
            except AttributeError:
                raise Exception("Call %s was not found in module!" % (fn.name,))
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
            # Next check is by first argument's type.
            if len(fn.argNames) > 0:
                fullType = fn.argTypes[0]
                if (fullType.pointers == 0 or fullType.pointers == 1):
                    if (fullType.baseType.startswith(self.prefix)):
                        typeName = fullType.baseType[len(self.prefix):]
                        target.append(typeName)
                        print(" * match %s by first argument" % (fn.name,))
                    else:
                        print(" - don't recognize type: %s" % (fullType,))
                else:
                    print(" - too many pointers in type: %s" % (fullType,))
            if len(target) == 0:
                print(" - unknown function %s" % (fn.name,))
                parts = newName.split("_")
                if len(parts) > 1:
                    print(" - possible targets - %s?" % (parts[1:],))
            else:
                match = True
                # Make sure that all items in 'target', if multiple ones exist,
                # are the same.  If they are not, it could indicate that the
                # function naming is ambiguous.
                if len(target) > 1:
                    match = True
                    i = 0
                    while match and i < len(target) - 1:
                        match = target[i] == target[i + 1]
                        i += 1
                if not match:
                    print(" - type mismatch for %s - %s" % (newName, target))
                else:
                    #setattr(newClass, newName, 
                    print("Found function %s for %s" % (newName, target[0]))

OpenNI2.check_cffi()
lib,ffi = OpenNI2.lib, OpenNI2.ffi
rc = lib.oni_initialize()
print("Init OpenNI2: %s" % (ffi.string(lib.oni_getString_Status(rc))))

files = ["openni2_types_python.h", "openni2_types_c.h", "openni2_types.h", "openni2_wrapper.h"]
walk = WalkAST(files, "oni_", ["DeviceInfoArray", "VideoStream", "Device", "VideoModeArray", "Recorder", "VideoMode", "VideoFrameRef", "DeviceState", "ImageRegistrationMode", "SensorType", "PixelFormat", "Status", "PlaybackControl", "CameraSettings"])
walk.generateClasses(lib)
