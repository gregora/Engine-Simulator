#include "TwoStroke.h"
#include <stdio.h>

int main(){
    TwoStroke engine;

    engine.apply_torque(100.0);
    
    for(int i = 0; i < 1000; i++){
        engine.update(0.0001);
        //engine.apply_torque(0);

        printf("Angle: %f, Angular Velocity: %f, Temperature: %f, Pressure: %f\n",
               engine.angle, engine.angular_velocity, engine.temperature, engine.pressure);
    }
}