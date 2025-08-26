#include "EngineVisualization.h"

EngineVisualization::EngineVisualization(TwoStroke& engine) : engine(engine) {
    // Initialize the visualization (e.g., create shapes)
    piston.setSize(sf::Vector2f(50, 20));
    piston.setFillColor(sf::Color(100, 100, 100));
}

void EngineVisualization::update() {
    float x = cos(engine.angle) * 100;
    piston.setPosition(0, (int) x);
}

void EngineVisualization::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(piston, states);
}
