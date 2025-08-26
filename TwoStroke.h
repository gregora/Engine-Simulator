#include "math.h"

#define ambient_pressure 101325.0
#define R_spec 287.05 // Specific gas constant for air in J/(kg·K)
#define c_v 718.0 // Specific heat capacity at constant volume for air in J/(kg·K)
#define air_density 1.225 // kg/m^3

class TwoStroke {
public:
    void apply_torque(float torque);
    void update(float dt);

    float angle = 0.0;
    float angular_velocity = 0.0;
    float external_torque = 0.0;

    float temperature = 298.0; // kelvin
    float pressure = ambient_pressure; // pascals

    float piston_length = 0.12; // meters
    float crank_radius = 0.05; // meters
    float piston_area = 0.01; // square meters

    float flywheel_inertia = 5; // kg*m^2

    float flywheel_damping = 4; // Damping coefficient for the flywheel

private:
};