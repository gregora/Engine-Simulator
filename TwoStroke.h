#ifndef TWO_STROKE_H
#define TWO_STROKE_H

#include "math.h"

#define ambient_pressure 101325.0
#define R_spec 287.05 // Specific gas constant for air in J/(kg·K)
#define c_v 718.0 // Specific heat capacity at constant volume for air in J/(kg·K)
#define air_density 1.225 // kg/m^3
#define fuel_energy_density 46.7e6 // J/kg

class TwoStroke {
public:
    void init();
    void apply_torque(float torque);
    void update(float dt);
    void valves();

    float angle = 0.0;
    float angular_velocity = 0.0;
    float external_torque = 0.0;

    float air_mass = 0.0005; // kg of air in the cylinder

    float temperature = 298.0; // kelvin
    float pressure = ambient_pressure; // pascals

    float cilinder_height = 0.08; // meters
    float crank_radius = 0.03; // meters
    float piston_area = 0.003; // square meters

    float flywheel_inertia = 0.1; // kg*m^2

    float flywheel_damping = 0.01; // Damping coefficient for the flywheel

private:
    float fuel_injection_mass = 0.0; // kg
    bool fuel_injected = false;
};

#endif // TWO_STROKE_H