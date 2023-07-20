#pragma once
#include <SFML/Graphics.hpp>
#include "Bolas.h"

class Mesa
{
public:
	void init() {

	}

private:
	std::vector<Bola> balls;
	std::vector<sf::CircleShape> cacapas;
#define ATRITO 0.05;
	
	std::vector<sf::RectangleShape> paredes;
	std::vector<sf::ConvexShape> quinas;
	


};

