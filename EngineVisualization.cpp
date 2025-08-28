#include "EngineVisualization.h"

EngineVisualization::EngineVisualization(TwoStroke& engine) : engine(engine) {
    // Initialize the visualization (e.g., create shapes)
    piston.setSize(sf::Vector2f(50, 30));
    piston.setOrigin(25, 0);
    piston.setFillColor(sf::Color(100, 100, 100));

    volume.setOrigin(25, 0);

    crank.setFillColor(sf::Color(70, 70, 70));
    crank.setSize(sf::Vector2f(10, engine.cilinder_height * 500 + engine.crank_radius * 500));
    crank.setOrigin(5, engine.cilinder_height * 250 + engine.crank_radius * 250);

    counterweight_texture.loadFromFile("textures/counterweight.png");

    counterweight.setTexture(counterweight_texture);
    counterweight.setOrigin(counterweight_texture.getSize().x / 2, counterweight_texture.getSize().y / 2);

    float counterweight_scale = 500 * 2 * engine.crank_radius / counterweight_texture.getSize().y;
    counterweight.setScale(counterweight_scale, counterweight_scale);
    counterweight.setPosition(0, engine.cilinder_height * 500 + engine.crank_radius * 500 - 7);

    cilinder.setSize(sf::Vector2f(50, engine.cilinder_height * 500 + engine.crank_radius * 1000));
    cilinder.setOrigin(25, 0);
    cilinder.setFillColor(sf::Color(5, 5, 5));
    cilinder.setPosition(0, - engine.cilinder_height * 500);
    cilinder.setOutlineThickness(15);
    cilinder.setOutlineColor(sf::Color(25, 25, 25));
}

void EngineVisualization::update() {
    float x = ((1 + sin(engine.angle)) * engine.crank_radius * 500);
    piston.setPosition(0, -x);

    volume.setSize(sf::Vector2f(50, (engine.cilinder_height * 500 - x)));
    volume.setPosition(0, (int)(- engine.cilinder_height * 500));

    float crank_angle = atan2(engine.cilinder_height, engine.crank_radius * cos(engine.angle) * 0.7);

    crank.setRotation(crank_angle * 180 / M_PI + 90);
    crank.setPosition(cos(crank_angle) * engine.crank_radius * 500, engine.cilinder_height * 500 - x - engine.crank_radius);

    counterweight.setRotation(- engine.angle * 180 / M_PI);

    int T = (engine.temperature - 273) / 2;

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
    target.draw(crank, states);
    target.draw(piston, states);
    target.draw(volume, states);
    target.draw(counterweight, states);

}
