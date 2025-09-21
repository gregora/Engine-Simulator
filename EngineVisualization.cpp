#include "EngineVisualization.h"

EngineVisualization::EngineVisualization(Engine& engine) : engine(engine) {
    init();
}

void EngineVisualization::init() {
   // Initialize the visualization

    float piston_width = sqrt(engine.piston_area / M_PI) * 2;

    cilinder.setSize(sf::Vector2f(500 * piston_width, engine.cilinder_height * 500 + piston_height * 500));
    cilinder.setOrigin(500 * piston_width / 2, 0);
    cilinder.setFillColor(sf::Color(5, 5, 5));
    cilinder.setPosition(0, 0);
    cilinder.setOutlineThickness(500 * piston_width / 3);
    cilinder.setOutlineColor(sf::Color(25, 25, 25));

    piston.setSize(sf::Vector2f(500 * piston_width, 500 * piston_height));
    piston.setOrigin(500 * piston_width / 2, 0);
    piston.setFillColor(sf::Color(100, 100, 100));

    piston_seal.setSize(sf::Vector2f(500 * piston_width, 500 * piston_height / 10));
    piston_seal.setOrigin(500 * piston_width / 2, 0);
    piston_seal.setFillColor(sf::Color(50, 50, 50));

    piston_seal2.setSize(sf::Vector2f(500 * piston_width, 500 * piston_height / 10));
    piston_seal2.setOrigin(500 * piston_width / 2, 0);
    piston_seal2.setFillColor(sf::Color(50, 50, 50));

    volume.setOrigin(500 * piston_width / 2, 0);

    rod.setFillColor(sf::Color(70, 70, 70));
    rod.setSize(sf::Vector2f(piston_width / 3 * 500, 2 * engine.crank_radius * 500));
    rod.setOrigin(piston_width / 6 * 500, 0);

    rod_end.setRadius(piston_width * 500 / 6);
    rod_end.setOrigin(piston_width * 500 / 6, piston_width * 500 / 6);
    rod_end.setFillColor(sf::Color(70, 70, 70));

    counterweight_texture.loadFromFile("textures/counterweight.png");

    counterweight.setTexture(counterweight_texture);
    counterweight.setOrigin(counterweight_texture.getSize().x / 2, counterweight_texture.getSize().y / 2);

    float counterweight_scale = 1.3 * 500 * 2 * engine.crank_radius / counterweight_texture.getSize().y;
    counterweight.setScale(counterweight_scale, counterweight_scale);
    counterweight.setPosition(0, engine.cilinder_height*500 + 500*engine.crank_radius + piston_height*500 / 2);

}

void EngineVisualization::update() {
    float x = ((1 + sin(engine.angle)) * engine.crank_radius * 500);
    float piston_width = 2 * sqrt(engine.piston_area / M_PI);

    volume.setSize(sf::Vector2f(piston_width * 500, (engine.cilinder_height * 500 - x)));
    volume.setPosition(0, 0);

    piston.setPosition(0, engine.cilinder_height*500 - x);
    piston_seal.setPosition(0, engine.cilinder_height*500 - x + piston_height/5*500);
    piston_seal2.setPosition(0, engine.cilinder_height*500 - x + 2*piston_height/5*500);

    float rod_angle = atan2(engine.cilinder_height, engine.crank_radius * cos(engine.angle));

    rod.setRotation(rod_angle * 180 / M_PI + 90);
    rod.setPosition(cos(engine.angle) * 500 * engine.crank_radius, 2*engine.crank_radius*500 + engine.cilinder_height*500 + piston_height/2*500 - x);
    rod_end.setPosition(cos(engine.angle) * 500 * engine.crank_radius, 2*engine.crank_radius*500 + engine.cilinder_height*500 + piston_height/2*500 - x);

    counterweight.setRotation(- engine.angle * 180 / M_PI);

    int T = (engine.temperature - 273) / 2.0f;

    if (T > 255){
        T = 255;
    }else if (T < 0){
        T = 0;
    }

    volume.setFillColor(sf::Color(T, 150, 150));

}


void EngineVisualization::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(cilinder, states);
    target.draw(volume, states);
    target.draw(rod, states);
    target.draw(rod_end, states);
    target.draw(counterweight, states);
    target.draw(piston, states);
    target.draw(piston_seal, states);
    target.draw(piston_seal2, states);

}
