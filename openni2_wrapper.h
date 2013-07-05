// ============================================================================
// openni2_c_wrapper.h: Function declarations for the C interface
// (c) Chris Hodapp, 2013
// ============================================================================

#ifndef OPENNI2_WRAPPER
#define OPENNI2_WRAPPER

#include "openni2_types.h"

#ifdef __cplusplus
extern "C" {
#endif

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
oni_Device * oni_new_Device();
void oni_delete_Device(oni_Device * device);
void oni_close(oni_Device * device);
// oni_getDeviceInfo: Do not modify the returned pointers!
oni_DeviceInfo oni_getDeviceInfo(oni_Device * device);
oni_ImageRegistrationMode oni_getImageRegistrationMode(oni_Device * device);
oni_PlaybackControl * oni_getPlaybackControl(oni_Device * device);
oni_Status oni_getProperty(oni_Device * device, int propertyId, void * data, int * dataSize);
// TODO (maybe?): templatized oni_getProperty?
const oni_SensorInfo * oni_getSensorInfo(oni_Device * device, oni_SensorType sensorType);
bool oni_hasSensor(oni_Device * device, oni_SensorType sensorType);
oni_Status oni_invoke_Device(oni_Device * device, int cmdId, const void * data, int dataSize);
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
// All of the oni_addDevice...Listener functions take function pointers rather
// than class instances.
oni_Status oni_addDeviceConnectedListener(oni_DeviceConnectedListener fnPtr);
oni_Status oni_addDeviceDisconnectedListener(oni_DeviceDisconnectedListener fnPtr);
oni_Status oni_addDeviceStateChangedListener(oni_DeviceStateChangedListener fnPtr);
// oni_enumerateDevices: You are responsible for the returned array.
int oni_enumerateDevicesCount();
void oni_enumerateDevices(oni_DeviceInfo * out);
const char * oni_getExtendedError();
oni_Version oni_getVersion();
oni_Status oni_initialize();
// The same thing applies to the oni_removeDevice functions as oni_addDevice
//oni_Status oni_removeDeviceConnectedListener(oni_DeviceConnectedListener fnPtr);
//oni_Status oni_removeDeviceDisconnectedListener(oni_DeviceDisconnectedListener fnPtr);
//oni_Status oni_removeDeviceStateChangedListener(oni_DeviceStateChangedListener fnPtr);
// TODO How would these work? The pointer to the class object would have to be
// the same. This may necessitate a struct rather than a function pointer.
void oni_shutdown();

// =======================
// openni::PlaybackControl
// =======================
void oni_delete_PlaybackControl(oni_PlaybackControl * control);
int oni_getNumberOfFrames(oni_PlaybackControl * control,
                          oni_VideoStream * stream);
bool oni_getRepeatEnabled(oni_PlaybackControl * control);
float oni_getSpeed(oni_PlaybackControl * control);
bool oni_isValid_PlaybackControl(oni_PlaybackControl * control);
oni_Status oni_seek(oni_PlaybackControl * control, oni_VideoStream * stream,
                    int frameIndex);
oni_Status oni_setRepeatEnabled(oni_PlaybackControl * control, bool repeat);
oni_Status oni_setSpeed(oni_PlaybackControl * control, float speed);

// ================
// openni::Recorder
// ================
oni_Recorder * oni_new_Recorder();
void oni_delete_Recorder(oni_Recorder * recorder);
oni_Status oni_attach(oni_Recorder * recorder, oni_VideoStream * stream,
                      bool allowLossy);
oni_Status oni_create(oni_Recorder * recorder, const char * filename);
void oni_destroy(oni_Recorder * recorder);
bool oni_isValid_Recorder(oni_Recorder * recorder);
oni_Status oni_start(oni_Recorder * recorder);
void oni_stop(oni_Recorder * recorder);

// ==================
// openni::SensorInfo
// ==================
oni_SensorType oni_getSensorType();
// Array<VideoMode> getSupportedVideoModes(); ?

// =====================
// openni::VideoFrameRef
// =====================
// oni_new_VideoFrameRef: 'other' can be NULL for default constructor.
oni_VideoFrameRef * oni_new_VideoFrameRef(oni_VideoFrameRef * other);
void oni_delete_VideoFrameRef(oni_VideoFrameRef * ref);
oni_VideoFrameRef * oni_copy_VideoFrameRef(oni_VideoFrameRef * ref,
                                           oni_VideoFrameRef * source);
int oni_getCropOriginX(oni_VideoFrameRef * ref);
int oni_getCropOriginY(oni_VideoFrameRef * ref);
bool oni_getCroppingEnabled(oni_VideoFrameRef * ref);
const void * oni_getData(oni_VideoFrameRef * ref);
int oni_getDataSize(oni_VideoFrameRef * ref);
int oni_getFrameIndex(oni_VideoFrameRef * ref);
int oni_getHeight(oni_VideoFrameRef * ref);
oni_SensorType oni_getSensorType_VideoFrameRef(oni_VideoFrameRef * ref);
int oni_getStrideInBytes(oni_VideoFrameRef * ref);
uint64_t oni_getTimestamp(oni_VideoFrameRef * ref);
oni_VideoMode oni_getVideoMode(oni_VideoFrameRef * ref);
int oni_getWidth(oni_VideoFrameRef * ref);
bool oni_isValid_VideoFrameRef(oni_VideoFrameRef * ref);
void oni_release_VideoFrameRef(oni_VideoFrameRef * ref);

// =================
// openni::VideoMode
// =================
// oni_new_VideoMode: 'other' can be NULL for default constructor.
oni_VideoMode * oni_new_VideoMode(oni_VideoMode * other);
oni_VideoMode * oni_copy_VideoMode(oni_VideoMode * mode,
                                   oni_VideoMode * source);
int oni_getFps(oni_VideoMode * mode);
oni_PixelFormat oni_getPixelFormat(oni_VideoMode * mode);
int oni_getResolutionX(oni_VideoMode * mode);
int oni_getResolutionY(oni_VideoMode * mode);
void oni_setFps(oni_VideoMode * mode, int fps);
void oni_setPixelFormat(oni_VideoMode * mode, oni_PixelFormat format);
void oni_setResolution(oni_VideoMode * mode, int resX, int resY);

// ===================
// openni::VideoStream
// ===================
oni_VideoStream * oni_new_VideoStream();
void oni_delete_VideoStream(oni_VideoStream * stream); 
//oni_Status oni_addNewFrameListener(NewFrameListener *pListener); 
oni_Status oni_create_VideoStream(oni_VideoStream * stream, oni_Device * device,
                                  oni_SensorType sensorType);
void oni_destroy_VideoStream(oni_VideoStream * stream);
// oni_getCameraSettings: You do not own the returned object.
oni_CameraSettings * oni_getCameraSettings(oni_VideoStream * stream);
bool oni_getCropping(oni_VideoStream * stream, int *pOriginX, int *pOriginY, int *pWidth, int *pHeight);
float oni_getHorizontalFieldOfView(oni_VideoStream * stream);
int oni_getMaxPixelValue(oni_VideoStream * stream);
int oni_getMinPixelValue(oni_VideoStream * stream);
bool oni_getMirroringEnabled(oni_VideoStream * stream);
oni_Status oni_getProperty_VideoStream(oni_VideoStream * stream, int propertyId,
                                       void *data, int *dataSize);
//template<class T> Status getProperty (int propertyId, T *value) const
oni_SensorInfo * oni_getSensorInfo_VideoStream(oni_VideoStream * stream);
float oni_getVerticalFieldOfView(oni_VideoStream * stream);
// oni_getVideoMode_VideoStream: You must delete this object when done.
oni_VideoMode * oni_getVideoMode_VideoStream(oni_VideoStream * stream);
oni_Status oni_invoke_VideoStream(oni_VideoStream * stream, int commandId, void *data, int dataSize);
//template<class T> Status invoke (int commandId, const T &value)
bool oni_isCommandSupported_VideoStream(oni_VideoStream * stream, int commandId);
bool oni_isCroppingSupported(oni_VideoStream * stream);
bool oni_isPropertySupported_VideoStream(oni_VideoStream * stream, int propertyId);
bool oni_isValid_VideoStream(oni_VideoStream * stream);
oni_Status oni_readFrame(oni_VideoStream * stream, oni_VideoFrameRef *pFrame);
//void oni_removeNewFrameListener(NewFrameListener *pListener)
oni_Status oni_resetCropping(oni_VideoStream * stream);
oni_Status oni_setCropping(oni_VideoStream * stream, int originX, int originY, int width, int height);
oni_Status oni_setMirroringEnabled(oni_VideoStream * stream, bool isEnabled);
oni_Status oni_setProperty_VideoStream(oni_VideoStream * stream, int propertyId,
                                       const void *data, int dataSize);
// template<class T > Status setProperty (int propertyId, const T &value)
oni_Status oni_setVideoMode(oni_VideoStream * stream,
                            oni_VideoMode * videoMode);
oni_Status oni_start_VideoStream(oni_VideoStream * stream);
void oni_stop_VideoStream(oni_VideoStream * stream);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // OPENNI2_WRAPPER
