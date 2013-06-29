/*
This is a C wrapper to the OpenNI2 library (which has of course a C++ interface).

These functions and classes are all taken from:
http://www.openni.org/wp-content/doxygen/html/annotated.html

I'm aiming to keep it as close as possible to the interface while being
C-compatible.  Every function name, type name, and constant name should match
the naming in OpenNI2, except for a few things:
 - Using a prefix of "oni_" rather than the "openni" namespace
 - Using a suffix of "_new" and "_delete" for constructor and destructor,
respectively.
 - Making some allowances for overloaded or templatized functions (still to be
determined...), and for name conflicts (e.g. isValid)

enums are wrapped as extern ints.

(c) Chris Hodapp, 2013
*/

#ifdef __cplusplus
extern "C" {
// C++-only typedefs:
typedef openni::CameraSettings oni_CameraSettings;
typedef openni::Device oni_Device;
typedef openni::DeviceInfo oni_DeviceInfo;
typedef openni::ImageRegistrationMode oni_ImageRegistrationMode;
//typedef openni::OpenNI::Listener oni_Listener;
// TODO Fix this (I don't know what the real Listener class is):
typedef struct oni_Listener oni_Listener;
typedef openni::PlaybackControl oni_PlaybackControl;
typedef openni::SensorInfo oni_SensorInfo;
typedef openni::SensorType oni_SensorType;
typedef openni::Status oni_Status;
typedef openni::VideoStream oni_VideoStream;
typedef openni::DepthPixel oni_DepthPixel;
#else
// C-only typedefs & declarations
#include <stdbool.h>

typedef struct Array Array;
typedef struct oni_CameraSettings oni_CameraSettings;
typedef struct oni_Device oni_Device;
typedef struct oni_DeviceInfo oni_DeviceInfo;
typedef struct oni_Listener oni_Listener;
typedef struct oni_PlaybackControl oni_PlaybackControl;
typedef struct oni_SensorInfo oni_SensorInfo;
typedef struct oni_VideoStream oni_VideoStream;
typedef unsigned short uint16_t;
typedef uint16_t oni_DepthPixel;

// =============================
// openni::ImageRegistrationMode
// =============================
typedef int oni_ImageRegistrationMode;
extern const int oni_IMAGE_REGISTRATION_OFF;
extern const int oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR;

// ==================
// openni::SensorType
// ==================
typedef int oni_SensorType;
extern const int oni_SENSOR_IR;
extern const int oni_SENSOR_COLOR;
extern const int oni_SENSOR_DEPTH;

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

// Common typedefs

// ===================
// openni::oni_Version
// ===================
typedef struct {
    int build;
    int maintenance;
    int major;
    int minor;
} oni_Version;


// =============
// openni::Array
// =============
// Array is templated, oh joy...

// ======================
// openni::CameraSettings
// ======================
bool oni_getAutoExposureEnabled(oni_CameraSettings * camera);
bool oni_getAutoWhiteBalanceEnabled(oni_CameraSettings * camera);
bool oni_CameraSettings_isValid(oni_CameraSettings * camera);
oni_Status oni_setAutoExposureEnabled(oni_CameraSettings * camera, bool enabled);
oni_Status oni_setAutoWhiteBalanceEnabled(oni_CameraSettings * camera, bool enabled);

// ===========================
// openni::CoordinateConverter
// ===========================
oni_Status oni_convertDepthToColor(
    oni_VideoStream * depth, oni_VideoStream * color, int depthX, int depthY,
    oni_DepthPixel depthZ, int *pColorX, int *pColorY);
oni_Status oni_convertDepthToWorld1(
    oni_VideoStream * depth, int depthX, int depthY, oni_DepthPixel depthZ,
    float *pWorldX, float *pWorldY, float *pWorldZ);
oni_Status oni_convertDepthToWorld2(
    oni_VideoStream * depth, float depthX, float depthY, float depthZ,
    float *pWorldX, float *pWorldY, float *pWorldZ);
oni_Status oni_convertWorldToDepth1(
    oni_VideoStream * depth, float worldX, float worldY, float worldZ,
    int *pDepthX, int *pDepthY, oni_DepthPixel *pDepthZ);
oni_Status oni_convertWorldToDepth2(
    oni_VideoStream * depth, float worldX, float worldY, float worldZ,
    float *pDepthX, float *pDepthY, float *pDepthZ);

// ==============
// openni::Device
// ==============
oni_Device * oni_new();
void oni_delete(oni_Device * device);
void oni_close(oni_Device * device);
// oni_getDeviceInfo: Do not modify the returned pointer.
oni_DeviceInfo * oni_getDeviceInfo(oni_Device * device);
oni_ImageRegistrationMode oni_getImageRegistrationMode(oni_Device * device);
oni_PlaybackControl * oni_getPlaybackControl(oni_Device * device);
oni_Status oni_getProperty(oni_Device * device, int propertyId, void * data, int * dataSize);
// TODO (maybe?): templatized oni_getProperty?
const oni_SensorInfo * oni_getSensorInfo(oni_Device * device, oni_SensorType sensorType);
bool oni_hasSensor(oni_Device * device, oni_SensorType sensorType);
oni_Status oni_invoke(oni_Device * device, int cmdId, const void * data, int dataSize);
// TODO (maybe?): templatized oni_invoke?
bool oni_isCommandSupported(oni_Device * device, int cmdId);
bool oni_isFile(oni_Device * device);
bool oni_isImageRegistrationModeSupported(oni_Device * device, oni_ImageRegistrationMode mode);
bool oni_isPropertySupported(oni_Device * device, int propertyId);
bool oni_Device_isValid(oni_Device * device);
oni_Status oni_open(oni_Device * device, const char * uri);
oni_Status oni_setDepthColorSyncEnabled(oni_Device * device, bool isEnabled);
oni_Status oni_setImageRegistrationMode(oni_Device * device, oni_ImageRegistrationMode mode);
oni_Status oni_setProperty(oni_Device * device, int propId, const void * data, int dataSize);
// TODO (maybe?): templatized oni_setProperty?

// ==================
// openni::DeviceInfo
// ==================
// (You do not own any of the returned pointers)
const char * oni_getName(oni_DeviceInfo * info);
const char * oni_getUri(oni_DeviceInfo * info);
uint16_t oni_getUsbProductId(oni_DeviceInfo * info);
uint16_t oni_getUsbVendorId(oni_DeviceInfo * info);
const char * oni_getVendor(oni_DeviceInfo * info);

// ==============
// openni::OpenNI
// ==============
oni_Status oni_addListener(oni_Listener * pListener);
// TODO static void enumerateDevices(Array< DeviceInfo > *deviceInfoList)
oni_Status oni_initialize();
const char * oni_getExtendedError();
oni_Version oni_getVersion();

// ==================
// openni::SensorInfo
// ==================
oni_SensorType oni_getSensorType();
// Array<VideoMode> getSupportedVideoModes(); ?


#ifdef __cplusplus
} // extern "C"
#endif
