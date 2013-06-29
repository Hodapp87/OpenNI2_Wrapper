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

int oni_IMAGE_REGISTRATION_OFF = openni::IMAGE_REGISTRATION_OFF;
int oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR = openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR;

int oni_STATUS_OK = openni::STATUS_OK;
int oni_STATUS_ERROR = openni::STATUS_ERROR;
int oni_STATUS_NOT_IMPLEMENTED = openni::STATUS_NOT_IMPLEMENTED;
int oni_STATUS_NOT_SUPPORTED = openni::STATUS_NOT_SUPPORTED;
int oni_STATUS_BAD_PARAMETER = openni::STATUS_BAD_PARAMETER;
int oni_STATUS_OUT_OF_FLOW = openni::STATUS_OUT_OF_FLOW;
int oni_STATUS_NO_DEVICE = openni::STATUS_NO_DEVICE;
int oni_STATUS_TIME_OUT = openni::STATUS_TIME_OUT;

// =============
// openni::Camera
// =============
bool oni_getAutoExposureEnabled(oni_CameraSettings * camera) {
    EXC_CHECK( return camera->getAutoExposureEnabled(); );
    return false;
}

bool oni_getAutoWhiteBalanceEnabled(oni_CameraSettings * camera) {
    EXC_CHECK( return camera->getAutoWhiteBalanceEnabled(); );
    return false;
}

bool oni_isValid(oni_CameraSettings * camera) {
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

// ==============
// openni::OpenNI
// ==============
oni_Status oni_initialize() {
    EXC_CHECK( return openni::OpenNI::initialize(); );
    return openni::STATUS_ERROR;
}

const char * oni_getExtendedError() {
    EXC_CHECK( return openni::OpenNI::getExtendedError(); );
    return NULL;
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

int oni_open(oni_Device * device, const char * uri) {
    EXC_CHECK( return device->open(uri); );
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

