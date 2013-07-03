// ============================================================================
// openni2_cpp.h: Declarations that are C++ specific
// (c) Chris Hodapp, 2013
// ============================================================================

#include <OpenNI.h>

// These classes are treated as opaque pointers in the C interface.
typedef openni::CameraSettings oni_CameraSettings;
typedef openni::Device oni_Device;
typedef openni::DeviceState oni_DeviceState;
typedef openni::ImageRegistrationMode oni_ImageRegistrationMode;
//typedef openni::OpenNI::Listener oni_Listener;
// TODO Fix this (I don't know what the real Listener class is):
typedef struct oni_Listener oni_Listener;
typedef openni::PixelFormat oni_PixelFormat;
typedef openni::PlaybackControl oni_PlaybackControl;
typedef openni::Recorder oni_Recorder;
typedef openni::SensorInfo oni_SensorInfo;
typedef openni::SensorType oni_SensorType;
typedef openni::Status oni_Status;
typedef openni::VideoMode oni_VideoMode;
typedef openni::VideoFrameRef oni_VideoFrameRef;
typedef openni::VideoStream oni_VideoStream;
typedef openni::DepthPixel oni_DepthPixel;

