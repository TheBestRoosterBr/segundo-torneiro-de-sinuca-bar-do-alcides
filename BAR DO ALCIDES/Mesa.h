#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "Bolas.h"
#include "Taco.h"
#include <fstream>

class Mesa
{
public:

	sf::Vector2f wallStart;
	bool building = false;

	sf::Sound ballEnter;

	Mesa() {
		texture.loadFromFile("../Assets/mesa.png");
		mesaSpr.setTexture(texture);
		mesaSpr.setScale(0.25,0.25);
		mesaSpr.setPosition(200, 100);

		for (int i = 0; i < 16; i++) {
			Bola b(i);
			balls.push_back(b);
		}

		/*
		Wall w(290, 220, 90, 500);
		walls.push_back(w);

		Wall w2(290, 220, 215, 500);
		walls.push_back(w2);
		*/

		loadWalls();


		Tacada taco();

		ballEnter.setBuffer(ResourceManager::getSound("../Assets/ballEnter.mp3"));
		ballEnter.setVolume(70);


	}




	void update(Input& input) {
		//Balls physics

		for (int i = 0; i < balls.size(); i++) {
			balls[i].update();
			balls[i].boundsConstrain(mesaSpr.getGlobalBounds().getPosition().x, mesaSpr.getGlobalBounds().getPosition().y, mesaSpr.getGlobalBounds().width, mesaSpr.getGlobalBounds().height);
		}


		for (int i = 0; i < balls.size(); i++) {
			for (int j = 0; j < cacapas.size(); j++) {
				Bola& a = balls[i];
				
				float dist = vecLength(a.pos - cacapas[j].getPosition());

				if (dist < cacapas[j].getRadius()) {

					ballEnter.play();
					if (a.num == 0) {
						a.resetPos();
						a.vel.x = 0;
						a.vel.y = 0;
					} else {
						a.out = true;
					}
				}
			}
		}

		for (int i = 0; i < balls.size(); i++) {
			if (balls[i].out) {
				balls.erase(balls.begin() + i);
				i--;
			}
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

						//ballCollision.play();

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

						
						float speed = vb - va;

						if (speed > 0.05) {
							float pitch = 0.7 + constrain(1.8 * speed / 20, 0, 1);



							a.ballCollision.setPitch(pitch);
							a.ballCollision.setVolume(80 + (speed - 11) * 5);


							a.ballCollision.play();
						}

						float pva = vecDot(a.vel, perp);
						float pvb = vecDot(b.vel, perp);

						a.vel = vecMult(direction, vb) + vecMult(perp, pva);
						b.vel = vecMult(direction, va) + vecMult(perp, pvb);
					}
				}

			}
		}

		taco.update(balls[0].getPos(), input);

		if (taco.hitted) {
			taco.hitted = false;
			balls[0].vel.x += cos(taco.hitAngle + PI)*(taco.hitPower*3+3);
			balls[0].vel.y += sin(taco.hitAngle + PI) * (taco.hitPower*3+3);
		}


		if (input.keyboardState[sf::Keyboard::LShift][0] && input.mouseState[1][1]) {
			if (!building) {
				building = true;
				wallStart = input.mousePos;
			}
			else {

				building = false;

				float dx = input.mousePos.x - wallStart.x;
				float dy = input.mousePos.y - wallStart.y;

				float ang = atan2(dy, dx);
				if (ang < 0)
				{
					ang = deg2Rad(360) + ang;
				}

				Wall wall(wallStart.x, wallStart.y, rad2Deg(ang), vecLength(sf::Vector2f(dx, dy)));
				walls.push_back(wall);

			}
		}

		if (input.keyboardState[sf::Keyboard::RShift][0] && input.mouseState[1][1]) {
			sf::CircleShape buraco;
			buraco.setRadius(30);
			buraco.setOrigin(30, 30);
			buraco.setPosition(input.mousePos);
			cacapas.push_back(buraco);
		}

		if (input.keyboardState[sf::Keyboard::LControl][0] && input.keyboardState[sf::Keyboard::S][1]) {
			saveWalls();
		}
		if (input.keyboardState[sf::Keyboard::LControl][0] && input.keyboardState[sf::Keyboard::L][1]) {
			loadWalls();
		}
		
		
	}

	void draw(sf::RenderWindow& window) {
		window.draw(mesaSpr);


		for (sf::CircleShape buraco : cacapas) {
			buraco.setFillColor(sf::Color::Black);
			buraco.setOutlineColor(sf::Color::White);
			buraco.setOutlineThickness(2);

			window.draw(buraco);
		}


		//bolao.show(window);
		for (Bola bola : balls) {
			bola.show(window);
		}

		for (Wall wall : walls) {
			wall.show(window);
		}

		if (building) {
			sf::RectangleShape rect(sf::Vector2f(8, 8));
			rect.setOrigin(4, 4);
			rect.setFillColor(sf::Color::Black);
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(2);
			rect.setPosition(wallStart);

			window.draw(rect);
		}


		taco.show(window);
	}

	void loadWalls() {
		
		std::ifstream file("walls.txt");

		if (file.is_open()) {
			walls.clear();

			std::string line;

			std::getline(file, line);
			int wallNum = std::stoi(line);

			for (int i = 0; i < wallNum; i++) {
				std::getline(file, line);
				float wx = std::stof(line);
				std::getline(file, line);
				float wy = std::stof(line);
				std::getline(file, line);
				float wang = std::stof(line);
				std::getline(file, line);
				float wlength = std::stof(line);

				Wall wall(wx, wy, wang, wlength);
				walls.push_back(wall);
			}
			std::getline(file, line);
			int cacapaNum = std::stoi(line);

			for (int i = 0; i < cacapaNum; i++) {
				std::getline(file, line);
				float cx = std::stof(line);
				std::getline(file, line);
				float cy = std::stof(line);
				std::getline(file, line);
				float crad = std::stof(line);

				sf::CircleShape cacapa(crad);
				cacapa.setPosition(cx, cy);
				cacapa.setOrigin(crad, crad);

				cacapas.push_back(cacapa);
			}

		}
		else {
			std::cout << "Falha ao carregar walls.txt" << std::endl;
		}
		file.close();
		

	}

	void saveWalls() {
		std::ofstream file("walls.txt");

		if (file.is_open()) {
			file << walls.size() << std::endl;

			for (int i = 0; i < walls.size(); i++) {
				file << walls[i].pos.x << std::endl;
				file << walls[i].pos.y << std::endl;
				file << walls[i].angle << std::endl;
				file << walls[i].length << std::endl;
			}

			file << cacapas.size() << std::endl;
			for (int i = 0; i < cacapas.size(); i++) {
				file << cacapas[i].getPosition().x << std::endl;
				file << cacapas[i].getPosition().y << std::endl;
				file << cacapas[i].getRadius() << std::endl;
			}

		}
		else {
			std::cout << "Falha ao salvar walls.txt" << std::endl;
		}

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

