#ifndef BB_DRV_DS18B20_TEMPERATURE_SENSOR_H_
#define BB_DRV_DS18B20_TEMPERATURE_SENSOR_H_

#include "temperature_sensor.h"

#include <modm/board.hpp>
#include <modm/debug/logger.hpp>
#include <modm/platform/1-wire/bitbang_master.hpp>
#include <modm/driver/temperature/ds18b20.hpp>
#include <outpost/rtos/thread.h>

namespace hal
{

template <class OneWirePin>
class DS18B20_Temperature_Sensor : public hal::TemperatureSensor
{
    using OneWireMaster = modm::platform::BitBangOneWireMaster<OneWirePin>;

private:
    modm::Ds18b20<OneWireMaster> ds18b20_;
    uint8_t rom_[8];

public:
    DS18B20_Temperature_Sensor()
        : ds18b20_(rom_)
    {
        // Initialize 1-Wire bus
        OneWireMaster::template connect<typename OneWirePin::BitBang>();
        OneWireMaster::template initialize<Board::SystemClock>();

        if (!OneWireMaster::touchReset())
        {
            modm::log::info << "No devices on 1-Wire bus!" << modm::endl;
            while (true) {}
        }

        // Reset search for DS18B20 family (0x28)
        OneWireMaster::resetSearch(0x28);

        // Find the first sensor
        if (!OneWireMaster::searchNext(rom_))
        {
            modm::log::info << "No DS18B20 sensor found!" << modm::endl;
            while (true) {}
        }

        // Print ROM properly (2-digit hex per byte)
        modm::log::info << "Found DS18B20 ROM: ";
        for (uint8_t i = 0; i < 8; ++i)
        {
            if (rom_[i] < 0x10) modm::log::info << '0';
            modm::log::info << modm::hex << int(rom_[i]) << " ";
        }
        modm::log::info << modm::endl;

        // Initialize DS18B20 with the first valid ROM
        ds18b20_ = modm::Ds18b20<OneWireMaster>(rom_);

        // 12-bit resolution → ~750 ms conversion
        ds18b20_.configure(modm::ds18b20::Resolution::Bits12);
    }

    ~DS18B20_Temperature_Sensor() = default;

    int16_t measure_temp() override
    {
        int16_t real = 100;
        // Start temperature conversion
        ds18b20_.startConversion();

        // Wait until conversion is finished
        while (!ds18b20_.isConversionDone())
        {
            outpost::rtos::Thread::sleep(outpost::time::Milliseconds(100));
        }

        // Read raw temperature (1 LSB = 1/16 °C)
        int16_t raw = ds18b20_.readTemperature();

        // Return real °C
        return raw / 16 - real;
    }
};

} // namespace hal

#endif
