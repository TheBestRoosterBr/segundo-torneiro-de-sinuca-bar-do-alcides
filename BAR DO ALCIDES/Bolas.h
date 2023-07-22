#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#define SFML_STATIC



typedef double inerciaRotacional;

std::unordered_map<int, sf::Color> ColorMap;

enum colors {
	white,
	Yellow,
	lightBlue,
	red,
	violet,
	orange,
	green,
	brown,
	black,
	darkYellow,
	darkBlue,
	vine,
	purple,
	darkOrange,
	seaGreen,
	marromCinzentoSeiLa
};


class Bola {

protected:
	
//fisica
//physics
	sf::Vector2f pos;
	int num;
	int radius;
	inerciaRotacional L;
	int mass;

// isso é pra decorar as bolas
// balls graphics and details
	sf::CircleShape shape;
	sf::CircleShape BlackOrWhite;
	sf::Text number;

#define START_POSITION_X 750
#define START_POSITION_Y 500

public:
	Bola() {
		
	}
	Bola(int num) {
		radius = 20;
		mass = 1;
		L = 2 / 5 * mass * (radius * radius);
		this->num = num;
		shape.setFillColor(ColorMap[num]);
		shape.setRadius(radius);
		pos.x = START_POSITION_X + ((int)(num) * radius);
		pos.y = START_POSITION_Y + radius + (int)(num / 2);
		shape.setPosition(pos);
		(num > 8) ? BlackOrWhite.setFillColor(sf::Color::White) : BlackOrWhite.setFillColor(sf::Color::Black);
		BlackOrWhite.setRadius(radius / 2);
		BlackOrWhite.setPosition(pos.x + radius/2, pos.y + radius/2);

	}
	void init() {

	}
	void update() {

	}
	void show(sf::RenderWindow& window) {
		window.draw(shape);
		window.draw(BlackOrWhite);
	}

};

class Bolao:Bola {

private:
#define BOLAO_START_POSITION_X 100
public:
	Bolao() {
		num = 0;
		radius = 25;
		mass = 2;
		L = 2 / 5 * mass * (radius * radius);
		shape.setFillColor(ColorMap[num]);
		shape.setRadius(radius);
		pos.x = BOLAO_START_POSITION_X;
		pos.y = START_POSITION_Y;
		shape.setPosition(pos);

	}
	void init() {

	}
	void update() {

	}
	void show(sf::RenderWindow& window) {
		window.draw(shape);
	}
};