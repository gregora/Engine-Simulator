#include "EngineVisualization.h"

EngineVisualization::EngineVisualization(TwoStroke& engine) : engine(engine) {
    // Initialize the visualization (e.g., create shapes)
    piston.setSize(sf::Vector2f(50, 20));
    piston.setFillColor(sf::Color(100, 100, 100));
}

void EngineVisualization::update() {
    float x = (1 + sin(engine.angle)) * engine.crank_radius * 500;
    piston.setPosition(0, (int) -x);

    volume.setSize(sf::Vector2f(50, (int)(engine.piston_length * 500 - x)));
    volume.setPosition(0, (int)(- engine.piston_length * 500));

    int T = engine.temperature - 273;

    if (T > 255){
        T = 255;
    }else if (T < 0){
        T = 0;
    }

    volume.setFillColor(sf::Color(T, 150, 150));
}


void EngineVisualization::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(piston, states);
    target.draw(volume, states);
}
