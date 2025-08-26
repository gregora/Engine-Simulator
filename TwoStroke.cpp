#include "TwoStroke.h"
#include <stdio.h>

void TwoStroke::apply_torque(float torque){
    this->external_torque = torque;
}

void TwoStroke::update(float dt) {
    // Update the engine's state based on the applied torque and other factors

    float piston_force = (pressure - ambient_pressure) * piston_area;
    printf("Piston Force: %f\n", piston_force);

    float total_torque = -piston_force*crank_radius*cos(angle) + external_torque;

    angular_velocity += (total_torque / flywheel_inertia) * dt;
    angle += angular_velocity * dt;

    float  x = (1 + sin(angle)) * crank_radius;
    float dx = cos(angle)* angular_velocity * crank_radius * dt;

    float  V = (piston_length - x) * piston_area;
    float dV = - dx * piston_area; // Change in volume

    float dT = - R_spec * temperature * dV / (V*c_v); // Change in temperature
    pressure = (air_density * R_spec * temperature); // Ideal gas law

    temperature += dT;

}