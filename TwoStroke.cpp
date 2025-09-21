#include "TwoStroke.h"

void TwoStroke::valves() {
    float  x = (1 + sin(angle)) * crank_radius;
    float  V = (cilinder_height - x) * piston_area;

    float cycle_position = fmod(angle, 2 * M_PI);

    // explosion
    if(!fuel_injected && cycle_position > M_PI / 2 && cycle_position < M_PI) {
        fuel_injected = true;
        float energy_released = fuel_injection_mass * fuel_energy_density; // J
        float dT_explosion = energy_released / air_mass / c_v; // Temperature increase due to explosion
        temperature += dT_explosion;
    }

    // exhaust
    if(cycle_position > 3 * M_PI / 2 && cycle_position < 4 * M_PI / 2) {
        temperature = 298;
        air_mass = (V * air_density); // Reset air mass in the cylinder
    }

    if(cycle_position >= M_PI) {
        fuel_injected = false;
    }
 
}