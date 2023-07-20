#pragma once
#include <SFML/Graphics.hpp>
#include "Mesa.h"
#include "Bolas.h"

struct Taco {
	int force;
	int spin;
	int aim;
};

class Tacada {
	Taco taco;
	int angle;
	int force;

public:
	void tacar(Bolao& bolao, Mesa& m) {

	}
};
