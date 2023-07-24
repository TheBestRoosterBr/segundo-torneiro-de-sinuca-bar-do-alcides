#pragma once


#include <SFML/Graphics.hpp>
#define SFML_STATIC
#include "Mesa.h"
#include "Taco.h"
#include "Bolas.h"

class ImparOuPar {

	Mesa* mesa;
	//Taco player1;
	//Taco player2;

public:
	ImparOuPar() {
		ColorMap[white] = sf::Color::White;
		ColorMap[Yellow] = sf::Color::Yellow;
		ColorMap[red] = sf::Color::Red;
		ColorMap[lightBlue] = sf::Color::Blue;
		ColorMap[darkBlue] = sf::Color(0, 0, 155);
		ColorMap[darkOrange] = sf::Color(255, 155, 0);
		ColorMap[black] = sf::Color::Black;
		ColorMap[violet] = sf::Color(127, 0, 255);
		ColorMap[purple] = sf::Color(128,0,128);
		ColorMap[green] = sf::Color::Green;
		ColorMap[seaGreen] = sf::Color(46, 139, 87);
		ColorMap[brown] = sf::Color(139, 69, 19);
		ColorMap[vine] = sf::Color(138, 28, 145);
		ColorMap[marromCinzentoSeiLa] = sf::Color(210, 180, 140);

		mesa = new Mesa();



	}
	void update(float mouseX, float mouseY, bool mouseClick) {
		mesa->update(mouseX, mouseY, mouseClick);
	}
	void draw(sf::RenderWindow& window) {
		mesa->draw(window);
	}
};