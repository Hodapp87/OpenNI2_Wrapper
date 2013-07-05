// ============================================================================
// openni2_listener_wrapper.h: Declaration of openni2_listener_wrapper, a class
// that is internal to the C++ code for the wrapper.
// (c) Chris Hodapp, 2013
// ============================================================================

// openni2_listener_wrapper: The purpose behind this class is to set up a wrapper
// around the classes it derives from in such a manner that the C interface,
// instead of providing an instance of a custom class of each, may instead
// provide function pointers.
class openni2_listener_wrapper : public openni::OpenNI::DeviceConnectedListener,
                       public openni::OpenNI::DeviceDisconnectedListener,
                       public openni::OpenNI::DeviceStateChangedListener,
                       public openni::VideoStream::NewFrameListener
{
public:
    openni2_listener_wrapper();

    // Overrides function in openni::OpenNI::DeviceConnectedListener
    void onDeviceConnected(const openni::DeviceInfo * dev);

    // Overrides function in openni::OpenNI::DeviceDisconnectedListener
    void onDeviceDisconnected(const openni::DeviceInfo * dev);

    // Overrides function in openni::OpenNI::DeviceStateChangedListener
    void onDeviceStateChanged(const openni::DeviceInfo * dev,
                              openni::DeviceState state);

    // Overrides function in openni::VideoStream::NewFrameListener
    void onNewFrame(openni::VideoStream & stream);
   
    oni_DeviceConnectedListener onDeviceConnected_c;
    oni_DeviceDisconnectedListener onDeviceDisconnected_c;
    oni_DeviceStateChangedListener onDeviceStateChanged_c;
    oni_NewFrameListener onNewFrame_c;
};
