#ifndef FOUR_STROKE_H
#define FOUR_STROKE_H

#include "Engine.h"

class FourStroke : public Engine {
public:
    void valves() override;
private:
    bool fuel_injected = false;
};


#endif // FOUR_STROKE_H