#include "temperature_monitoring.h"

void TemperatureMonitoring::changeUnit(Unit newUnit)
{
    this->unit = newUnit;
}

Unit TemperatureMonitoring::getUnit()
{
    return this->unit;
}

int16_t TemperatureMonitoring::getTemperature()
{
    return this->temperature;
}

void TemperatureMonitoring::setTemperature(int16_t newTemperature)
{
    this->temperature = newTemperature;

    // -------- FSM with hysteresis --------
    switch (state)
    {
        case State::NORMAL:
            if (temperature >= 30)
                state = State::WARNING;
            break;

        case State::WARNING:
            if (temperature >= 40)
                state = State::CRITICAL;
            else if (temperature <= 28)
                state = State::NORMAL;
            break;

        case State::CRITICAL:
            if (temperature <= 38)
                state = State::WARNING;
            else if (temperature <= 28)
                state = State::NORMAL;
            break;
    }
}

TemperatureMonitoring::State
TemperatureMonitoring::getState() const
{
    return state;
}
