// ============================================================================
// openni2_c_wrapper.h: Function declarations
// (c) Chris Hodapp, 2013
// ============================================================================

#include <OpenNI.h>
#include <iostream>

#include "openni2_types_cxx.h"
#include "openni2_types.h"
#include "openni2_wrapper.h"
#include "openni2_listener_wrapper.h"

// EXC_CHECK(block): Wrap the block or statement in an exception check, e.g.
//     EXC_CHECK( delete ptr; )
// This being a C wrapper, none of the functions may throw exceptions, so it is
// wise to use this anyplace a conception could conceivably occur.
#define EXC_CHECK(block) \
    try { \
        block \
    } catch (std::exception & e) { \
        std::cout << "Error: " << e.what() << std::endl; \
    }

// ==========================
// Static constants for enums
// ==========================
oni_DeviceState oni_DEVICE_STATE_OK = openni::DEVICE_STATE_OK;
oni_DeviceState oni_DEVICE_STATE_ERROR = openni::DEVICE_STATE_ERROR;
oni_DeviceState oni_DEVICE_STATE_NOT_READY = openni::DEVICE_STATE_NOT_READY;
oni_DeviceState oni_DEVICE_STATE_EOF = openni::DEVICE_STATE_EOF;

oni_ImageRegistrationMode oni_IMAGE_REGISTRATION_OFF = openni::IMAGE_REGISTRATION_OFF;
oni_ImageRegistrationMode oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR = openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR;

oni_Status oni_STATUS_OK = openni::STATUS_OK;
oni_Status oni_STATUS_ERROR = openni::STATUS_ERROR;
oni_Status oni_STATUS_NOT_IMPLEMENTED = openni::STATUS_NOT_IMPLEMENTED;
oni_Status oni_STATUS_NOT_SUPPORTED = openni::STATUS_NOT_SUPPORTED;
oni_Status oni_STATUS_BAD_PARAMETER = openni::STATUS_BAD_PARAMETER;
oni_Status oni_STATUS_OUT_OF_FLOW = openni::STATUS_OUT_OF_FLOW;
oni_Status oni_STATUS_NO_DEVICE = openni::STATUS_NO_DEVICE;
oni_Status oni_STATUS_TIME_OUT = openni::STATUS_TIME_OUT;

oni_SensorType oni_SENSOR_IR = openni::SENSOR_IR;
oni_SensorType oni_SENSOR_COLOR = openni::SENSOR_COLOR;
oni_SensorType oni_SENSOR_DEPTH = openni::SENSOR_DEPTH;

oni_PixelFormat PIXEL_FORMAT_DEPTH_1_MM = openni::PIXEL_FORMAT_DEPTH_1_MM;
oni_PixelFormat PIXEL_FORMAT_DEPTH_100_UM = openni::PIXEL_FORMAT_DEPTH_100_UM;
oni_PixelFormat PIXEL_FORMAT_SHIFT_9_2 = openni::PIXEL_FORMAT_SHIFT_9_2;
oni_PixelFormat PIXEL_FORMAT_SHIFT_9_3 = openni::PIXEL_FORMAT_SHIFT_9_3;
oni_PixelFormat PIXEL_FORMAT_RGB888 = openni::PIXEL_FORMAT_RGB888;
oni_PixelFormat PIXEL_FORMAT_YUV422 = openni::PIXEL_FORMAT_YUV422;
oni_PixelFormat PIXEL_FORMAT_GRAY8 = openni::PIXEL_FORMAT_GRAY8;
oni_PixelFormat PIXEL_FORMAT_GRAY16 = openni::PIXEL_FORMAT_GRAY16;
oni_PixelFormat PIXEL_FORMAT_JPEG = openni::PIXEL_FORMAT_JPEG;

// ==========================
// Internal utility functions
// ==========================
void _convertDeviceInfo(const openni::DeviceInfo & devInfo,
                        oni_DeviceInfo * out)
{
    out->name = devInfo.getName();
    out->uri = devInfo.getUri();
    out->usbProductId = devInfo.getUsbProductId();
    out->usbVendorId = devInfo.getUsbVendorId();
    out->vendor = devInfo.getVendor();
}

// =========================
// openni::Array<DeviceInfo>
// =========================
void oni_delete_DeviceInfoArray(oni_DeviceInfoArray * array) {
    EXC_CHECK( delete array; );
}

oni_DeviceInfo oni_getElement_DeviceInfoArray(oni_DeviceInfoArray * array, int idx) {
    oni_DeviceInfo info;
    info.uri = NULL;
    info.name = NULL;
    info.usbProductId = 0;
    info.usbVendorId = 0;
    info.vendor = NULL;
    EXC_CHECK( _convertDeviceInfo((*array)[idx], &info); );
    return info;
}

int oni_getSize_DeviceInfoArray(oni_DeviceInfoArray * array) {
    EXC_CHECK( return array->getSize(); );
    return -1;
}

// ========================
// openni::Array<VideoMode>
// ========================
oni_VideoMode * oni_getElement_VideoModeArray(oni_VideoModeArray * array, int idx) {
    EXC_CHECK({
        const openni::VideoMode & mode = (*array)[idx];
        return (oni_VideoMode*) &mode;
    });
    return NULL;
}

int oni_getSize_VideoModeArray(oni_VideoModeArray * array) {
    EXC_CHECK( return array->getSize(); );
    return -1;
}

// ======================
// openni::CameraSettings
// ======================
bool oni_getAutoExposureEnabled(oni_CameraSettings * camera) {
    EXC_CHECK( return camera->getAutoExposureEnabled(); );
    return false;
}

bool oni_getAutoWhiteBalanceEnabled(oni_CameraSettings * camera) {
    EXC_CHECK( return camera->getAutoWhiteBalanceEnabled(); );
    return false;
}

bool oni_CameraSettings_isValid(oni_CameraSettings * camera) {
    EXC_CHECK( return camera->isValid(); );
    return false;
}

oni_Status oni_setAutoExposureEnabled(oni_CameraSettings * camera, bool enabled) {
    EXC_CHECK( return camera->setAutoExposureEnabled(enabled); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setAutoWhiteBalanceEnabled(oni_CameraSettings * camera, bool enabled) {
    EXC_CHECK( return camera->setAutoWhiteBalanceEnabled(enabled); );
    return openni::STATUS_ERROR;
}

// ===========================
// openni::CoordinateConverter
// ===========================
oni_Status oni_convertDepthToColor(oni_VideoStream * depth,
                                   oni_VideoStream * color, int depthX,
                                   int depthY, oni_DepthPixel depthZ,
                                   int *pColorX, int *pColorY)
{
    EXC_CHECK(return openni::CoordinateConverter::convertDepthToColor(
                  *depth, *color, depthX, depthY, depthZ, pColorX, pColorY);)
    return openni::STATUS_ERROR;
}

oni_Status oni_convertDepthToWorld1(oni_VideoStream * depth, int depthX,
                                    int depthY, oni_DepthPixel depthZ,
                                    float *pWorldX, float *pWorldY,
                                    float *pWorldZ)
{
    EXC_CHECK(return openni::CoordinateConverter::convertDepthToWorld(
                  *depth, depthX, depthY, depthZ, pWorldX, pWorldY, pWorldZ);)
    return openni::STATUS_ERROR;
}

oni_Status oni_convertDepthToWorld2(oni_VideoStream * depth, float depthX,
                                    float depthY, float depthZ, float *pWorldX,
                                    float *pWorldY, float *pWorldZ)
{
    EXC_CHECK(return openni::CoordinateConverter::convertDepthToWorld(
                  *depth, depthX, depthY, depthZ, pWorldX, pWorldY, pWorldZ);)
    return openni::STATUS_ERROR;
}

oni_Status oni_convertWorldToDepth1(oni_VideoStream * depth, float worldX,
                                    float worldY, float worldZ, int *pDepthX,
                                    int *pDepthY, oni_DepthPixel *pDepthZ)
{
    EXC_CHECK(return openni::CoordinateConverter::convertWorldToDepth(
                  *depth, worldX, worldY, worldZ, pDepthX, pDepthY, pDepthZ);)
    return openni::STATUS_ERROR;
}

oni_Status oni_convertWorldToDepth2(oni_VideoStream * depth, float worldX,
                                    float worldY, float worldZ, float *pDepthX,
                                    float *pDepthY, float *pDepthZ)
{
    EXC_CHECK(return openni::CoordinateConverter::convertWorldToDepth(
                  *depth, worldX, worldY, worldZ, pDepthX, pDepthY, pDepthZ);)
    return openni::STATUS_ERROR;
}

// ==============
// openni::Device
// ==============

oni_Device * oni_new_Device() {
    openni::Device * device = NULL;
    EXC_CHECK( device = new openni::Device(); );
    return device;
}

void oni_delete_Device(oni_Device * device) {
    EXC_CHECK( delete device; );
}

void oni_close(oni_Device * device) {
    EXC_CHECK( device->close(); );
}

oni_DeviceInfo oni_getDeviceInfo(oni_Device * device) {
    oni_DeviceInfo devInfo;
    devInfo.name = NULL;
    devInfo.uri = NULL;
    devInfo.usbProductId = 0;
    devInfo.usbVendorId = 0;
    devInfo.vendor = NULL;

    EXC_CHECK( {
        const openni::DeviceInfo & info = device->getDeviceInfo();
        _convertDeviceInfo(info, &devInfo);
    });

    return devInfo;
}

oni_ImageRegistrationMode oni_getImageRegistrationMode(oni_Device * device) {
    EXC_CHECK( return device->getImageRegistrationMode(); )
    return oni_IMAGE_REGISTRATION_OFF;
}

oni_PlaybackControl * oni_getPlaybackControl(oni_Device * device) {
    EXC_CHECK( return device->getPlaybackControl(); )
    return NULL;
}

oni_Status oni_getProperty_Device(oni_Device * device, int propertyId,
                                  void * data, int * dataSize) {
    EXC_CHECK( return device->getProperty(propertyId, data, dataSize); )
    return openni::STATUS_ERROR;
}

const oni_SensorInfo * oni_getSensorInfo(oni_Device * device, oni_SensorType sensorType) {
    EXC_CHECK( return device->getSensorInfo(sensorType); )
    return NULL;
}

bool oni_hasSensor(oni_Device * device, oni_SensorType sensorType) {
    EXC_CHECK( return device->hasSensor(sensorType); )
    return false;
}

oni_Status oni_invoke(oni_Device * device, int cmdId, const void * data, int dataSize) {
    EXC_CHECK( return device->invoke(cmdId, data, dataSize); )
    return openni::STATUS_ERROR;
}

bool oni_isCommandSupported(oni_Device * device, int cmdId) {
    EXC_CHECK( return device->isCommandSupported(cmdId); );
    return false;
}

bool oni_isFile(oni_Device * device) {
    EXC_CHECK( return device->isFile(); );
    return false;
}

bool oni_isImageRegistrationModeSupported(oni_Device * device, oni_ImageRegistrationMode mode) {
    EXC_CHECK( return device->isImageRegistrationModeSupported(mode); );
    return false;
}

bool oni_isPropertySupported(oni_Device * device, int propertyId) {
    EXC_CHECK( return device->isPropertySupported(propertyId); );
    return false;
}

bool oni_isValid_Device(oni_Device * device) {
    EXC_CHECK( return device->isValid(); );
    return false;
}

oni_Status oni_open(oni_Device * device, const char * uri) {
    EXC_CHECK( return device->open(uri); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setDepthColorSyncEnabled(oni_Device * device, bool isEnabled) {
    EXC_CHECK( return device->setDepthColorSyncEnabled(isEnabled); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setImageRegistrationMode(oni_Device * device, oni_ImageRegistrationMode mode) {
    EXC_CHECK( return device->setImageRegistrationMode(mode); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setProperty_Device(oni_Device * device, int propId,
                                  const void * data, int dataSize) {
    EXC_CHECK( return device->setProperty(propId, data, dataSize); );
    return openni::STATUS_ERROR;
}

// ===========================
// Utility functions for enums
// ===========================
const char * oni_getString_DeviceState(oni_DeviceState state) {
    switch (state) {
    case openni::DEVICE_STATE_OK: return "DEVICE_STATE_OK";
	case openni::DEVICE_STATE_ERROR: return "DEVICE_STATE_ERROR";
	case openni::DEVICE_STATE_NOT_READY: return "DEVICE_STATE_NOT_READY";
	case openni::DEVICE_STATE_EOF: return "DEVICE_STATE_EOF";
    default: return "Unknown DeviceState";
    }
}

const char * oni_getString_ImageRegistrationMode(oni_ImageRegistrationMode mode) {
    switch (mode) {
    case openni::IMAGE_REGISTRATION_OFF: return "IMAGE_REGISTRATION_OFF";
    case openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR:
        return "IMAGE_REGISTRATION_DEPTH_TO_COLOR";
    default: return "Unknown ImageRegistrationMode";
    }
}

const char * oni_getString_SensorType(oni_SensorType type_) {
    switch (type_) {
    case openni::SENSOR_IR: return "SENSOR_IR";
    case openni::SENSOR_COLOR: return "SENSOR_COLOR";
    case openni::SENSOR_DEPTH: return "SENSOR_DEPTH";
    default: return "Unknown SensorType";
    }
}

const char * oni_getString_PixelFormat(oni_PixelFormat fmt) {
    switch (fmt) {
	case openni::PIXEL_FORMAT_DEPTH_1_MM: return "PIXEL_FORMAT_DEPTH_1_MM";
	case openni::PIXEL_FORMAT_DEPTH_100_UM: return "PIXEL_FORMAT_DEPTH_100_UM";
	case openni::PIXEL_FORMAT_SHIFT_9_2: return "PIXEL_FORMAT_SHIFT_9_2";
	case openni::PIXEL_FORMAT_SHIFT_9_3: return "PIXEL_FORMAT_SHIFT_9_3";
	case openni::PIXEL_FORMAT_RGB888: return "PIXEL_FORMAT_RGB888";
	case openni::PIXEL_FORMAT_YUV422: return "PIXEL_FORMAT_YUV422";
	case openni::PIXEL_FORMAT_GRAY8: return "PIXEL_FORMAT_GRAY8";
	case openni::PIXEL_FORMAT_GRAY16: return "PIXEL_FORMAT_GRAY16";
	case openni::PIXEL_FORMAT_JPEG: return "PIXEL_FORMAT_JPEG";
    default: return "Unknown PixelFormat";
    }
}

const char * oni_getString_Status(oni_Status status) {
    switch (status) {
    case openni::STATUS_OK: return "STATUS_OK";
    case openni::STATUS_ERROR: return "STATUS_ERROR";
    case openni::STATUS_NOT_IMPLEMENTED: return "STATUS_NOT_IMPLEMENTED";
    case openni::STATUS_NOT_SUPPORTED: return "STATUS_NOT_SUPPORTED";
    case openni::STATUS_BAD_PARAMETER: return "STATUS_BAD_PARAMETER";
    case openni::STATUS_OUT_OF_FLOW: return "STATUS_OUT_OF_FLOW";
    case openni::STATUS_NO_DEVICE: return "STATUS_NO_DEVICE";
    case openni::STATUS_TIME_OUT: return "STATUS_TIME_OUT";
    default: return "Unknown Status";
    }
}

// ==========================================
// openni::OpenNI::DeviceConnectedListener
// openni::OpenNI::DeviceDisconnectedListener
// openni::OpenNI::DeviceStateChangedListener
// ==========================================
openni2_listener_wrapper::openni2_listener_wrapper()
{
    onDeviceConnected_c.fnPtr = NULL;
    onDeviceConnected_c._obj = NULL;
    onDeviceDisconnected_c.fnPtr = NULL;
    onDeviceDisconnected_c._obj = NULL;
    onDeviceStateChanged_c.fnPtr = NULL;
    onDeviceStateChanged_c._obj = NULL;
    onNewFrame_c.fnPtr = NULL;
    onNewFrame_c._obj = NULL;
}

void openni2_listener_wrapper::onDeviceConnected(const openni::DeviceInfo * dev) {
    oni_DeviceInfo info;
    _convertDeviceInfo(*dev, &info);
    onDeviceConnected_c.fnPtr(&info);
}

void openni2_listener_wrapper::onDeviceDisconnected(const openni::DeviceInfo * dev) {
    oni_DeviceInfo info;
    _convertDeviceInfo(*dev, &info);
    onDeviceDisconnected_c.fnPtr(&info);
}

void openni2_listener_wrapper::onDeviceStateChanged(const openni::DeviceInfo * dev,
                                                    openni::DeviceState state) {
    oni_DeviceInfo info;
    _convertDeviceInfo(*dev, &info);
    onDeviceStateChanged_c.fnPtr(&info, state);
}

void openni2_listener_wrapper::onNewFrame(openni::VideoStream & stream) {
    oni_VideoStream * streamPtr = &stream;
    onNewFrame_c.fnPtr(streamPtr);
}

// ==============
// openni::OpenNI
// ==============
oni_Status oni_addDeviceConnectedListener(oni_DeviceConnectedListener * listen) {
    // Wrap this function pointer in an ad-hoc member of our subclass:
    openni2_listener_wrapper * connected = new openni2_listener_wrapper();
    connected->onDeviceConnected_c.fnPtr = listen->fnPtr;
    connected->onDeviceConnected_c._obj = connected;
    oni_Status rc = openni::STATUS_ERROR;
    EXC_CHECK({
        rc = openni::OpenNI::addDeviceConnectedListener(connected);
        listen->_obj = connected;
    });
    return rc;
    // N.B. In this function, and the three below, I am assuming that OpenNI is
    // taking over ownership of the openni2_listener_wrapper object, but the docs
    // never state this.
}

oni_Status oni_addDeviceDisconnectedListener(oni_DeviceDisconnectedListener * listen) {
    // Wrap this function pointer in an ad-hoc member of our subclass:
    openni2_listener_wrapper * connected = new openni2_listener_wrapper();
    connected->onDeviceDisconnected_c.fnPtr = listen->fnPtr;
    connected->onDeviceDisconnected_c._obj = connected;
    oni_Status rc = openni::STATUS_ERROR;
    EXC_CHECK({
        rc = openni::OpenNI::addDeviceDisconnectedListener(connected);
        listen->_obj = connected;
    });
    return rc;
}

oni_Status oni_addDeviceStateChangedListener(oni_DeviceStateChangedListener * listen) {
    openni2_listener_wrapper * connected = new openni2_listener_wrapper();
    connected->onDeviceStateChanged_c.fnPtr = listen->fnPtr;
    connected->onDeviceStateChanged_c._obj = connected;
    oni_Status rc = openni::STATUS_ERROR;
    EXC_CHECK({
        rc = openni::OpenNI::addDeviceStateChangedListener(connected);
        listen->_obj = connected;
    });
    return rc;
}

oni_DeviceInfoArray * oni_enumerateDevices() {
    EXC_CHECK({
        openni::Array<openni::DeviceInfo> * devices =
            new openni::Array<openni::DeviceInfo>();
        openni::OpenNI::enumerateDevices(devices);

        return devices;

/*
        int count = devices.getSize();
        if (count > maxDevices && maxDevices >= 0) {
            count = maxDevices;
        }

        for (int i = 0; i < count; ++i) {
            _convertDeviceInfo(devices[i], out + i);
        }
*/
    });
}

const char * oni_getExtendedError() {
    EXC_CHECK( return openni::OpenNI::getExtendedError(); );
    return NULL;
}

oni_Version oni_getVersion() {
    oni_Version ver_c;
    openni::Version ver;
    EXC_CHECK( ver = openni::OpenNI::getVersion(); );
    ver_c.build = ver.build;
    ver_c.maintenance = ver.maintenance;
    ver_c.major = ver.major;
    ver_c.minor = ver.minor;
    return ver_c;
}

oni_Status oni_initialize() {
    EXC_CHECK( return openni::OpenNI::initialize(); );
    return openni::STATUS_ERROR;
}

void oni_removeDeviceConnectedListener(oni_DeviceConnectedListener listen) {
    EXC_CHECK( openni::OpenNI::removeDeviceConnectedListener(listen._obj); );
}

void oni_removeDeviceDisconnectedListener(oni_DeviceDisconnectedListener listen) {
    EXC_CHECK( openni::OpenNI::removeDeviceDisconnectedListener(listen._obj); );
}

void oni_removeDeviceStateChangedListener(oni_DeviceStateChangedListener listen) {
    EXC_CHECK( openni::OpenNI::removeDeviceStateChangedListener(listen._obj); );
}

void oni_shutdown() {
    EXC_CHECK( openni::OpenNI::shutdown(); );
}

// =======================
// openni::PlaybackControl
// =======================
void oni_delete_PlaybackControl(oni_PlaybackControl * control) {
    EXC_CHECK( delete control; );
}

int oni_getNumberOfFrames(oni_PlaybackControl * control,
                          oni_VideoStream * stream) {
    EXC_CHECK( return control->getNumberOfFrames(*stream); );
    return 0;
}

bool oni_getRepeatEnabled(oni_PlaybackControl * control) {
    EXC_CHECK( return control->getRepeatEnabled(); );
    return false;
}

float oni_getSpeed(oni_PlaybackControl * control) {
    EXC_CHECK( return control->getSpeed(); );
    return 0.0;
}

bool oni_isValid_PlaybackControl(oni_PlaybackControl * control) {
    EXC_CHECK( return control->isValid(); );
    return 0.0;
}

oni_Status oni_seek(oni_PlaybackControl * control, oni_VideoStream * stream,
                    int frameIndex) {
    EXC_CHECK( return control->seek(*stream, frameIndex); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setRepeatEnabled(oni_PlaybackControl * control, bool repeat) {
    EXC_CHECK( return control->setRepeatEnabled(repeat); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setSpeed(oni_PlaybackControl * control, float speed) {
    EXC_CHECK( return control->setSpeed(speed); );
    return openni::STATUS_ERROR;
}

// ================
// openni::Recorder
// ================
oni_Recorder * oni_new_Recorder() {
    EXC_CHECK( return new openni::Recorder(); );
    return NULL;
}

void oni_delete_Recorder(oni_Recorder * recorder) {
    EXC_CHECK( delete recorder; );
}

oni_Status oni_attach(oni_Recorder * recorder, oni_VideoStream * stream,
                      bool allowLossy) {
    EXC_CHECK( return recorder->attach(*stream, allowLossy); );
    return openni::STATUS_ERROR;
}

oni_Status oni_create(oni_Recorder * recorder, const char * filename) {
    EXC_CHECK( return recorder->create(filename); );
    return openni::STATUS_ERROR;
}

void oni_destroy(oni_Recorder * recorder) {
    EXC_CHECK( recorder->destroy(); );
}

bool oni_isValid_Recorder(oni_Recorder * recorder) {
    EXC_CHECK( return recorder->isValid(); );
    return false;
}

oni_Status oni_start(oni_Recorder * recorder) {
    EXC_CHECK( return recorder->start(); );
    return openni::STATUS_ERROR;
}

void oni_stop(oni_Recorder * recorder) {
    EXC_CHECK( recorder->stop(); );
}

// ==================
// openni::SensorInfo
// ==================
oni_SensorType oni_getSensorType(const oni_SensorInfo * info) {
    EXC_CHECK( return info->getSensorType(); );
}

oni_VideoModeArray * oni_getSupportedVideoModes(const oni_SensorInfo * info) {
    EXC_CHECK({
        const openni::Array<openni::VideoMode> & modes =
            info->getSupportedVideoModes();
        return (oni_VideoModeArray*) &modes;
    });
    return NULL;
}

// =====================
// openni::VideoFrameRef
// =====================
oni_VideoFrameRef * oni_new_VideoFrameRef(oni_VideoFrameRef * other) {
    oni_VideoFrameRef * newRef = NULL;
    EXC_CHECK({
        newRef = other == NULL ?
            new openni::VideoFrameRef() :
            new openni::VideoFrameRef(*other);
    });
    return newRef;
}

void oni_delete_VideoFrameRef(oni_VideoFrameRef * ref) {
    EXC_CHECK( delete ref; );
}

oni_VideoFrameRef * oni_copy_VideoFrameRef(oni_VideoFrameRef * ref,
                                           oni_VideoFrameRef * source) {
    EXC_CHECK({
        openni::VideoFrameRef & newRef = (*ref).operator =(*source);
        return &newRef;
    });
    return NULL;
}

int oni_getCropOriginX(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getCropOriginX(); );
    return 0;
}

int oni_getCropOriginY(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getCropOriginY(); );
    return 0;
}

bool oni_getCroppingEnabled(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getCroppingEnabled(); );
    return false;
}

const void * oni_getData(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getData(); );
    return NULL;
}

int oni_getDataSize(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getDataSize(); );
    return 0;
}

int oni_getFrameIndex(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getFrameIndex(); );
    return 0;
}

int oni_getHeight(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getHeight(); );
    return 0;
}

oni_SensorType oni_getSensorType_VideoFrameRef(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getSensorType(); );
}

int oni_getStrideInBytes(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getStrideInBytes(); );
    return 0;
}

uint64_t oni_getTimestamp(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getTimestamp(); );
    return 0;
}

oni_VideoMode oni_getVideoMode(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getVideoMode(); );
}

int oni_getWidth(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->getWidth(); );
    return 0;
}

bool oni_isValid_VideoFrameRef(oni_VideoFrameRef * ref) {
    EXC_CHECK( return ref->isValid(); );
    return false;
}

void oni_release_VideoFrameRef(oni_VideoFrameRef * ref) {
    EXC_CHECK( ref->release(); );
}

// =================
// openni::VideoMode
// =================
oni_VideoMode * oni_new_VideoMode(oni_VideoMode * other) {
    oni_VideoMode * newMode = NULL;
    EXC_CHECK({
        newMode = other == NULL ?
            new openni::VideoMode() :
            new openni::VideoMode(*other);
    });
    return newMode;
}

oni_VideoMode * oni_copy_VideoMode(oni_VideoMode * mode,
                                   oni_VideoMode * source) {
    EXC_CHECK({
        openni::VideoMode & newMode = (*mode).operator =(*source);
        return &newMode;
    });
    return NULL;
}

int oni_getFps(oni_VideoMode * mode) {
    EXC_CHECK( return mode->getFps(); );
    return 0;
}

oni_PixelFormat oni_getPixelFormat(oni_VideoMode * mode) {
    EXC_CHECK( return mode->getPixelFormat(); );
}

int oni_getResolutionX(oni_VideoMode * mode) {
    EXC_CHECK( return mode->getResolutionX(); );
    return 0;
}

int oni_getResolutionY(oni_VideoMode * mode) {
    EXC_CHECK( return mode->getResolutionY(); );
    return 0;
}

void oni_setFps(oni_VideoMode * mode, int fps) {
    EXC_CHECK( mode->setFps(fps); );
}

void oni_setPixelFormat(oni_VideoMode * mode, oni_PixelFormat format) {
    EXC_CHECK( mode->setPixelFormat(format); );
}

void oni_setResolution(oni_VideoMode * mode, int resX, int resY) {
    EXC_CHECK( mode->setResolution(resX, resY); );
}

// ===================
// openni::VideoStream
// ===================
oni_VideoStream * oni_new_VideoStream() {
    EXC_CHECK( return new openni::VideoStream(); );
    return NULL;
}

void oni_delete_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK( delete stream; );
} 

oni_Status oni_addNewFrameListener(oni_VideoStream * stream,
                                   oni_NewFrameListener * listen) {
    // Wrap this function pointer in an ad-hoc member of our subclass:
    openni2_listener_wrapper * connected = new openni2_listener_wrapper();
    connected->onNewFrame_c.fnPtr = listen->fnPtr;
    connected->onNewFrame_c._obj = connected;
    oni_Status rc = openni::STATUS_ERROR;
    EXC_CHECK({
        rc = stream->addNewFrameListener(connected);
        listen->_obj = connected;
    });
    return rc;
}

oni_Status oni_create_VideoStream(oni_VideoStream * stream, oni_Device * device,
                                  oni_SensorType sensorType) {
    EXC_CHECK( return stream->create(*device, sensorType); );
    return openni::STATUS_ERROR;
}

void oni_destroy_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK( stream->destroy(); );
}

oni_CameraSettings * oni_getCameraSettings(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getCameraSettings(); );
    return NULL;
}

bool oni_getCropping(oni_VideoStream * stream, int *pOriginX, int *pOriginY,
                     int *pWidth, int *pHeight) {
    EXC_CHECK( return stream->getCropping(pOriginX, pOriginY, pWidth, pHeight); );
    return false;
}

float oni_getHorizontalFieldOfView(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getHorizontalFieldOfView(); );
    return 0.0;
}

int oni_getMaxPixelValue(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getMaxPixelValue(); );
    return 0;
}

int oni_getMinPixelValue(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getMinPixelValue(); );
    return 0;
}

bool oni_getMirroringEnabled(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getMirroringEnabled(); );
    return false;
}

oni_Status oni_getProperty_VideoStream(oni_VideoStream * stream, int propertyId,
                                       void *data, int *dataSize) {
    EXC_CHECK( return stream->getProperty(propertyId, data, dataSize); );
    return openni::STATUS_ERROR;
}

oni_SensorInfo * oni_getSensorInfo_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK({
        const openni::SensorInfo & info = stream->getSensorInfo();
        return (oni_SensorInfo*) &info;
    });
    return NULL;
}

float oni_getVerticalFieldOfView(oni_VideoStream * stream) {
    EXC_CHECK( return stream->getVerticalFieldOfView(); );
    return 0.0;
}

oni_VideoMode * oni_getVideoMode_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK({
        openni::VideoMode * mode = new openni::VideoMode(stream->getVideoMode());
        return mode;
    });
    return NULL;
}

oni_Status oni_invoke_VideoStream(oni_VideoStream * stream, int commandId,
                                  void *data, int dataSize) {
    EXC_CHECK( return stream->invoke(commandId, data, dataSize); );
    return openni::STATUS_ERROR;
}

bool oni_isCommandSupported_VideoStream(oni_VideoStream * stream, int commandId) {
    EXC_CHECK( return stream->isCommandSupported(commandId); );
    return false;
}

bool oni_isCroppingSupported(oni_VideoStream * stream) {
    EXC_CHECK( return stream->isCroppingSupported(); );
    return false;
}

bool oni_isPropertySupported_VideoStream(oni_VideoStream * stream, int propertyId) {
    EXC_CHECK( return stream->isPropertySupported(propertyId); );
    return false;
}

bool oni_isValid_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK( return stream->isValid(); );
    return false;
}

oni_Status oni_readFrame(oni_VideoStream * stream, oni_VideoFrameRef *pFrame) {
    EXC_CHECK( return stream->readFrame(pFrame); );
    return openni::STATUS_ERROR;
}

void oni_removeNewFrameListener(oni_VideoStream * stream,
                                oni_NewFrameListener * listen) {
    EXC_CHECK( stream->removeNewFrameListener(listen->_obj); );
}

oni_Status oni_resetCropping(oni_VideoStream * stream) {
    EXC_CHECK( return stream->resetCropping(); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setCropping(oni_VideoStream * stream, int originX, int originY, int width, int height) {
    EXC_CHECK( return stream->setCropping(originX, originY, width, height); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setMirroringEnabled(oni_VideoStream * stream, bool isEnabled) {
    EXC_CHECK( return stream->setMirroringEnabled(isEnabled); );
    return openni::STATUS_ERROR;
}

oni_Status oni_setProperty_VideoStream(oni_VideoStream * stream, int propertyId,
                                       const void *data, int dataSize) {
    EXC_CHECK( return stream->setProperty(propertyId, data, dataSize); );
    return openni::STATUS_ERROR;
}

// template<class T > Status setProperty (int propertyId, const T &value)
oni_Status oni_setVideoMode(oni_VideoStream * stream,
                            oni_VideoMode * videoMode) {
    EXC_CHECK( return stream->setVideoMode(*videoMode); );
    return openni::STATUS_ERROR;
}

oni_Status oni_start_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK( return stream->start(); );
    return openni::STATUS_ERROR;
}

void oni_stop_VideoStream(oni_VideoStream * stream) {
    EXC_CHECK( stream->stop(); );
}
