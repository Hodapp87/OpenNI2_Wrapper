#include <stdio.h>
#include "openni2_c_wrapper.h"

int main(int argc, const char ** argv) {

    oni_device * device = oni_device_new();

    if (device == NULL) {
        printf("Cannot get device!\n");
        return 1;

    } else {

        oni_device_info * info = oni_device_getDeviceInfo(device);
        printf("Name: %s\n", oni_device_info_getName(info));
        printf("URI: %s\n", oni_device_info_getUri(info));
        printf("USB product ID: %d\n", oni_device_info_getUsbProductId(info));
        printf("USB vendor ID: %d\n", oni_device_info_getUsbVendorId(info));
        printf("Vendor: %s\n", oni_device_info_getVendor(info));

        oni_device_delete(device);

        return 0;
    }
}
