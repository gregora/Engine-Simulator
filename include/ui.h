#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include <vector>

class Gauge : public sf::Drawable, public sf::Transformable {
public:
	Gauge(std::string name = "", float min = 0, float max = 1);
	~Gauge();

	std::string name = "";
	std::string unit = "";
	float min = 0;
	float max = 1;
	float value = 0.5;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

	sf::Sprite sprite;
	sf::Texture texture;

	sf::Font font;
};


class Button : public sf::Drawable, public sf::Transformable {

public:
	Button(char key);
	float active = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Font font;
	char key;

};

class Bar : public sf::Drawable, public sf::Transformable {

public:
	Bar(std::string name = "", float min = 0, float max = 1, bool horizontal = true);
	~Bar();

	std::string name = "";
	float min = 0;
	float max = 1;
	float value = 0.5;
	bool horizontal = true;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Font font;
};

class Chart : public sf::Drawable, public sf::Transformable {

public:
	Chart(std::string name = "", float min_x = 0, float max_x = 1, float min_y = 0, float max_y = 1, float view_width = 400, float view_height = 200);
	~Chart();

	std::string name = "";
	float min_x = 0;
	float max_x = 1;
	std::vector<float> values_x;
	std::vector<float> values_y;
	float min_y = 0;
	float max_y = 1;

	float view_height = 200;
	float view_width = 400;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Color line_color = sf::Color(200, 0, 0);

private:
	sf::RectangleShape background;	
	sf::Font font;
};

class FPS : public sf::Drawable, public sf::Transformable {

public:
	FPS();
	sf::Clock c;
	uint fps = 0;
	uint frame_average = 1;

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Font font;

	uint current_frame = 0;

};