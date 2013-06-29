#include <stdio.h>
#include "openni2_c_wrapper.h"

int main(int argc, const char ** argv) {

    int rc = oni_initialize();
    const char * err = oni_getExtendedError();
    printf("Extended error: %s\n", err);

    if (rc == oni_STATUS_OK) {

        oni_Device * device = oni_new();

        if (device == NULL) {
            printf("Cannot get device!\n");
            return 1;

        } else {

            int status = oni_open(device, NULL);
            printf("Open status: %d\n", status);

            oni_DeviceInfo * info = oni_getDeviceInfo(device);
            printf("Name: %s\n", oni_getName(info));
            printf("URI: %s\n", oni_getUri(info));
            printf("USB product ID: %d\n", oni_getUsbProductId(info));
            printf("USB vendor ID: %d\n", oni_getUsbVendorId(info));
            printf("Vendor: %s\n", oni_getVendor(info));

            //printf("oni_IMAGE_REGISTRATION_OFF = %d\n", oni_IMAGE_REGISTRATION_OFF);
            //printf("oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR = %d\n", oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR);

            oni_delete(device);

            return 0;
        }
    }
}
