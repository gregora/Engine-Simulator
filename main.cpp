#include "TwoStroke.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"
#include "include/ui.h"

int main(){
    TwoStroke engine;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);

    Gauge g("RPM", 0, 6000);
    g.setPosition(30, 400);
    g.scale(0.4f, 0.4f);

    sf::Font font;
    font.loadFromFile("fonts/Prototype.ttf");
    
    sf::Text time_text;
    time_text.setFont(font);
    time_text.setCharacterSize(20);
    time_text.setFillColor(sf::Color::White);
    time_text.setPosition(10, 10);

    sf::Text playback_text;
    playback_text.setFont(font);
    playback_text.setCharacterSize(24);
    playback_text.setFillColor(sf::Color::White);
    playback_text.setPosition(10, 50);

    visualization.setPosition(400, 200);
    visualization.setScale(1.5f, 1.5f);

    float t = 0;
    float dt = 0.0003f;

    float playback_speed = 0.1f;

    float framerate = 60.0f;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (t < 1.0f) {
            engine.apply_torque(30.0f);
        }else{
            engine.apply_torque(0.0f);
        }

        int updates = (float) (playback_speed / framerate / dt);

        for (int i = 0; i < updates; i++) {
            t += dt;
            engine.update(dt);
        }

        // sleep
        sf::sleep(sf::milliseconds(16));

        time_text.setString("Time: " + std::to_string(t) + "s");
        playback_text.setString(std::to_string(playback_speed) + "x");

        g.value = 30 * engine.angular_velocity / M_PI;

        visualization.update();  // Update the visualization
        window.clear();
    
        window.draw(visualization);
        window.draw(time_text);
        window.draw(playback_text);
        window.draw(g);
        window.display();
    
    }

    return 0;
}