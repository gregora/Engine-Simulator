#include "TwoStroke.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"

int main(){
    TwoStroke engine;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);

    sf::Text time_text;

    visualization.setPosition(400, 300);

    float t = 0;
    float dt = 0.000003f;

    float playback_speed = 0.1f;

    float framerate = 60;

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

        int updates = (float) (playback_speed / framerate / dt);

        for (int i = 0; i < updates; i++) {
            engine.update(dt);
        }

        // sleep
        sf::sleep(sf::milliseconds(16));

        visualization.update();  // Update the visualization
        window.clear();
    
        window.draw(visualization);
        window.display();
    
        t += dt;
    }

    return 0;
}