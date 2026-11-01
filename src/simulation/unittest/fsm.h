// fsm.h
#pragma once

enum class State { NORMAL, WARNING, CRITICAL };

class TemperatureFSM {
public:
    TemperatureFSM() : state(State::NORMAL) {}
    State getState() const { return state; }
    void update(float temp);

private:
    State state;
};
