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

	// Temp
	std::vector<unsigned short> lidar_bram;
	int zoomAngle = 0;

	enum class States
	{
		Idle,
		Normal,
		Zoomed
	} state = States::Idle;

	void schoolProjectCode();
	void initializeFakeLidarData();
	void handleUserInput();
	sf::Color getColorByDistance(int distance);
	unsigned short getLidarData(int angle);
	void setLidarData(int angle, unsigned short distance);
	void clearScreen(sf::Color color);
	void drawPixel(int x, int y, sf::Color color);
	void drawLine(int x1, int y1, int x2, int y2, sf::Color color);
	void drawCircle(int x, int y, int r, sf::Color color);
	void drawCircleBorder(int x, int y, int r, sf::Color color);
	void drawCircleSliceBorder(int x, int y, int r, float startAngle, float endAngle, sf::Color color);
	// Temp

	void run();
	void handleEvents();
	void update();
	void draw();
	void quit();

public:
	App() = default;
	void start();
};
