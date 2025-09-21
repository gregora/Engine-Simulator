#include "Engine.h"
#include "TwoStroke.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"
#include "include/ui.h"

int main(){

    float playback_speed = 0.1f;
    float framerate = 60.0f;


    // Yamaha RX100 engine parameters
    TwoStroke engine;
    engine.piston_area = 0.00196;
    engine.crank_radius = 0.025;
    engine.cilinder_height = 0.0583;
    engine.fuel_injection_mass = 3.08641975e-7;
    engine.init();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);
    visualization.piston_height = 0.04f;
    visualization.init();

    Gauge g("RPM", 0, 6000);
    g.setPosition(30, 420);
    g.scale(0.35f, 0.35f);

    sf::Font font;
    font.loadFromFile("fonts/Prototype.ttf");
    
    sf::Text time_text;
    time_text.setFont(font);
    time_text.setCharacterSize(20);
    time_text.setFillColor(sf::Color::White);
    time_text.setPosition(10, 10);

    sf::Text playback_text;
    playback_text.setFont(font);
    playback_text.setCharacterSize(28);
    playback_text.setFillColor(sf::Color::White);
    playback_text.setPosition(10, 50);

    visualization.setPosition(400, 200);
    visualization.setScale(2.0f, 2.0f);

    float t = 0;
    float dt = 0.0003f;


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (t < 0.5f) {
            engine.apply_torque(20.0f);
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
        char text1[100];
        sprintf(text1, "Time: %.3fs", t);
        time_text.setString(text1);

        char text2[100];
        sprintf(text2, "%.2fx", playback_speed);
        playback_text.setString(text2);

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