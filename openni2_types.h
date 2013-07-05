// ============================================================================
// openni2_types_common.h: Type definitions common to C & C++
// (c) Chris Hodapp, 2013
// ============================================================================
#ifndef OPENNI2_TYPES_COMMON
#define OPENNI2_TYPES_COMMON

#if !defined(OPENNI2_TYPES_C) && !defined(OPENNI2_TYPES_CXX)
#error You must #include either openni2_types_cxx.h or openni2_types_c.h.
#endif 

#include <stdbool.h>
#include <stdint.h>

// ======================================
// openni::DeviceInfo  ->  oni_DeviceInfo
// ======================================
typedef struct {
    const char * uri;
    const char * name;
    uint16_t usbProductId;
    uint16_t usbVendorId;
    const char * vendor;
} oni_DeviceInfo;

// ============================================================================
// openni::OpenNI::DeviceConnectedListener -> oni_DeviceConnectedListener
// openni::OpenNI::DeviceDisconnectedListener -> oni_DeviceDisconnectedListener
// openni::OpenNI::DeviceStateChangedListener -> oni_DeviceStateChangedListener
// ============================================================================
typedef void (*oni_DeviceConnectedListener) (oni_DeviceInfo*);
typedef void (*oni_DeviceDisconnectedListener) (oni_DeviceInfo*);
typedef void (*oni_DeviceStateChangedListener) (oni_DeviceInfo*, oni_DeviceState);
typedef void (*oni_NewFrameListener) (oni_VideoStream*);

// ================================
// openni::Version  ->  oni_Version
// ================================
typedef struct {
    int build;
    int maintenance;
    int major;
    int minor;
} oni_Version;

// ========================================
// openni::RGB888Pixel  ->  oni_RGB888Pixel
// ========================================
typedef struct { uint8_t r, g, b; } oni_RGB888Pixel;

// ====================================================
// openni::YUV422DoublePixel  ->  oni_YUV422DoublePixel
// ====================================================
typedef struct { uint8_t u, v, y1, y2; } oni_YUV422DoublePixel;

#endif // OPENNI2_TYPES_COMMON
