#include "Engine.h"
#include <stdio.h>

void Engine::init(){
    angle = 0.0;
    angular_velocity = 0.0;
    external_torque = 0.0;

    float  x = (1 + sin(angle)) * crank_radius;
    float  V = (cilinder_height - x) * piston_area;

    air_mass = (V * air_density); // Initial air mass in the cylinder
    temperature = 298.0;
    pressure = ambient_pressure;
}


void Engine::apply_torque(float torque){
    this->external_torque = torque;
}

void Engine::update(float dt) {
    // Update the engine's state based on the applied torque and other factors
    float  x = (1 + sin(angle)) * crank_radius;
    float  V = (cilinder_height - x) * piston_area;

    float dx = cos(angle)* angular_velocity * crank_radius * dt;
    float dV = - dx * piston_area; // Change in volume

    pressure = air_mass / V * (R_spec * temperature); // Ideal gas law

    float piston_force = (pressure - ambient_pressure) * piston_area;

    float total_torque = -piston_force*crank_radius*cos(angle) + external_torque - (flywheel_damping * angular_velocity);

    if(abs(angular_velocity) > 0.0001){
        total_torque += - angular_velocity / abs(angular_velocity) * friction * crank_radius;
    }

    angular_velocity += (total_torque / flywheel_inertia) * dt;
    angle += angular_velocity * dt;

    float dT = - (pressure * dV) / (air_mass * c_v); // Change in temperature
    temperature += dT;

    valves();

}


void Engine::valves(){
    // Default implementation does nothing
}