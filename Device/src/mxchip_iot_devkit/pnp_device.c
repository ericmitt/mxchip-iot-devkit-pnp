﻿/*********************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 *
 * Generated Date: 3/3/2020
 *********************************************************************************************/

#include "pnp_device.h"

// Number of Digital Twins interfaces that this device supports.
#define DIGITALTWIN_INTERFACE_NUM 5

#define DEVICEINFO_INDEX 0

#define SENSORS_INDEX 1

#define LEDS_INDEX 2

#define SCREEN_INDEX 3

#define SETTINGS_INDEX 4

#define DEFAULT_SEND_TELEMETRY_INTERVAL_MS 10000

#define DEVICE_CAPABILITY_MODEL_URI "urn:mxchip:mxchip_iot_devkit:1"

static DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceClientHandles[DIGITALTWIN_INTERFACE_NUM];
static TICK_COUNTER_HANDLE tickcounter = NULL;
static tickcounter_ms_t lastTickSend;

int pnp_device_initialize(const char* connectionString, const char* trustedCert)
{
    if ((tickcounter = tickcounter_create()) == NULL)
    {
        LogError("tickcounter_create failed");
        return -1;
    }

    DIGITALTWIN_DEVICE_CLIENT_LL_HANDLE digitalTwinDeviceClientHandle = NULL;
    memset(&interfaceClientHandles, 0, sizeof(interfaceClientHandles));

    // Initialize DigitalTwin device handle
    if ((digitalTwinDeviceClientHandle = DigitalTwinClientHelper_InitializeDeviceHandle(connectionString, false, trustedCert)) == NULL)
    {
        LogError("DigitalTwinClientHelper_InitializeDeviceHandle failed");
        return -1;
    }

    // Invoke to the ***Interface_Create - implemented in a separate library - to create DIGITALTWIN_INTERFACE_CLIENT_HANDLE.
    // NOTE: Other than creation and destruction, NO operations may occur on any DIGITALTWIN_INTERFACE_CLIENT_HANDLE
    // until after we've completed its registration (see DigitalTwinClientHelper_RegisterInterfacesAndWait).

    if ((interfaceClientHandles[DEVICEINFO_INDEX] = DeviceinfoInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("DeviceinfoInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[SENSORS_INDEX] = SensorsInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("SensorsInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[LEDS_INDEX] = LedsInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("LedsInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[SCREEN_INDEX] = ScreenInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("ScreenInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[SETTINGS_INDEX] = SettingsInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("SettingsInterface_Create failed");
        return -1;
    }

    // Register the interface(s) we've created with Azure IoT.  This call will block until interfaces
    // are successfully registered, we get a failure from server, or we timeout.
    if (DigitalTwinClientHelper_RegisterInterfacesAndWait(digitalTwinDeviceClientHandle, DEVICE_CAPABILITY_MODEL_URI, interfaceClientHandles, DIGITALTWIN_INTERFACE_NUM) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("DigitalTwinClientHelper_RegisterInterfacesAndWait failed");
        return -1;
    }

    DigitalTwinClientHelper_Check();

    // report properties

    DeviceinfoInterface_Property_ReportAll();

    tickcounter_get_current_ms(tickcounter, &lastTickSend);
    return 0;
}

void pnp_device_run()
{
    tickcounter_ms_t nowTick;
    tickcounter_get_current_ms(tickcounter, &nowTick);

    if (nowTick - lastTickSend >= DEFAULT_SEND_TELEMETRY_INTERVAL_MS)
    {
        LogInfo("Send telemetry data to IoT Hub");

        SensorsInterface_Telemetry_SendAll();

        tickcounter_get_current_ms(tickcounter, &lastTickSend);
    }
    else
    {
        // Just check data from IoT Hub
        DigitalTwinClientHelper_Check();
    }
}

void pnp_device_close()
{
    if (interfaceClientHandles[DEVICEINFO_INDEX] != NULL)
    {
        DeviceinfoInterface_Close(interfaceClientHandles[DEVICEINFO_INDEX]);
    }

    if (interfaceClientHandles[SENSORS_INDEX] != NULL)
    {
        SensorsInterface_Close(interfaceClientHandles[SENSORS_INDEX]);
    }

    if (interfaceClientHandles[LEDS_INDEX] != NULL)
    {
        LedsInterface_Close(interfaceClientHandles[LEDS_INDEX]);
    }

    if (interfaceClientHandles[SCREEN_INDEX] != NULL)
    {
        ScreenInterface_Close(interfaceClientHandles[SCREEN_INDEX]);
    }

    if (interfaceClientHandles[SETTINGS_INDEX] != NULL)
    {
        SettingsInterface_Close(interfaceClientHandles[SETTINGS_INDEX]);
    }

    DigitalTwinClientHelper_DeInitialize();
}
