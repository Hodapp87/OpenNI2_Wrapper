#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "openni2_c.h"

void listDevices();
char * getFirstUri();
void echoDeviceInfo(oni_DeviceInfo info);
void deviceConnect(oni_DeviceInfo * info);
void deviceDisconnect(oni_DeviceInfo * info);
void deviceStateChange(oni_DeviceInfo * info, oni_DeviceState state);
void echoSensorInfo(const oni_SensorInfo * info);

int main(int argc, const char ** argv) {
    int rc;

    char * uri = NULL;
    oni_Device * device = NULL;

    oni_DeviceConnectedListener listen1;
    oni_DeviceDisconnectedListener listen2;
    oni_DeviceStateChangedListener listen3;

    listen1.fnPtr = &deviceConnect;
    listen2.fnPtr = &deviceDisconnect;
    listen3.fnPtr = &deviceStateChange;
    //const char * err = oni_getExtendedError();
    //printf("Extended error: %s\n", err);

    rc = oni_initialize();

    if (rc == oni_STATUS_OK) {
        rc = oni_addDeviceConnectedListener(&listen1);
        rc = oni_addDeviceDisconnectedListener(&listen2);
        rc = oni_addDeviceStateChangedListener(&listen3);

        listDevices();

        uri = getFirstUri();
    }

    if (uri != NULL) {
        printf("Using URI: %s\n", uri);
        device = oni_new_Device();
    } else {
        printf("Unable to find device!\n");
    }

    if (device != NULL) {
        rc = oni_open(device, uri);
        printf("oni_open: rc=%s\n", oni_getString_Status(rc));

        printf("Device is %s\n", oni_isValid_Device(device) ? "valid" : "invalid");

        printf("Registration mode: %s\n", oni_getString_ImageRegistrationMode(
                   oni_getImageRegistrationMode(device)));

        {
            int i;
            bool hasSensor;
            oni_SensorType types[] = { oni_SENSOR_IR, oni_SENSOR_COLOR, oni_SENSOR_DEPTH };

            for (i = 0; i < 3; ++i) {

                hasSensor = oni_hasSensor(device, types[i]);

                if (hasSensor) {
                    const oni_SensorInfo * info = oni_getSensorInfo(device, types[i]);
                    if (info == NULL) {
                        printf("Present, but can't get info\n");
                    } else {
                        echoSensorInfo(info);
                    }
                } else {
                    const char * sensorName = oni_getString_SensorType(types[i]);
                    printf("Sensor type %s: Not present", sensorName);
                }
            }
        }
        
        oni_close(device);
    }
}

// listDevices: Echo a list of devices to stdout.
void listDevices() {
    int i;

    oni_DeviceInfoArray * devices = oni_enumerateDevices();
    int deviceCount = oni_getSize_DeviceInfoArray(devices);
    printf("OpenNI reported %d devices\n", deviceCount);

    for (i = 0; i < deviceCount; ++i) {
        oni_DeviceInfo info;
        printf("Device %d:\n", i);

        info = oni_getElement_DeviceInfoArray(devices, i);
        echoDeviceInfo(info);
    }
    free(devices);
}

// getFirstUri: Get the URI of what looks like a valid device, or return NULL.
char * getFirstUri() {
    char * uri = NULL;

    oni_DeviceInfoArray * devices = oni_enumerateDevices();
    int deviceCount = oni_getSize_DeviceInfoArray(devices);
    if (deviceCount > 0) {
        oni_DeviceInfo info;
        info = oni_getElement_DeviceInfoArray(devices, 0);
        uri = (char*) info.uri;
    }

    return uri;
}

void echoDeviceInfo(oni_DeviceInfo info) {
    const char * warn = "(warning: NULL)";
    printf("\tName: %s\n", info.name == NULL ? warn : info.name);
    printf("\tURI: %s\n", info.uri == NULL ? warn : info.uri);
    printf("\tUSB product ID: %d\n", info.usbProductId);
    printf("\tUSB vendor ID: %d\n", info.usbVendorId);
    printf("\tVendor: %s\n", info.vendor == NULL ? warn : info.vendor);
}

void deviceConnect(oni_DeviceInfo * info) {
    printf("Device connected:\n");
    echoDeviceInfo(*info);
}

void deviceDisconnect(oni_DeviceInfo * info) {
    printf("Device disconnected:\n");
    echoDeviceInfo(*info);
}

void deviceStateChange(oni_DeviceInfo * info, oni_DeviceState state) {
    printf("Device state change:\n");
    echoDeviceInfo(*info);
    printf("New device state: %d\n", state);
}

void echoSensorInfo(const oni_SensorInfo * info) {
    const char * sensorName = oni_getString_SensorType(oni_getSensorType(info));
    oni_VideoModeArray * modes = oni_getSupportedVideoModes(info);
    int modeCount = oni_getSize_VideoModeArray(modes);

    printf("Sensor type %s:\n", sensorName);
    if (modes == NULL) {
        printf("\tUnable to get list of video modes!\n");
    } else {
        int i;
        for (i = 0; i < modeCount; ++i) {
            oni_VideoMode * mode = oni_getElement_VideoModeArray(modes, i);
            printf("  FPS: %d; ", oni_getFps(mode));
            printf("PixelFormat: %s; ", oni_getString_PixelFormat(oni_getPixelFormat(mode)));
            printf("resolution X & Y: %dx%d\n", oni_getResolutionX(mode),
                   oni_getResolutionY(mode));
        }
    }
}
