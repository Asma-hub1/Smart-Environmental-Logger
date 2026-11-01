/*
 * Authors: Janina
 * dummy sensor task
*/

#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include<cstdint>

#include <outpost/rtos.h>
#include <outpost/rtos/thread.h>

#include"temperature_monitoring.h"
#include"temperature_sensor.h"

class SensorTask : public outpost::rtos::Thread
{
    public:
    SensorTask(TemperatureMonitoring& temperatureMonitoring):
        outpost::rtos::Thread(0),
        mTempMonitoring(temperatureMonitoring),
        mTempSensor(NULL)
    {
        this->sensorValue = 0;
    }

    void setSensor(hal::TemperatureSensor* tempSensor)
    {
        mTempSensor = tempSensor;
    }

    ~SensorTask() = default;

    void run();

    private:

    TemperatureMonitoring& mTempMonitoring;
    hal::TemperatureSensor* mTempSensor;

    uint16_t sensorValue;

    void read_sensor();
    void update_FSM();

};

#endif