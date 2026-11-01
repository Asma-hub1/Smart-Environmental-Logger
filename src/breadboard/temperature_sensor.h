#ifndef HAL_TEMPERATURE_SENSOR_H_
#define HAL_TEMPERATURE_SENSOR_H_

#include <cstdint>

namespace hal
{

class TemperatureSensor
{
public:
    TemperatureSensor() = default;
    virtual ~TemperatureSensor() = default;

    virtual int16_t
    measure_temp() = 0;

};
}

#endif /* HAL_TEMPERATURE_SENSOR_H_ */