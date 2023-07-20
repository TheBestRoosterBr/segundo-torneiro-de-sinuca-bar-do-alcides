#pragma once
#include <SFML/Graphics.hpp>
#include "Bolas.h"

class Mesa
{
public:
	void init() {
		texture.loadFromFile("Assets/mesa.png");
		mesaSpr.setTexture(texture);
	}
	void update() {

	}

private:
#define ATRITO 0.05;
	Bolao bolao;
	std::vector<Bola> balls;
	std::vector<sf::CircleShape> cacapas;
	std::vector<sf::RectangleShape> paredes;
	std::vector<sf::ConvexShape> quinas;

	sf::Texture texture;
	sf::Sprite mesaSpr;

};

