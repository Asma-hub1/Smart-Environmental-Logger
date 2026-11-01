#ifndef TEMPERATURE_MONITORING_H
#define TEMPERATURE_MONITORING_H

#include <cstdint>

enum Unit { CELSIUS, KELVIN, FAHRENHEIT };

class TemperatureMonitoring
{
public:
    // FSM states
    enum class State
    {
        NORMAL,
        WARNING,
        CRITICAL
    };

    TemperatureMonitoring()
        : temperature(0),
          unit(CELSIUS),
          state(State::NORMAL)
    {}

    // Existing interface
    void changeUnit(Unit newUnit);
    int16_t getTemperature();
    void setTemperature(int16_t newTemperature);
    Unit getUnit();

    // FSM interface (NEW)
    State getState() const;

private:
    int16_t temperature;
    Unit unit;

    // FSM state (NEW)
    State state;
};

#endif
