#ifdef __cplusplus
extern "C" {
typedef openni::Device oni_device;
typedef openni::DeviceInfo oni_device_info;
#else
typedef struct oni_device oni_device;
typedef struct oni_device_info oni_device_info;
#endif
typedef unsigned short uint16_t;

// openni::Device
oni_device * oni_device_new();
void oni_device_delete(oni_device * device);
void oni_device_close(oni_device * device);
// oni_device_getDeviceInfo: Do not modify the returned pointer.
oni_device_info * oni_device_getDeviceInfo(oni_device * device);

// openni::DeviceInfo
// (You do not own any of the returned pointers)
const char * oni_device_info_getName(oni_device_info * info);
const char * oni_device_info_getUri(oni_device_info * info);
uint16_t oni_device_info_getUsbProductId(oni_device_info * info);
uint16_t oni_device_info_getUsbVendorId(oni_device_info * info);
const char * oni_device_info_getVendor(oni_device_info * info);

#ifdef __cplusplus
} // extern "C"
#endif
