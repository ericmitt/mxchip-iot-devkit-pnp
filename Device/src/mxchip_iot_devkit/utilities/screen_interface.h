/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 3/3/2020
 ***********************************************************************************************/

#ifndef SCREEN_INTERFACE_H
#define SCREEN_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "digitaltwin_interface_client.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/threadapi.h"

#include "digitaltwin_client_helper.h"
#include "digitaltwin_serializer.h"
#include "parson.h"
#include "../mxchip_iot_devkit_impl.h"

#ifdef __cplusplus
extern "C"
{
#endif

// DigitalTwin interface name from service perspective.
static const char ScreenInterfaceId[] = "urn:mxchip:screen:1";
static const char ScreenInterfaceInstanceName[] = "screen";

// Telemetry names for this interface.

// Property names for this interface.

// Command names for this interface

#define ScreenInterface_EchoCommand "echo"

#define ScreenInterface_CountdownCommand "countdown"

// Methods
DIGITALTWIN_INTERFACE_CLIENT_HANDLE ScreenInterface_Create();

void ScreenInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle);

#ifdef __cplusplus
}
#endif

#endif  // SCREEN_INTERFACE_H
