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

// These functions are all taken from:
// http://www.openni.org/wp-content/doxygen/html/annotated.html
// and are meant to be a thin wrapper.

// ==============
// openni::Device
// ==============
oni_device * oni_device_new() {
    openni::Device * oni_device = NULL;
    EXC_CHECK( oni_device = new openni::Device(); );
    return oni_device;
}

void oni_device_delete(oni_device * device) {
    EXC_CHECK( delete device; );
}

void oni_device_close(oni_device * device) {
    EXC_CHECK( device->close(); );
}

oni_device_info * oni_device_getDeviceInfo(oni_device * device) {
    EXC_CHECK( {
        const openni::DeviceInfo & info = device->getDeviceInfo();
        return (oni_device_info*) &info;
    });
    return NULL;
}

// ==================
// openni::DeviceInfo
// ==================
const char * oni_device_info_getName(oni_device_info * info) {
    EXC_CHECK( return info->getName(); );
    return NULL;
}

const char * oni_device_info_getUri(oni_device_info * info) {
    EXC_CHECK( return info->getUri(); );
    return NULL;
}

uint16_t oni_device_info_getUsbProductId(oni_device_info * info) {
    EXC_CHECK( return info->getUsbProductId(); );
    return 0;
}

uint16_t oni_device_info_getUsbVendorId(oni_device_info * info) {
    EXC_CHECK( return info->getUsbVendorId(); );
    return 0;
}

const char * oni_device_info_getVendor(oni_device_info * info) {
    EXC_CHECK( return info->getVendor(); );
    return NULL;
}

