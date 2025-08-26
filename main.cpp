#include "TwoStroke.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"

int main(){
    TwoStroke engine;

    engine.apply_torque(50.0);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);

    visualization.setPosition(400, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // sleep
        sf::sleep(sf::milliseconds(30));

        engine.update(0.016f); // Update the engine simulation
        visualization.update();  // Update the visualization

        window.clear();
        window.draw(visualization);
        window.display();
    }

    return 0;
}