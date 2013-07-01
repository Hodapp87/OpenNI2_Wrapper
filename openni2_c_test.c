#include <stdio.h>
#include <stdlib.h>

#include "openni2_c_wrapper.h"

void listDevices();
void echoDeviceInfo(oni_DeviceInfo info);

int main(int argc, const char ** argv) {

    int rc = oni_initialize();
    const char * err = oni_getExtendedError();
    printf("Extended error: %s\n", err);

    listDevices();

    if (rc == oni_STATUS_OK) {

        oni_Device * device = oni_new_Device();

        if (device == NULL) {
            printf("Cannot get device!\n");
            return 1;

        } else {

            int status = oni_open(device, NULL);
            printf("Open status: %d\n", status);

            oni_DeviceInfo info = oni_getDeviceInfo(device);

            //printf("oni_IMAGE_REGISTRATION_OFF = %d\n", oni_IMAGE_REGISTRATION_OFF);
            //printf("oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR = %d\n", oni_IMAGE_REGISTRATION_DEPTH_TO_COLOR);

            oni_delete_Device(device);

            return 0;
        }
    }
}

// listDevices: Echo a list of devices to stdout.
void listDevices() {
    int deviceCount;
    oni_DeviceInfo * devices = NULL;
    int i;

    deviceCount = oni_enumerateDevicesCount();
    devices = (oni_DeviceInfo *) malloc(deviceCount * sizeof(oni_DeviceInfo));
    oni_enumerateDevices(devices);

    for (i = 0; i < deviceCount; ++i) {
        printf("Device %d:\n", i);
        echoDeviceInfo(devices[i]);
    }
    free(devices);
}

void echoDeviceInfo(oni_DeviceInfo info) {
    const char * warn = "(warning: NULL)";
    printf("\tName: %s\n", info.name == NULL ? warn : info.name);
    printf("\tURI: %s\n", info.uri == NULL ? warn : info.uri);
    printf("\tUSB product ID: %d\n", info.usbProductId);
    printf("\tUSB vendor ID: %d\n", info.usbVendorId);
    printf("\tVendor: %s\n", info.vendor == NULL ? warn : info.vendor);
}
