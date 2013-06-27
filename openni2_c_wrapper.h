/*
This is a C wrapper to the OpenNI2 library (which has of course a C++ interface).

I'm aiming to keep it as close as possible to the interface while being
C-compatible.  Every function name, type name, and constant name should match
the naming in OpenNI2, except for a few things:
 - Using a prefix of "oni_" rather than the "openni" namespace
 - Using a suffix of "_new" and "_delete" for constructor and destructor,
respectively.
 - Making some allowances for overloaded or templatized functions (still to be
determined...)

enums are wrapped as extern ints.

(c) Chris Hodapp, 2013
*/

#ifdef __cplusplus
extern "C" {
// C++-only typedefs:
typedef openni::Device oni_Device;
typedef openni::DeviceInfo oni_DeviceInfo;
typedef openni::ImageRegistrationMode oni_ImageRegistrationMode;
typedef openni::Status oni_Status;
#else
// C-only typedefs & declarations
typedef struct Array Array;
typedef struct oni_Device oni_Device;
typedef struct oni_DeviceInfo oni_DeviceInfo;
typedef unsigned short uint16_t;

// =============================
// openni::ImageRegistrationMode
// =============================
typedef int oni_ImageRegistrationMode;
extern const int oni_IMAGE_REGISTRATION_OFF;
extern const int oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR;

// ==============
// openni::Status
// ==============
typedef int oni_Status;
extern const int oni_STATUS_OK;
extern const int oni_STATUS_ERROR;
extern const int oni_STATUS_NOT_IMPLEMENTED;
extern const int oni_STATUS_NOT_SUPPORTED;
extern const int oni_STATUS_BAD_PARAMETER;
extern const int oni_STATUS_OUT_OF_FLOW;
extern const int oni_STATUS_NO_DEVICE;
extern const int oni_STATUS_TIME_OUT;
#endif

// =============
// openni::Array
// =============
// Array is templated, oh joy...

// ==============
// openni::OpenNI
// ==============
oni_Status oni_openNI_initialize();
// TODO: How do I indicate that functions like this return a STATUS enum?
const char * oni_openNI_getExtendedError();

// ==============
// openni::Device
// ==============
oni_Device * oni_Device_new();
void oni_Device_delete(oni_Device * device);
void oni_Device_close(oni_Device * device);
// oni_Device_getDeviceInfo: Do not modify the returned pointer.
oni_DeviceInfo * oni_Device_getDeviceInfo(oni_Device * device);
int oni_Device_open(oni_Device * device, const char * uri);

// ==================
// openni::DeviceInfo
// ==================
// (You do not own any of the returned pointers)
const char * oni_DeviceInfo_getName(oni_DeviceInfo * info);
const char * oni_DeviceInfo_getUri(oni_DeviceInfo * info);
uint16_t oni_DeviceInfo_getUsbProductId(oni_DeviceInfo * info);
uint16_t oni_DeviceInfo_getUsbVendorId(oni_DeviceInfo * info);
const char * oni_DeviceInfo_getVendor(oni_DeviceInfo * info);

#ifdef __cplusplus
} // extern "C"
#endif
