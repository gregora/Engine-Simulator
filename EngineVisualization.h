#include <SFML/Graphics.hpp>
#include "TwoStroke.h"

class EngineVisualization: public sf::Transformable, public sf::Drawable {
public:
    EngineVisualization(TwoStroke& engine);
    void init();

    void update();

    float piston_height = 0.04f;

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    TwoStroke& engine;
    sf::RectangleShape piston;
    sf::RectangleShape piston_seal;
    sf::RectangleShape piston_seal2;
    sf::RectangleShape volume;
    sf::RectangleShape rod;
    sf::Sprite counterweight;
    sf::Texture counterweight_texture;
    sf::RectangleShape cilinder;
};