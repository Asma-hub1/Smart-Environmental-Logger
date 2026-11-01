// fsm.cpp
#include "fsm.h"

void TemperatureFSM::update(float temp) {
    switch (state) {
        case State::NORMAL:
            if (temp >= 30.0f) state = State::WARNING;
            break;
        case State::WARNING:
            if (temp <= 28.0f) state = State::NORMAL;
            else if (temp >= 40.0f) state = State::CRITICAL;
            break;
        case State::CRITICAL:
            if (temp <= 28.0f) state = State::NORMAL;
            else if (temp <= 38.0f) state = State::WARNING;
            break;
    }
}
