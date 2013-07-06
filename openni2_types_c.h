// ============================================================================
// openni2_types_c.h: Types that are specific to the C interface
// (c) Chris Hodapp, 2013
// ============================================================================
#ifndef OPENNI2_TYPES_C
#define OPENNI2_TYPES_C

#ifdef OPENNI2_TYPES_CXX
#error You cannot #include both openni2_types_cxx.h and openni2_types_c.h.
#endif

#include <stdbool.h>
#include <stdint.h>

// ==================================================================
// Forward Declarations (for opaque pointers that map to C++ classes)
// ==================================================================
typedef struct oni_DeviceInfoArray oni_DeviceInfoArray;
typedef struct oni_VideoModeArray oni_VideoModeArray;
typedef struct oni_CameraSettings oni_CameraSettings;
typedef struct oni_Device oni_Device;
typedef struct oni_PlaybackControl oni_PlaybackControl;
typedef struct oni_Recorder oni_Recorder;
typedef struct oni_SensorInfo oni_SensorInfo;
typedef struct oni_VideoFrameRef oni_VideoFrameRef;
typedef struct oni_VideoMode oni_VideoMode;
typedef struct oni_VideoStream oni_VideoStream;
typedef uint16_t oni_DepthPixel;
// These four are still opaque pointers, but they are never used in the C
// interface directly.
typedef struct oni_DeviceConnectedListener_cxx
    oni_DeviceConnectedListener_cxx;
typedef struct oni_DeviceDisconnectedListener_cxx
    oni_DeviceDisconnectedListener_cxx;
typedef struct oni_DeviceStateChangedListener_cxx
    oni_DeviceStateChangedListener_cxx;
typedef struct oni_NewFrameListener_cxx
    oni_NewFrameListener_cxx;

// ========================================
// openni::DeviceState  ->  oni_DeviceState
// ========================================
typedef int oni_DeviceState;
extern const int oni_DEVICE_STATE_OK;
extern const int oni_DEVICE_STATE_ERROR;
extern const int oni_DEVICE_STATE_NOT_READY;
extern const int oni_DEVICE_STATE_EOF;

// ============================================================
// openni::ImageRegistrationMode  ->  oni_ImageRegistrationMode
// ============================================================
typedef int oni_ImageRegistrationMode;
extern const int oni_IMAGE_REGISTRATION_OFF;
extern const int oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR;

// ======================================
// openni::SensorType  ->  oni_SensorType
// ======================================
typedef int oni_SensorType;
extern const int oni_SENSOR_IR;
extern const int oni_SENSOR_COLOR;
extern const int oni_SENSOR_DEPTH;

// ========================================
// openni::PixelFormat  ->  oni_PixelFormat
// ========================================
typedef int oni_PixelFormat;
extern const int PIXEL_FORMAT_DEPTH_1_MM;
extern const int PIXEL_FORMAT_DEPTH_100_UM;
extern const int PIXEL_FORMAT_SHIFT_9_2;
extern const int PIXEL_FORMAT_SHIFT_9_3;
extern const int PIXEL_FORMAT_RGB888;
extern const int PIXEL_FORMAT_YUV422;
extern const int PIXEL_FORMAT_GRAY8;
extern const int PIXEL_FORMAT_GRAY16;
extern const int PIXEL_FORMAT_JPEG;

// ==============================
// openni::Status  ->  oni_Status
// ==============================
typedef int oni_Status;
extern const int oni_STATUS_OK;
extern const int oni_STATUS_ERROR;
extern const int oni_STATUS_NOT_IMPLEMENTED;
extern const int oni_STATUS_NOT_SUPPORTED;
extern const int oni_STATUS_BAD_PARAMETER;
extern const int oni_STATUS_OUT_OF_FLOW;
extern const int oni_STATUS_NO_DEVICE;
extern const int oni_STATUS_TIME_OUT;


#endif // OPENNI2_TYPES_C
