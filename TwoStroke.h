#ifndef TWO_STROKE_H
#define TWO_STROKE_H

#include "Engine.h"

class TwoStroke : public Engine {
public:
    void valves() override;

    float fuel_injection_mass = 0.0; // kg
    bool fuel_injected = false;
};


#endif // TWO_STROKE_H