#ifndef TWO_STROKE_H
#define TWO_STROKE_H

#include "Engine.h"

class TwoStroke : public Engine {
public:
    void valves() override;

private:
    bool fuel_injected = false;
};


#endif // TWO_STROKE_H