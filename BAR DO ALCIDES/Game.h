#pragma once



#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




class ResourceManager {
public:

	static sf::Texture& getTexture(const std::string& filename);
	static sf::SoundBuffer& getSound(const std::string& filename);
	static sf::Font& getFont(const std::string& filename);

	static void deleteTexture(const std::string& filename);
	static void deleteSound(const std::string& filename);
	static void deleteFont(const std::string& filename);



private:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::SoundBuffer> sounds;
	static std::map<std::string, sf::Font> fonts;


};






class Input {
public:
	bool keyboardState[sf::Keyboard::KeyCount][3];
	bool mouseState[sf::Mouse::ButtonCount][3];
	float mouseScroll = 0;

	sf::Vector2f mousePos;

	Input() {
		mousePos.x = 0;
		mousePos.y = 0;

		mouseScroll = 0;

		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			keyboardState[i][0] = false;
			keyboardState[i][1] = false;
			keyboardState[i][2] = false;
		}

		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
			mouseState[i][0] = false;
			mouseState[i][1] = false;
			mouseState[i][2] = false;
		}
	}

	void update() {
		mouseScroll = 0;

		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			bool keyState = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);

			if (!keyboardState[i][0] && keyState) {
				keyboardState[i][1] = true;
			}
			else {
				keyboardState[i][1] = false;
			}

			if (keyboardState[i][0] && !keyState) {
				keyboardState[i][2] = true;
			}
			else {
				keyboardState[i][2] = false;
			}

			keyboardState[i][0] = keyState;

		}

		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {

			bool buttonState = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);

			if (!mouseState[i][0] && buttonState) {
				mouseState[i][1] = true;
			}
			else {
				mouseState[i][1] = false;
			}

			if (mouseState[i][0] && !buttonState) {
				mouseState[i][2] = true;
			}
			else {
				mouseState[i][2] = false;
			}

			mouseState[i][0] = buttonState;

		}
	}


};


class Game
{
	Input input;
	sf::RenderWindow * window = NULL;

public:

	Game(int x, int y, const char * title);
	~Game();

	void run();





};