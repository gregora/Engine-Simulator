#include <SFML/Graphics.hpp>
#include "TwoStroke.h"

class EngineVisualization: public sf::Transformable, public sf::Drawable {
public:
    EngineVisualization(TwoStroke& engine);

    void update();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    TwoStroke& engine;
    sf::RectangleShape piston;
};