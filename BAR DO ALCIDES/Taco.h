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

	float aproach = 0;




public:
	float hitPower = 0;

	bool fixedAng = false;
	float targetDist = 0;

	bool vanishing = false;
	bool aproaching = false;
	bool hitting = false;
	bool hitted = false;
	float hitAngle = 0;
	sf::Vector2f hitDir;

	Tacada() {
		tacoTex.loadFromFile("../Assets/tacoInicial.png");
		tacoSpr.setTexture(tacoTex);
		tacoSpr.setScale(0.5, 0.5);

		angle = 0;
		pos.x = 0;
		pos.y = 0;

	}

	void setTarget(sf::Vector2f tar, Input input) {
		target = tar;
		hitted = false;
		fixedAng = true;
		hitAngle = angle;
		hitDir.x = cos(angle);
		hitDir.y = sin(angle);
		idleTimer = 0;
		pos = target;
		targetDist = maximum(0, -vecDot(hitDir, target - sf::Vector2f(input.mousePos.x, input.mousePos.y)));
		hitPower = targetDist/300;
	}

	void update(sf::Vector2f bolaoPos, Input& input) {


		if (hitting) {
			idleTimer = 0;
			targetDist -= 10;
			if (targetDist <= 0) {
				hitted = true;
				hitting = false;
				vanishing = true;
				
			}
		}
		else if(fixedAng) {
			targetDist = maximum(0, - vecDot(hitDir, target - sf::Vector2f(input.mousePos.x, input.mousePos.y)));
			hitPower = targetDist/300;

			if (input.mouseState[0][1]) {
				hitting = true;
				fixedAng = false;
			}

			if (input.mouseState[1][1]) {
				fixedAng = false;
				targetDist = 0;
			}
		}
		else {



			float dx = input.mousePos.x - bolaoPos.x;
			float dy = input.mousePos.y - bolaoPos.y;

			float ang = atan2(dy, dx);
			if (ang < 0)
			{
				ang = deg2Rad(360) + ang;
			}


			if (vanishing) {
				aproach += 20;
				if (aproach > 4000) {
					vanishing = false;
				}
			}
			else {
				angle = ang;

				pos.x = input.mousePos.x;
				pos.y = input.mousePos.y;
			}


			if (!aproaching) {
				if (input.mouseState[0][1]) {
					vanishing = false;
					if (aproach <= 0) {
						setTarget(bolaoPos, input);
					}
					else {
						aproaching = true;
					}
				}
			}
			else {
				aproach -= 50;
				if (aproach < 0) {
					aproach = 0;
					aproaching = false;
				}
			}
		

			idleTimer += 0.05;

			

		}
	}

	void show(sf::RenderWindow& window) {

		
		tacoSpr.setOrigin(0, 20);
		tacoSpr.setRotation(rad2Deg(angle));

		// Varies from 0 to 100
		float phase = (sin(idleTimer) + 1) * 50;
		float dist = phase + targetDist + aproach;

		tacoSpr.setPosition(pos.x + cos(angle)*dist, pos.y + sin(angle) * dist);

		window.draw(tacoSpr);
	}
};
