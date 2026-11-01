#include "sensor_task.h"

#include <modm/board.hpp>
#include <modm/platform.hpp>
#include <modm/debug/logger.hpp>
#include <outpost/rtos/thread.h>

using namespace Board;

// Board-defined ST-Link UART logger
static LoggerDevice loggerDevice;
static modm::log::Logger myLogger(loggerDevice);

// LED pins
using LedGreen  = modm::platform::GpioOutputB0;
using LedYellow = modm::platform::GpioOutputE1;
using LedRed    = modm::platform::GpioOutputB14;

void SensorTask::run()
{
    // LED initialization (once)
    LedGreen::setOutput(false);
    LedYellow::setOutput(false);
    LedRed::setOutput(false);

    while (true)
    {
        // 1. Read temperature
        read_sensor();

        // 2. Update FSM
        update_FSM();

        // 3. Get FSM state
        auto state = mTempMonitoring.getState();

        // 4. FSM-driven LED behavior
        switch (state)
        {
            case TemperatureMonitoring::State::NORMAL:
                // Green steady, others off
                LedGreen::set();
                LedYellow::reset();
                LedRed::reset();
                outpost::rtos::Thread::sleep(outpost::time::Seconds(1));
                break;

            case TemperatureMonitoring::State::WARNING:
                // Yellow slow blink
                LedGreen::reset();
                LedRed::reset();
                LedYellow::toggle();
                outpost::rtos::Thread::sleep(outpost::time::Seconds(1));
                break;

            case TemperatureMonitoring::State::CRITICAL:
                // Red fast blink
                LedGreen::reset();
                LedYellow::reset();
                LedRed::toggle();
                outpost::rtos::Thread::sleep(outpost::time::Milliseconds(1));
                break;
        }

        // 5. Logging
        myLogger << "Temperature: "
                 << sensorValue
                 << " C | State: "
                 << static_cast<int>(state)
                 << modm::endl;
    }
}

void SensorTask::read_sensor()
{
    // Blocking call: starts conversion, waits, reads value
    sensorValue = mTempSensor->measure_temp();
}

void SensorTask::update_FSM()
{
    mTempMonitoring.setTemperature(sensorValue);
}
