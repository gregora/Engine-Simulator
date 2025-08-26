#include "TwoStroke.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"

int main(){
    TwoStroke engine;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);

    visualization.setPosition(400, 300);

    float t = 0;
    float dt = 0.0003f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (t < 1.0f) {
            engine.apply_torque(500.0f);
        }else{
            engine.apply_torque(0.0f);
        }

        engine.update(dt); // Update the engine simulation
        visualization.update();  // Update the visualization

        // sleep
        sf::sleep(sf::milliseconds(1));

        window.clear();
        window.draw(visualization);
        window.display();
    
        t += dt;
    }

    return 0;
}