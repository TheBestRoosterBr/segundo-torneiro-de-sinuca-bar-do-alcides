#pragma once


#define SFML_STATIC
#include <SFML/Graphics.hpp>

class Game
{

	sf::RenderWindow * window = NULL;

public:

	Game(int x, int y, const char * title);
	~Game();

	void run();





};