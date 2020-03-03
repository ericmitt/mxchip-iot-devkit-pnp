﻿/*******************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.8.
 *
 * You need to add your implementation here to:
 *    - get telemetry data from device/sensor
 *    - set read-only property data
 *    - handle read-write property callback
 *    - process device command
 *
 * Generated Date: 3/3/2020
 *******************************************************************************************/

#include "IoT_DevKit_HW.h"
#include "mxchip_iot_devkit_impl.h"
#include "utilities/digitaltwin_serializer.h"
#include "utilities/deviceinfo_interface.h"
#include "utilities/sensors_interface.h"
#include "utilities/leds_interface.h"
#include "utilities/screen_interface.h"
#include "utilities/settings_interface.h"

#include "ui/screen.h"
#include "ui/screen_animation.h"

#include "pnp_statistics.h"

#define Payload_Buffer_Size 256

double Sensors_Telemetry_ReadHumidity()
{
    return getDevKitHumidityValue();
}

double Sensors_Telemetry_ReadTemperature()
{
    return getDevKitTemperatureValue(0);
}

double Sensors_Telemetry_ReadPressure()
{
    return getDevKitPressureValue();
}

void Sensors_Telemetry_ReadMagnetometer(SENSORS_MAGNETOMETER * magnetometer)
{
    if (magnetometer)
    {
        getDevKitMagnetometerValue(&magnetometer->x, &magnetometer->y, &magnetometer->z);
    }
}

void Sensors_Telemetry_ReadGyroscope(SENSORS_GYROSCOPE * gyroscope)
{
    if (gyroscope)
    {
        getDevKitGyroscopeValue(&gyroscope->x, &gyroscope->y, &gyroscope->z);
    }
}

void Sensors_Telemetry_ReadAccelerometer(SENSORS_ACCELEROMETER * accelerometer)
{
    if (accelerometer)
    {
        getDevKitAcceleratorValue(&accelerometer->x, &accelerometer->y, &accelerometer->z);
    }
}

void SendTelemetry_Succeeded_Callback(const char* interfaceName)
{
    telemetry_sent_inc();
}

void SendTelemetry_Error_Callback(const char* interfaceName)
{
    error_inc();
}

void ReportProperty_Succeeded_Callback(const char* interfaceName, const char* propertyName)
{
    int last_setting_change = 0;
    int last_setting_value = 0;
    get_last_setting_change(&last_setting_change, &last_setting_value);
    if (get_telemetry_sent_number() > 0)
    {
        switch(last_setting_change)
        {
        case SETTING_CHANGE_FANSPEED:
            play_fanspeed_animation(last_setting_value);
            break;
        case SETTING_CHANGE_CURRENT:
            play_current_animation(last_setting_value);
            break;
        case SETTING_CHANGE_VOLTAGE:
            play_voltage_animation(last_setting_value);
            break;
        case SETTING_CHANGE_IRDA:
            play_irda_animation(last_setting_value);
            break;
        }
    }
    setting_change(SETTING_CHANGE_NONE, 0);
}

void ReportProperty_Error_Callback(const char* interfaceName, const char* propertyName)
{
    setting_change(SETTING_CHANGE_NONE, 0);
    error_inc();
}

char* Deviceinfo_Property_GetManufacturer()
{
    return "MXChip";
}

char* Deviceinfo_Property_GetModel()
{
    return "AZ3166";
}

char* Deviceinfo_Property_GetSwVersion()
{
    return "1.0.0";
}

char* Deviceinfo_Property_GetOsName()
{
    return "Arm Mbed OS v5.2";
}

char* Deviceinfo_Property_GetProcessorArchitecture()
{
    return "Arm Cortex M4";
}

char* Deviceinfo_Property_GetProcessorManufacturer()
{
    return "STMicro";
}

long Deviceinfo_Property_GetTotalStorage()
{
    return  2048L;
}

long Deviceinfo_Property_GetTotalMemory()
{
    return 256L;
}

bool Settings_Property_FanSpeedCallback(double fanSpeed)
{
    setting_change(SETTING_CHANGE_FANSPEED, (int)fanSpeed);
    return true;
}

bool Settings_Property_VoltageCallback(double voltage)
{
    setting_change(SETTING_CHANGE_VOLTAGE, (int)voltage);
    return true;
}

bool Settings_Property_CurrentCallback(double current)
{
    setting_change(SETTING_CHANGE_CURRENT, (int)current);
    return true;
}

bool Settings_Property_IrSwitchCallback(bool irSwitch)
{
    setting_change(SETTING_CHANGE_IRDA, (int)irSwitch);
    return true;
}

DIGITALTWIN_COMMAND_RESULT Leds_Command_Blink(long interval, LEDS_BLINK_blinkResponse* response, unsigned int* statusCode)
{
    if (interval > 0 && interval < 60)
    {
        startBlinkDevKitRGBLED(interval * 1000);
        response->description = "Start blinking";
    }
    else
    {
        response->description = "Invalid interval";
    }
    
    *statusCode = 200;
    LogInfo("Device executed 'blink' command successfully");
    return DIGITALTWIN_COMMAND_OK;
}

DIGITALTWIN_COMMAND_RESULT Leds_Command_TurnOnLed(unsigned int* statusCode)
{
    turnOnUserLED();
    *statusCode = 200;
    LogInfo("Execute 'turnOnLed' command successfully");
    return DIGITALTWIN_COMMAND_OK;
}

DIGITALTWIN_COMMAND_RESULT Leds_Command_TurnOffLed(unsigned int* statusCode)
{
    turnOffUserLED();
    *statusCode = 200;
    LogInfo("Execute 'turnOffLed' command successfully");
    return DIGITALTWIN_COMMAND_OK;
}

DIGITALTWIN_COMMAND_RESULT Screen_Command_Echo(char* text, SCREEN_ECHO_echoResponse* response, unsigned int* statusCode)
{
    LogInfo("Parameter: text = %s", text);

    screen_echo(text);

    response->echo = text;

    *statusCode = 200;
    LogInfo("Device executed 'echo' command successfully");
    return DIGITALTWIN_COMMAND_OK;
}

DIGITALTWIN_COMMAND_RESULT Screen_Command_Countdown(int number, unsigned int* statusCode)
{
    LogInfo("Countdown number = %d", number);
        
    play_countdown_animation(number);

    *statusCode = 200;
    LogInfo("Execute 'countdown' command successfully");
    return DIGITALTWIN_COMMAND_OK;
}

bool Settings_Property_FanSpeedCallback(double fanSpeed)
{
    // TODO: provide implementation here
    LogInfo("FanSpeed property new value: %f", fanSpeed);
    return true;
}

bool Settings_Property_VoltageCallback(double voltage)
{
    // TODO: provide implementation here
    LogInfo("Voltage property new value: %f", voltage);
    return true;
}

bool Settings_Property_CurrentCallback(double current)
{
    // TODO: provide implementation here
    LogInfo("Current property new value: %f", current);
    return true;
}

bool Settings_Property_IrSwitchCallback(bool irSwitch)
{
    // TODO: provide implementation here
    LogInfo("IrSwitch property new value: %d", irSwitch);
    return true;
}

