

#include "Game.h"
#include "parOuImpar.h"
#include <string>

Game::Game(int x, int y, const char * title) {
	this->window = new sf::RenderWindow(sf::VideoMode(x, y), title);
	
}

Game::~Game() {
	delete window;
}

void Game::run() {
	ImparOuPar jogo;


	sf::Font basicFont;
	basicFont.loadFromFile("../Assets/fonts/Daydream.ttf");
	sf::Text coords;
	coords.setFont(basicFont);
	coords.setCharacterSize(10);
	coords.setFillColor(sf::Color::Black);
	coords.setOutlineColor(sf::Color::White);
	coords.setOutlineThickness(2);
	
	int mouseX = 0;
	int mouseY = 0;
	bool mouseState[3] = { false, false, false };


	while (window->isOpen()) {

		mouseState[1] = false;
		mouseState[2] = false;

		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window->close();
			} else 	if (e.type == sf::Event::MouseMoved) {
				mouseX = e.mouseMove.x;
				mouseY = e.mouseMove.y;
			}
			else if (e.type == sf::Event::MouseButtonPressed) {
				if (!mouseState[0]) {
					mouseState[1] = true;
				}
				mouseState[0] = true;
			}
			else if (e.type == sf::Event::MouseButtonReleased) {
				if (mouseState[0]) {
					mouseState[2] = true;
				}
				mouseState[0] = false;
			}
		}

		window->clear(sf::Color::Black);

		jogo.update(mouseX, mouseY, mouseState[1]);
		jogo.draw(*window);

		std::string str = "X:";
		str += std::to_string(mouseX);
		str += "/ Y:";
		str += std::to_string(mouseY);
		coords.setString(str);
		window->draw(coords);

		window->display();

	}
}