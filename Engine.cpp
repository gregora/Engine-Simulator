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
    fuel_injection_mass = 3.08641975e-7;
    fuel_injected = false;
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

    angular_velocity += (total_torque / flywheel_inertia) * dt;
    angle += angular_velocity * dt;

    float dT = - R_spec * temperature * dV / (V*c_v); // Change in temperature
    temperature += dT;

    valves();

}

void Engine::valves(){
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