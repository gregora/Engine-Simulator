#include "EngineVisualization.h"

EngineVisualization::EngineVisualization(TwoStroke& engine) : engine(engine) {
    // Initialize the visualization (e.g., create shapes)
    piston.setSize(sf::Vector2f(50, 30));
    piston.setOrigin(25, 0);
    piston.setFillColor(sf::Color(100, 100, 100));

    volume.setOrigin(25, 0);

    crank.setFillColor(sf::Color(70, 70, 70));
    crank.setSize(sf::Vector2f(10, engine.piston_length * 500 + engine.crank_radius * 500));
    crank.setOrigin(5, engine.piston_length * 250 + engine.crank_radius * 250);
    crank.setPosition(0, 15);

    crank_circle.setRadius(engine.crank_radius * 500);
    crank_circle.setOrigin(engine.crank_radius * 500, engine.crank_radius * 500);
    crank_circle.setFillColor(sf::Color(50, 50, 50));
    crank_circle.setPosition(0, 50 + engine.crank_radius * 500);

    cilinder.setSize(sf::Vector2f(50, engine.piston_length * 500 + engine.crank_radius * 1000));
    cilinder.setOrigin(25, 0);
    cilinder.setFillColor(sf::Color(5, 5, 5));
    cilinder.setPosition(0, - engine.piston_length * 500);
    cilinder.setOutlineThickness(15);
    cilinder.setOutlineColor(sf::Color(25, 25, 25));
}

void EngineVisualization::update() {
    float x = ((1 + sin(engine.angle)) * engine.crank_radius * 500);
    piston.setPosition(0, -x);

    volume.setSize(sf::Vector2f(50, (engine.piston_length * 500 - x)));
    volume.setPosition(0, (int)(- engine.piston_length * 500));

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
    target.draw(crank_circle, states);

}
