#include "Engine.h"
#include "TwoStroke.h"
#include "FourStroke.h"
#include "Dynamometer.h"
#include <string.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "EngineVisualization.h"
#include "include/ui.h"
#include "include/Video.h"

int main(int argc, char** argv) {

    float playback_speed = 0.1f;
    float framerate = 60.0f;

    int engine_type = 0;
    Engine* engine_ptr = nullptr;

    bool render = false;
    Video* video = NULL;

    for(int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-engine") == 0 && i + 1 < argc) {
            engine_type = atof(argv[i + 1]);
        } else if (strcmp(argv[i], "-render") == 0 && i + 1 < argc) {
            render = atof(argv[i + 1]) != 0;
        }
    }


    if (render) {
        video = new Video(800, 600, framerate, "render/output.mp4");
    }

    float min_fuel_injection_mass = 0;

    // Yamaha RX100 engine parameters
    TwoStroke rx100;
    rx100.piston_area = 0.00196;
    rx100.crank_radius = 0.025;
    rx100.cilinder_height = 0.0583;
    rx100.flywheel_inertia = 0.1;
    rx100.flywheel_damping = 0.1;
    rx100.init();

    // Honda K20 engine parameters
    FourStroke k20;
    k20.piston_area = 0.0058088;
    k20.crank_radius = 0.0430;
    k20.cilinder_height = 0.09419;
    k20.flywheel_inertia = 0.25;
    k20.flywheel_damping = 0.1;
    k20.init();


    if (engine_type == 0) {
        min_fuel_injection_mass = 3.1e-6;
        engine_ptr = (Engine*) &rx100;
    } else if (engine_type == 1) {
        min_fuel_injection_mass = 7.1e-6;
        engine_ptr = (Engine*) &k20;
    }

    Engine& engine = *engine_ptr;


    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Simulation");
    EngineVisualization visualization(engine);
    if(engine_type == 0) {
        visualization.piston_height = 0.04f;
    } else if (engine_type == 1) {
        visualization.piston_height = 0.06f;
    }

    visualization.init();

    float throttle = 0.0f;
    Bar throttle_bar("Throttle");
    throttle_bar.horizontal = false;
    throttle_bar.setPosition(730, 460);
    throttle_bar.setScale(0.8, 0.8);

    Button starter('S');
    starter.setPosition(580, 410);
    starter.setScale(1, 1);

    Gauge g("RPM", 0, 6000);
    g.setPosition(30, 420);
    g.scale(0.35f, 0.35f);

    int chart_length = 1000;

    Chart pressure_chart("Pressure", 0, 4 * M_PI, ambient_pressure, 20000000, 200, 150);
    pressure_chart.setPosition(570, 30);
    pressure_chart.values_x.reserve(chart_length);
    pressure_chart.values_y.reserve(chart_length);
    pressure_chart.line_color = sf::Color(0, 200, 200);

    Chart temperature_chart("Temperature", 0, 4 * M_PI, 293, 10000, 200, 150);
    temperature_chart.setPosition(570, 200);
    temperature_chart.values_x.reserve(chart_length);
    temperature_chart.values_y.reserve(chart_length);
    temperature_chart.line_color = sf::Color(200, 100, 0);

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
    float dt = 0.00003f;

    float delta_angle = 4.0f * M_PI / chart_length; // for charts
    float last_angle = -delta_angle;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                if (render) {
                    video->release();
                }
            }
            // scroll wheel as a throttle
            if (event.type == sf::Event::MouseWheelScrolled) {
                throttle += event.mouseWheelScroll.delta / 20;
            
                if (throttle > 1.0f) {
                    throttle = 1.0f;
                }else if (throttle < 0.0f) {
                    throttle = 0.0f;
                }

                engine.fuel_injection_mass = (5.0f * throttle) * min_fuel_injection_mass;
            }
        }

        // check if s is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (engine_type == 0) {
                engine.apply_torque(30.0f);
            } else if (engine_type == 1) {
                engine.apply_torque(60.0f);
            }
            starter.active = true;
        }else {
            engine.apply_torque(0.0f);
            starter.active = false;
        }

        int updates = (float) (playback_speed / framerate / dt);

        for (int i = 0; i < updates; i++) {
            t += dt;
            engine.update(dt);

            if (engine.angle - last_angle >= delta_angle) {

                last_angle = engine.angle;

                pressure_chart.values_x.push_back(engine.angle);
                pressure_chart.values_y.push_back(engine.pressure);
                temperature_chart.values_x.push_back(engine.angle);
                temperature_chart.values_y.push_back(engine.temperature);

                // delete old values
                for(int j = 0; j < pressure_chart.values_x.size() - chart_length; j++){
                    if(pressure_chart.values_x.at(j) < engine.angle - 4 * M_PI){
                        pressure_chart.values_x.erase(pressure_chart.values_x.begin());
                        pressure_chart.values_y.erase(pressure_chart.values_y.begin());

                        temperature_chart.values_x.erase(temperature_chart.values_x.begin());
                        temperature_chart.values_y.erase(temperature_chart.values_y.begin());
                    }else{
                        break;
                    }
                }

                pressure_chart.min_x = pressure_chart.values_x.back() - 4*M_PI;
                pressure_chart.max_x = pressure_chart.values_x.back();
                temperature_chart.min_x = temperature_chart.values_x.back() - 4*M_PI;
                temperature_chart.max_x = temperature_chart.values_x.back();

            }
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

        throttle_bar.value = throttle;

        visualization.update();  // Update the visualization
        window.clear();
    
        window.draw(visualization);
        window.draw(time_text);
        window.draw(playback_text);
        window.draw(g);
        window.draw(pressure_chart);
        window.draw(temperature_chart);
        window.draw(throttle_bar);
        window.draw(starter);
        window.display();

        if (render) {
            sf::Texture texture;
            texture.create(800, 600);
            texture.update(window);
            sf::Image screenshot = texture.copyToImage();
            video->write((uint8_t*)screenshot.getPixelsPtr());
        }
    
    }

    return 0;
}