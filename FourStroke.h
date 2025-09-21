#ifndef FOUR_STROKE_H
#define FOUR_STROKE_H

#include "Engine.h"

class FourStroke : public Engine {
public:
    void valves() override;

    float fuel_injection_mass = 0.0; // kg
    bool fuel_injected = false;
};


#endif // FOUR_STROKE_H