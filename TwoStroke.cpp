#include "TwoStroke.h"

void TwoStroke::valves() {
    float  x = (1 + sin(angle)) * crank_radius;
    float  V = (cilinder_height - x) * piston_area;

    float cycle_position = fmod(angle, 2 * M_PI);

    // combustion
    if(!fuel_injected && cycle_position > 1.0/2 * M_PI && cycle_position < 2.0/2*M_PI) {
        fuel_injected = true;
        float energy_released = fuel_injection_mass * fuel_energy_density; // J
        float dT_explosion = energy_released / air_mass / c_v; // Temperature increase due to explosion
        temperature += dT_explosion;
    }

    //  exhaust + intake
    if(cycle_position > 2.8/2 * M_PI && cycle_position < 3.2/2 * M_PI) {
        temperature = 298;
        air_mass = (V * air_density); // Reset air mass in the cylinder
    }

    if(cycle_position >= M_PI) {
        fuel_injected = false;
    }
 
}