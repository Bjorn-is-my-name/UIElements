#pragma once

#include <SFML/Graphics.hpp>
#include <UIElements.hpp>

using namespace uie;

class App
{
private:
	sf::RenderWindow window;
	sf::Font font;

	RoundedRectangle r;
	RoundedRectangle r2;
	Text t;
	Button b;
	Checkbox cb;
	Container<Text> c;
	LineLayout<> l;

	void run();
	void handleEvents();
	void update();
	void draw();
	void quit();

public:
	App() = default;
	void start();
};
