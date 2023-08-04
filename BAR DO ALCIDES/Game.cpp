#pragma once

#include "Game.h"
#include "parOuImpar.h"
#include <string>


std::map<std::string, sf::Texture> ResourceManager::textures;
std::map<std::string, sf::SoundBuffer> ResourceManager::sounds;
std::map<std::string, sf::Font> ResourceManager::fonts;

sf::Texture& ResourceManager::getTexture(const std::string& filename) {
	if (textures.find(filename) == textures.end()) {
		// Texture not found, load it from file
		sf::Texture texture;
		if (texture.loadFromFile(filename)) {
			textures[filename] = texture;
		}
		else {
			// Handle error if texture loading fails
			// You can throw an exception, log an error, etc.
		}
	}

	return textures[filename];
}


sf::SoundBuffer& ResourceManager::getSound(const std::string& filename) {
	if (sounds.find(filename) == sounds.end()) {
		// Sound not found, load it from file
		sf::SoundBuffer sound;
		if (sound.loadFromFile(filename)) {
			sounds[filename] = sound;
		}
		else {
			// Handle error if sound loading fails
			// You can throw an exception, log an error, etc.
		}
	}

	return sounds[filename];
}


sf::Font& ResourceManager::getFont(const std::string& filename) {
	if (fonts.find(filename) == fonts.end()) {
		// Font not found, load it from file
		sf::Font font;
		if (font.loadFromFile(filename)) {
			fonts[filename] = font;
		}
		else {
			// Handle error if font loading fails
			// You can throw an exception, log an error, etc.
		}
	}

	return fonts[filename];
}

void ResourceManager::deleteTexture(const std::string& filename) {
	auto it = textures.find(filename);
	if (it != textures.end()) {
		textures.erase(it);
		// Optional: The texture will be automatically deleted when it goes out of scope
		// But, you can explicitly call 'delete' to free the memory immediately
		// delete &(it->second);
	}
}


void ResourceManager::deleteSound(const std::string& filename) {
	auto it = sounds.find(filename);
	if (it != sounds.end()) {
		sounds.erase(it);
		// Optional: The sound buffer will be automatically deleted when it goes out of scope
		// But, you can explicitly call 'delete' to free the memory immediately
		// delete &(it->second);
	}
}


void ResourceManager::deleteFont(const std::string& filename) {
	auto it = fonts.find(filename);
	if (it != fonts.end()) {
		fonts.erase(it);
		// Optional: The font will be automatically deleted when it goes out of scope
		// But, you can explicitly call 'delete' to free the memory immediately
		// delete &(it->second);
	}
}











Game::Game(int x, int y, const char * title) {
	this->window = new sf::RenderWindow(sf::VideoMode(x, y), title);
	this->window->setFramerateLimit(60);
	
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


	while (window->isOpen()) {


		sf::Event e;
		while (window->pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window->close();
			} else 	if (e.type == sf::Event::MouseMoved) {
				input.mousePos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
			}
			else if (e.type == sf::Event::MouseWheelScrolled) {
				input.mouseScroll = e.mouseWheelScroll.delta;
			}
			
		}

		input.update();


		window->clear(sf::Color::Black);

		jogo.update(input);
		jogo.draw(*window);

		std::string str = "X:";
		str += std::to_string(input.mousePos.x);
		str += "/ Y:";
		str += std::to_string(input.mousePos.y);
		coords.setString(str);
		window->draw(coords);

		window->display();

	}
}