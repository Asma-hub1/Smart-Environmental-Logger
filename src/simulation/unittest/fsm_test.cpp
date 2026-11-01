#include "fsm.h"
#include <iostream>
#include <chrono>
#include <cassert>

int main() {
    TemperatureFSM fsm;

    auto start = std::chrono::high_resolution_clock::now();
    assert(fsm.getState() == State::NORMAL);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "[Test] InitialState: " 
              << "State = NORMAL, "
              << "Elapsed = " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
              << " ns\n";

    start = std::chrono::high_resolution_clock::now();
    fsm.update(30.0f); // NORMAL -> WARNING
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Test] NormalToWarning: " 
              << "State = " << (fsm.getState() == State::WARNING ? "WARNING" : "ERROR") << ", "
              << "Elapsed = " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
              << " ns\n";

    start = std::chrono::high_resolution_clock::now();
    fsm.update(40.0f); // WARNING -> CRITICAL
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Test] WarningToCritical: " 
              << "State = " << (fsm.getState() == State::CRITICAL ? "CRITICAL" : "ERROR") << ", "
              << "Elapsed = " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
              << " ns\n";

    start = std::chrono::high_resolution_clock::now();
    fsm.update(38.0f); // CRITICAL -> WARNING
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Test] CriticalToWarning: " 
              << "State = " << (fsm.getState() == State::WARNING ? "WARNING" : "ERROR") << ", "
              << "Elapsed = " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
              << " ns\n";

    start = std::chrono::high_resolution_clock::now();
    fsm.update(28.0f); // WARNING -> NORMAL
    end = std::chrono::high_resolution_clock::now();
    std::cout << "[Test] WarningToNormal: " 
              << "State = " << (fsm.getState() == State::NORMAL ? "NORMAL" : "ERROR") << ", "
              << "Elapsed = " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() 
              << " ns\n";

    std::cout << "All FSM tests passed!" << std::endl;
    return 0;
}
