#include "../support.h"

#include <FreeRTOSConfigLocal.h>
#include <modm/board.hpp>
#include <outpost/rtos/thread.h>

#include <modm/driver/temperature/ds18b20.hpp>
#include <modm/platform/1-wire/bitbang_master.hpp>

#include "temperature_sensor.h"
#include "ds18b20_temperature_sensor.hpp"
#include "lcd_task.h"
#include "temperature_monitoring.h"
#include "sensor_task.h"

using namespace Board;

// Correct GPIO pin for OneWire
using OneWirePin = GpioA3;

// Tasks
TemperatureMonitoring myTemperatureMonitoring;
LcdTask myLcdTask(myTemperatureMonitoring);
SensorTask mySensorTask(myTemperatureMonitoring);

int main()
{
    Rcc::configurePowerSource(Rcc::PowerSource::Ldo);
    Board::initialize();

    // Create DS18B20 sensor
    static hal::DS18B20_Temperature_Sensor<OneWirePin> tempSensorHw;
    hal::TemperatureSensor& tempSensor = tempSensorHw;

    mySensorTask.setSensor(&tempSensor);

    myLcdTask.start();
    mySensorTask.start();

    outpost::rtos::Thread::startScheduler();
    return 0;
}
