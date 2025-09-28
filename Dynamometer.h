#ifndef DYNAMOMETER_H
#define DYNAMOMETER_H

#include "Engine.h"

class Dynamometer {
public:
    Dynamometer(Engine* engine);

    void run_test(float duration, float load_torque, float min_injection, float max_injection);

    void apply_load(float load_torque);

    Engine* engine;

    int samples = 100;
    float* rpm_results;
    float* power_results;

};

#endif // DYNAMOMETER_H