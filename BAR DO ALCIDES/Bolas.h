#pragma once

#include <SFML/Graphics.hpp>
#define SFML_STATIC
typedef double inerciaRotacional;

class Bola {

protected:
	sf::Vector2i pos;
	int num;
	int radius;
	inerciaRotacional L;
	int mass;
	sf::CircleShape shape;




public:
	void init() {

	}
	void update() {

	}

};

class Bolao:Bola {

private:
	
public:
	void init() {

	}
	void update() {

	}
};