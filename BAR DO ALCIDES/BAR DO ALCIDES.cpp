#pragma once

#include "Game.h"

#define SFML_STATIC
#include <SFML/Graphics.hpp>



int main() {

	Game game(1600, 900, "Bar do Alcides");
	game.run();


}