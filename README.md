# Temperature Monitoring FSM

## Overview

This system monitors temperature using a **DS18B20 sensor** and updates a **Finite State Machine (FSM)** for temperature-based logic. Output is logged to the development screen.

Components:

* **DS18B20 Temperature Sensor**: 1-Wire digital temperature sensor.
* **SensorTask**: Reads temperature and updates FSM.
* **TemperatureMonitoring FSM**: Maintains temperature state and triggers logic.

---

## 1. Sensor Initialization

1. The `DS18B20_Temperature_Sensor` class:

   * Detects the first DS18B20 sensor on the 1-Wire bus.
   * Prints its ROM for debugging.
   * Configures the sensor to **12-bit resolution** (~750 ms conversion).

2. Temperature is read via `measure_temp()`:

   * Starts conversion.
   * Waits until conversion is finished (`isConversionDone()`).
   * Reads raw temperature (`1 LSB = 1/16 °C`) and converts to °C.

---

## 2. SensorTask

* Runs periodically (every 8 seconds).
* **Steps**:

  1. Calls `read_sensor()` → fetches temperature from DS18B20.
  2. Calls `update_FSM()` → updates `TemperatureMonitoring` with the new value.
  3. Logs temperature to the **dev screen** for monitoring.

---

## 3. TemperatureMonitoring FSM

* Maintains temperature-related state.
* Example states:

| State      | Condition to enter   | Action                       |
| ---------- | -------------------- | ---------------------------- |
| **Normal** | 15 °C ≤ temp ≤ 30 °C | No action, LED off           |
| **High**   | temp > 30 °C         | Warning, LED slow      .     |
| **Low**    | temp < 15 °C         | Critical, LED fast           |

* FSM updates each cycle via `setTemperature(sensorValue)`.
* Can be extended for hysteresis, alerts, or other temperature-based logic.

---

## 4. Key Design Points

1. **Single sensor usage**: Only the first DS18B20 is used, avoiding conflicts.
2. **Blocking conversion handling**: `measure_temp()` ensures a valid reading.
3. **Separation of concerns**:

   * SensorTask → acquisition
   * FSM → logic
   * Dev screen → output/log

---
