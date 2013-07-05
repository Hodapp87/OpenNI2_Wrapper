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

#ifdef __cplusplus
extern "C" {
#endif

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
// ============================================================================
// For this and the next three typedefs: 'fnPtr' is a pointer to a function that
// serves as the listener callback, and '_obj' is an internal pointer to a class
// member of a corresponding internal type.  Said class member contains 'fnPtr'
// upon creation.  The only reason it must be kept around is so that the calls
// to remove the listeners can still function.
typedef struct {
    void (*fnPtr) (oni_DeviceInfo*);
    oni_DeviceConnectedListener_cxx * _obj;
} oni_DeviceConnectedListener;

// ============================================================================
// openni::OpenNI::DeviceDisconnectedListener -> oni_DeviceDisconnectedListener
// ============================================================================
typedef struct {
    void (*fnPtr) (oni_DeviceInfo*);
    oni_DeviceDisconnectedListener_cxx * _obj;
} oni_DeviceDisconnectedListener;

// ============================================================================
// openni::OpenNI::DeviceStateChangedListener -> oni_DeviceStateChangedListener
// ============================================================================
typedef struct {
    void (*fnPtr) (oni_DeviceInfo*, oni_DeviceState);
    oni_DeviceStateChangedListener_cxx * _obj;
} oni_DeviceStateChangedListener;

// ============================================================================
// openni::VideoStream::NewFrameListener  ->  oni_NewFrameListener
// ============================================================================
typedef struct {
    void (*fnPtr) (oni_VideoStream*);
    oni_NewFrameListener_cxx * _obj;
} oni_NewFrameListener;

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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // OPENNI2_TYPES_COMMON
