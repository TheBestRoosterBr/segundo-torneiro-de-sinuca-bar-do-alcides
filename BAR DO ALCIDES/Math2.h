#pragma once

#ifndef MATH2
#define MATH2

#include <math.h>
#include <cstdlib>
#include <string>

#define Gravity 9.81
const long double PI  = 3.141592653589793;
#define EULER 2.71828





// Retorna o sinal de um numero
int sign(float val) {
	if (val > 0) {
		return 1;
	}
	else if (val < 0) {
		return -1;
	}
	return 0;
}


// Maximo Minimo e Constrain que e os dois juntos
// Returns the bigger value
float maximum(float val, float val2) {
	if (val > val2) {
		return val;
	}
	return val2;
}

// Returns the smaller value
float minimum(float val, float val2) {
	if (val < val2) {
		return val;
	}
	return val2;
}


float constrain(float val, float min, float max) {
	return maximum(minimum(val, max), min);
}


float ruleOfThree(float val, float valMin, float valMax, float outMin, float outMax) {
	float perc = (val - valMin) / (valMax - valMin);
	return outMin + (outMax - outMin) * perc;
}
float ruleOfThree(float val, float valMax, float val2Max) {
	return (val / valMax) * val2Max;
}


// Randomness

// Random Integer up to a max
int randInt(int max) {
	return std::rand() % max;
}

// Random Integer between a min and a max
int randIntRange(int min, int max) {
	if (min > max) {
		return max + randInt(min - max);
	}
	return min + randInt(max-min);
}

// Random Float up to a max
float randFloat(float max) {	
	return max * std::rand() / (RAND_MAX + 1.);
}

// Random Float between a min and a max
float randFloatRange(float min, float max) {
	return min + randFloat(max - min);
}






float pitagoras(float cateto1, float cateto2) {
	return sqrt(pow(cateto1, 2) + pow(cateto2, 2));
}



/// Converts degrees to radians
float deg2Rad(float angle) {
	return (angle * PI) / 180;
}

/// Converts radians to degrees
float rad2Deg(float angle) {
	return (angle * 180) / PI;
}



// Text Utils

std::string fixedDigits(int number, int digits){
	std::string str = std::to_string(number);

	while (str.size() < digits) {
		str.insert(str.begin(), '0');
	}

	while (str.size() > digits) {
		str.erase(str.begin());
	}
	
	return str;

}





/*
void printIntVec(std::vector<int> vec) {
	std::cout << "[ ";
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
		if (i == vec.size() - 1) {
			std::cout << " ]";

		}
		else {
			std::cout << ", ";
		}
	}
}

std::string streamIntVec(std::vector<int> vec) {
	std::stringstream a;
	a << "[ ";
	for (int i = 0; i < vec.size(); i++) {
		a << vec[i];
		if (i == vec.size() - 1) {


		}
		else {
			a << ", ";
		}
	}
	a << " ]";

	return a.str();
}
*/




#endif // !MATH2