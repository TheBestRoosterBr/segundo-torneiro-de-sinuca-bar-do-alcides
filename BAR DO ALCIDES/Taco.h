#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "Mesa.h"
#include "Bolas.h"


class Tacada {
	float angle;

	sf::Vector2f pos;
	sf::Vector2f target;

	sf::Texture tacoTex;
	sf::Sprite tacoSpr;

	float idleTimer = 0;

	float aproach = -100;




public:
	bool hitPower = 0;
	bool hitting = false;
	bool hitted = false;
	float hitAngle = 0;

	Tacada() {
		tacoTex.loadFromFile("../Assets/tacoInicial.png");
		tacoSpr.setTexture(tacoTex);
		tacoSpr.setScale(0.5, 0.5);

		angle = 0;
		pos.x = 0;
		pos.y = 0;

	}

	void setTarget(sf::Vector2f tar) {
		target = tar;
		hitting = true;
		hitted = false;
		hitAngle = angle;
		hitPower = (1 + sin(idleTimer)) * 20;
	}

	void update(sf::Vector2f bolaoPos, float mouseX, float mouseY, bool mouseClick) {


		if (hitting) {
			idleTimer = 0;
			aproach += 10;
			if (aproach >= 0) {
				hitted = true;
				hitting = false;
				aproach = -100;
			}
		}
		else {


			float dx = mouseX - bolaoPos.x;
			float dy = mouseY - bolaoPos.y;


			float Deg2Rad = 3.1415 / 180;
			float ang = atan2(dy, dx);
			if (ang < 0)
			{
				ang = Deg2Rad * 360 + ang;
			}





			angle = ang;

			pos.x = mouseX;
			pos.y = mouseY;

			idleTimer += 0.05;

			if (mouseClick) {
				setTarget(bolaoPos);
			}

		}
	}

	void show(sf::RenderWindow& window) {

		float Rad2Deg =  180/ 3.1415;
		tacoSpr.setOrigin(0, 20);
		tacoSpr.setRotation(angle * Rad2Deg);


		tacoSpr.setPosition(pos.x + cos(angle)*( -aproach  + (sin(idleTimer) + 1)*50), pos.y + sin(angle) * (-aproach + (sin(idleTimer)+1) * 50));

		window.draw(tacoSpr);
	}
};
