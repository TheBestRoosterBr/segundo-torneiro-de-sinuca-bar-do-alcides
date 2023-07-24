#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#define SFML_STATIC

#include <iostream>

#include "Vec.h"

typedef double inerciaRotacional;

std::unordered_map<int, sf::Color> ColorMap;

enum colors {
	white,
	Yellow,
	lightBlue,
	red,
	violet,
	orange,
	green,
	brown,
	black,
	darkYellow,
	darkBlue,
	vine,
	purple,
	darkOrange,
	seaGreen,
	marromCinzentoSeiLa
};


class Bola {

protected:
	

	inerciaRotacional L;
	int mass;

// isso é pra decorar as bolas
// balls graphics and details
	sf::CircleShape shape;
	sf::CircleShape BlackOrWhite;
	sf::Text number;

#define START_POSITION_X 1100
#define START_POSITION_Y 360


public:

//fisica
//physics
	sf::Vector2f pos;
	sf::Vector2f vel;
	float friction = 0.005;
	int num;
	int radius;


	Bola() {
		Bola(0);
	}
	Bola(int num) {
		vel.x = 0;
		vel.y = 0;
		radius = 20;
		mass = 1;
		L = 2 / 5 * mass * (radius * radius);
		this->num = num;

		shape.setRadius(radius);
		shape.setOrigin(sf::Vector2f(radius, radius));
	
		BlackOrWhite.setRadius(radius / 2);
		BlackOrWhite.setOrigin(sf::Vector2f(radius / 2, radius / 2));

		if (num == 0) {
			shape.setFillColor(sf::Color::White);
			BlackOrWhite.setFillColor(sf::Color::White);

			pos.x = START_POSITION_X - 500;
			pos.y = START_POSITION_Y;

		} else {
			shape.setFillColor(ColorMap[num]);
			

			int ballInd = num - 1;

			int layer = numToLayer(ballInd);
			float layerHei = radius * sqrt(3.5);

			pos.x = START_POSITION_X + layer * layerHei;
			pos.y = START_POSITION_Y - ((float)((radius * 2) * (layer + 1)) / 2) + (ballInd - layerMinNum(layer)) * radius * 2;
			(num > 8) ? BlackOrWhite.setFillColor(sf::Color::White) : BlackOrWhite.setFillColor(sf::Color::Black);
		}

		shape.setPosition(pos);
		BlackOrWhite.setPosition(pos);

	}
	void init() {

	}
	void update() {
		pos.x += vel.x;
		pos.y += vel.y;

		vel -= vecMult(vecNormal(vel), friction);
	}

	void boundsConstrain(int x, int y, int wid, int hei) {
		if (pos.x > x + wid - radius) {
			pos.x = x + wid - radius;
			vel.x *= -1;
		} else if (pos.x < x + radius) {
			pos.x = x + radius;
			vel.x *= -1;
		}

		if (pos.y > y + hei - radius) {
			pos.y = y + hei - radius;
			vel.y *= -1;
		}
		else if (pos.y < y + radius) {
			pos.y = y + radius;
			vel.y *= -1;
		}
	}

	void show(sf::RenderWindow& window) {
		shape.setPosition(pos);
		BlackOrWhite.setPosition(pos);
		window.draw(shape);
		window.draw(BlackOrWhite);
	}


	void setVel(float x, float  y) {
		vel.x = x;
		vel.y = y;
	}

	void setPos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	sf::Vector2f getPos() {
		return pos;
	}

	int numToLayer(int n) {
		if (n <= 0) {
			return 0;
		}
		else if (n > 0 && n < 3 ) {
			return 1;
		}
		else if (n > 2 && n < 6) {
			return 2;
		}
		else if (n > 5 && n < 10) {
			return 3;
		}

		// To handle the case when n is greater than 9
		return 4;
		
	}

	int layerMinNum(int layer) {
		return (layer * (layer + 1)) / 2;
	}


};

class Bolao:Bola {

private:
#define BOLAO_START_POSITION_X 100
public:
	Bolao() {
		num = 0;
		radius = 25;
		mass = 2;
		L = 2 / 5 * mass * (radius * radius);
		shape.setFillColor(ColorMap[num]);
		shape.setRadius(radius);
		pos.x = BOLAO_START_POSITION_X;
		pos.y = START_POSITION_Y;
		shape.setPosition(pos);
		shape.setOrigin(radius, radius);

	}
	void init() {

	}
	void update() {

	}
	void show(sf::RenderWindow& window) {
		window.draw(shape);
	}

	sf::Vector2f getPos() {
		return pos;
	}
};


class Wall {

public:
	sf::Vector2f pos;
	sf::Vector2f dir;
	float angle;
	float length;

	Wall(float x, float y, float ang, float len) {
		pos.x = x;
		pos.y = y;
		dir.x = cos(ang*3.1415/180);
		dir.y = sin(ang * 3.1415 / 180);
		angle = ang;
		length = len;
	}

	void show(sf::RenderWindow& window) {
		sf::RectangleShape rect(sf::Vector2f(length, 4));
		rect.setOrigin(0, 2);
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(2);
		rect.rotate(angle);
		rect.setPosition(pos);

		window.draw(rect);
	}

	sf::Vector2f closestPointToPoint(sf::Vector2f point) {
		sf::Vector2f dif = point - pos;
		float dist = vecDot(dif, dir);
		if (dist < 0) {
			return pos;
		}
		else if(dist > length){
			return pos + (dir * length);
		}

		return pos + (dir * dist);
	}
};