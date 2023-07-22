#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "Bolas.h"

class Mesa
{
public:
	Mesa() {
		texture.loadFromFile("../Assets/mesa.png");
		mesaSpr.setTexture(texture);
		mesaSpr.setScale(0.25,0.25);
		for (int i = 1; i < 15; i++) {
			Bola b(i);
			balls.push_back(b);
		}
	}
	void update() {

	}
	void draw(sf::RenderWindow& window) {
		window.draw(mesaSpr);
		bolao.show(window);
		for(Bola bola : balls) {
			bola.show(window);
		}
		
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

