#include "Game.h"

Game::Game(int x, int y, const char * title) {
	this->window = new sf::RenderWindow(sf::VideoMode(x, y), title);
	
}

Game::~Game() {
	delete window;
}

void Game::run() {
	while (window->isOpen()) {

		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear(sf::Color::Black);
		window->display();

	}
}