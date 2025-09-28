#include "Dynamometer.h"

Dynamometer::Dynamometer(Engine* engine){
    this->engine = engine;
}

void Dynamometer::apply_load(float load_torque) {
    engine->apply_torque(load_torque);
}

void Dynamometer::run_test(float duration, float load_torque, float min_injection, float max_injection){
    engine->apply_torque(40); // start the engine

    rpm_results = new float[samples];
    power_results = new float[samples];

    float dt = 0.00001f;
    float t = 0;

    int i = 0;
    int sample = 0;

    while(t < duration + 0.5){

        engine->update(dt);

        if (t > 0.5){
            engine->apply_torque(load_torque* (t - 0.5) / duration);

            engine->fuel_injection_mass = (max_injection - min_injection) * (t - 0.5) / duration;
        
            if (i % (int) (duration / samples / dt) == 0){
                rpm_results[sample] = engine->angular_velocity / (2 * 3.1415) * 60;
                power_results[sample] = - engine->angular_velocity * load_torque;
                sample++;
                //printf("Engine RPM: %f\n", engine->angular_velocity / (2 * 3.1415) * 60);
                //printf("Engine power: %f\n", - engine->angular_velocity * load_torque);

            }
            i++;
        }




        t += dt;

    }

    engine->angular_velocity = 0;
    engine->angle = 0;
    engine->fuel_injection_mass = min_injection;
    engine->init();



}