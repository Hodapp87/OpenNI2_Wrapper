// (c) Chris Hodapp, 2013
#include <OpenNI.h>
#include <iostream>

#include "openni2_c_wrapper.h"

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
oni_Device * oni_new() {
    openni::Device * device = NULL;
    EXC_CHECK( device = new openni::Device(); );
    return device;
}

void oni_delete(oni_Device * device) {
    EXC_CHECK( delete device; );
}

void oni_close(oni_Device * device) {
    EXC_CHECK( device->close(); );
}

oni_DeviceInfo * oni_getDeviceInfo(oni_Device * device) {
    EXC_CHECK( {
        const openni::DeviceInfo & info = device->getDeviceInfo();
        return (oni_DeviceInfo*) &info;
    });
    return NULL;
}

oni_ImageRegistrationMode oni_getImageRegistrationMode(oni_Device * device) {
    EXC_CHECK( return device->getImageRegistrationMode(); )
    return oni_IMAGE_REGISTRATION_OFF;
}

oni_PlaybackControl * oni_getPlaybackControl(oni_Device * device) {
    EXC_CHECK( return device->getPlaybackControl(); )
    return NULL;
}

oni_Status oni_getProperty(oni_Device * device, int propertyId, void * data, int * dataSize) {
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

bool oni_Device_isValid(oni_Device * device) {
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

oni_Status oni_setProperty(oni_Device * device, int propId, const void * data, int dataSize) {
    EXC_CHECK( return device->setProperty(propId, data, dataSize); );
    return openni::STATUS_ERROR;
}

// ==================
// openni::DeviceInfo
// ==================
const char * oni_getName(oni_DeviceInfo * info) {
    EXC_CHECK( return info->getName(); );
    return NULL;
}

const char * oni_getUri(oni_DeviceInfo * info) {
    EXC_CHECK( return info->getUri(); );
    return NULL;
}

uint16_t oni_getUsbProductId(oni_DeviceInfo * info) {
    EXC_CHECK( return info->getUsbProductId(); );
    return 0;
}

uint16_t oni_getUsbVendorId(oni_DeviceInfo * info) {
    EXC_CHECK( return info->getUsbVendorId(); );
    return 0;
}

const char * oni_getVendor(oni_DeviceInfo * info) {
    EXC_CHECK( return info->getVendor(); );
    return NULL;
}

// ==============
// openni::OpenNI
// ==============
/*oni_Status oni_addListener(oni_Listener * pListener) {
    EXC_CHECK( return openni::OpenNI::addListener(pListener); );
    return openni::STATUS_ERROR;
}
*/

oni_Status oni_initialize() {
    EXC_CHECK( return openni::OpenNI::initialize(); );
    return openni::STATUS_ERROR;
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
