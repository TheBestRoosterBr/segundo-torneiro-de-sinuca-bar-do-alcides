#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "Bolas.h"
#include "Taco.h"

class Mesa
{
public:
	Mesa() {
		texture.loadFromFile("../Assets/mesa.png");
		mesaSpr.setTexture(texture);
		mesaSpr.setScale(0.25,0.25);
		mesaSpr.setPosition(200, 100);

		for (int i = 0; i < 16; i++) {
			Bola b(i);
			balls.push_back(b);
		}


		Wall w(290, 220, 90, 500);
		walls.push_back(w);

		Wall w2(290, 220, 215, 500);
		walls.push_back(w2);


		Tacada taco();

	}




	void update(float mouseX, float mouseY, bool mouseClick) {
		//Balls physics

		for (int i = 0; i < balls.size(); i++) {
			balls[i].update();
			balls[i].boundsConstrain(mesaSpr.getGlobalBounds().getPosition().x, mesaSpr.getGlobalBounds().getPosition().y, mesaSpr.getGlobalBounds().width, mesaSpr.getGlobalBounds().height);
		}

		for (int i = 0; i < balls.size(); i++) {
			Bola& a = balls[i];

			for (int j = 0; j < walls.size(); j++) {
				Wall& w = walls[j];

				sf::Vector2f wpoint = w.closestPointToPoint(a.pos);

				sf::Vector2f dif = a.pos - wpoint;
				float dist = vecLength(dif);

				if (dist < a.radius) {

					sf::Vector2f direction = vecNormal(dif);
					sf::Vector2f perp = vecPerpendicular(direction);

					float overlap = (a.radius) - dist;

					sf::Vector2f move = vecMult(direction, overlap);

					a.pos += move;

					float va = vecDot(a.vel, direction);
					if (!(va > 0)) {
						float pva = vecDot(a.vel, perp);
						a.vel = vecMult(direction, -va) + vecMult(perp, pva);
					}
				}
			}


			for (int j = i+1; j < balls.size(); j++) {
				
				Bola& b = balls[j];

				sf::Vector2f dif = a.pos - b.pos;
				float dist = vecLength(dif);

				if (dist < a.radius + b.radius) {

					sf::Vector2f direction = vecNormal(dif);
					sf::Vector2f perp = vecPerpendicular(direction);

					float overlap = (a.radius + b.radius) - dist;

					sf::Vector2f move = vecMult(direction, overlap/2);

					a.pos += move;
					b.pos -= move;
					


					float va = vecDot(a.vel,direction);
					float vb = vecDot(b.vel,direction);


					if (!(va > 0 && vb < 0)) {
						float pva = vecDot(a.vel, perp);
						float pvb = vecDot(b.vel, perp);

						a.vel = vecMult(direction, vb) + vecMult(perp, pva);
						b.vel = vecMult(direction, va) + vecMult(perp, pvb);
					}
				}

			}
		}

		taco.update(balls[0].getPos(), mouseX, mouseY, mouseClick);

		if (taco.hitted) {
			taco.hitted = false;
			balls[0].vel.x += cos(taco.hitAngle + 3.1415)*(taco.hitPower*3+3);
			balls[0].vel.y += sin(taco.hitAngle + 3.1415) * (taco.hitPower*3+3);
		}
		
	}

	void draw(sf::RenderWindow& window) {
		window.draw(mesaSpr);
		bolao.show(window);
		for (Bola bola : balls) {
			bola.show(window);
		}

		for (Wall wall : walls) {
			wall.show(window);
		}

		taco.show(window);
	}

private:
#define ATRITO 0.05;
	Bolao bolao;
	std::vector<Bola> balls;
	std::vector<Wall> walls;
 	std::vector<sf::CircleShape> cacapas;
	std::vector<sf::RectangleShape> paredes;
	std::vector<sf::ConvexShape> quinas;

	sf::Texture texture;
	sf::Sprite mesaSpr;

	Tacada taco;

};

