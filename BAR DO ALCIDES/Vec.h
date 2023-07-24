#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>

float vecLength(sf::Vector2f vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float vecDot(sf::Vector2f vec1, sf::Vector2f vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float vecCross(sf::Vector2f vec1, sf::Vector2f vec2) {
	return vec1.x * vec2.y + vec1.y * vec2.x;
}

sf::Vector2f vecNormal(sf::Vector2f vec) {
	float length = vecLength(vec);
	if (length == 0) {
		return sf::Vector2f(0, 0);
	}
	return sf::Vector2f(vec.x / length, vec.y / length);
}

sf::Vector2f vecPerpendicular(sf::Vector2f vec) {
	return sf::Vector2f(-vec.y, vec.x);
}

sf::Vector2f vecMult(sf::Vector2f vec, float val) {
	return sf::Vector2f(vec.x * val, vec.y * val);
}
