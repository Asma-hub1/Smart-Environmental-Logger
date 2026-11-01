# Temperature Monitoring FSM

## Overview
This finite state machine (FSM) monitors temperature data from a DS18B20 sensor  
and classifies the system state into **Normal**, **Warning**, or **Critical**.  
The FSM prevents state oscillation by using **hysteresis**.

System feedback is provided via:
- UART logging on the development screen  
- LED signaling based on the current FSM state  

No LCD is involved.

---

## States

### 1. NORMAL
- **Condition**: Temperature is within the safe range  
- **Indicator**: Green LED steady (no alert)  
- **Purpose**: Default operating state  

---

### 2. WARNING
- **Condition**: Temperature elevated but not dangerous  
- **Indicator**: Yellow LED slow blinking (≈ 1 s period)  
- **Purpose**: Early warning to the user  

---

### 3. CRITICAL
- **Condition**: Temperature dangerously high  
- **Indicator**: Red LED very fast blinking (**1 ms toggle interval**)  
- **Purpose**: Immediate attention required  

---

## State Transitions

Hysteresis is applied to avoid rapid switching when the temperature is near threshold values.

### NORMAL → WARNING
- Trigger: `temperature ≥ 30°C`

### WARNING → NORMAL
- Trigger: `temperature ≤ 28°C`

### WARNING → CRITICAL
- Trigger: `temperature ≥ 40°C`

### CRITICAL → WARNING
- Trigger: `temperature ≤ 38°C`

### CRITICAL → NORMAL
- Trigger: `temperature ≤ 28°C`

---

## Timing Behavior
- FSM evaluation occurs once per sensor update  
- LED behavior is derived from FSM state  
- Blink timing is implemented in the RTOS task, not inside the FSM  
- CRITICAL state uses a **1 ms RTOS delay** to maximize visual urgency  

---

## Run & Test

Compile and run the FSM and its unit tests using Google Test:

```bash
g++ -std=c++17 fsm.cpp fsm_test.cpp -lgtest_main -lgtest -lpthread -o fsm_test
./fsm_test
