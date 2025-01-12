#include <App.hpp>
#include <UIElements.hpp>

// Temp
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_VISSIBLE_DISTANCE 4750 // 4.8 Meter, minus 5 cm to prevent drawing over radar border (only drawn once)
#define M_PI 3.14159265358979323846
#define BLACK sf::Color::Black
#define WHITE sf::Color::White
#define RED sf::Color::Red
#define YELLOW sf::Color::Yellow
#define GREEN sf::Color::Green
#define CYAN sf::Color::Cyan
#define BLUE sf::Color::Blue
#define GREY_OUTLINE sf::Color(128, 128, 128, 128)

void App::schoolProjectCode()
{
	initializeFakeLidarData();

	while (window.isOpen())
	{
		handleUserInput();

		clearScreen(BLACK); // Might slow Nexys board down to much, have to check

		// Draw lidar data to the screen
		if (state == States::Normal)
		{
			// Origin at the center of the screen (can be set in state handling to increase Nexys performance)
			int centerX = SCREEN_WIDTH / 2;
			int centerY = SCREEN_HEIGHT / 2;

			drawCircleBorder(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 239, GREY_OUTLINE);

			for (uint16_t i = 0; i < 360; i++)
			{
				float distance = getLidarData(i);
				sf::Color color = getColorByDistance(distance);

				if (distance == 0 || distance > MAX_VISSIBLE_DISTANCE) // Skip to next angle if distance is out of range
					continue;

				distance /= 20.0; // Devide by 20mm, 1 pixel is 2cm in distance

				float radians = (i - 90) * (M_PI / 180);
				int x = centerX + distance * cos(radians);
				int y = centerY + distance * sin(radians);

				drawPixel(x, y, color);
			}

			// Draw a center pixel
			drawPixel(centerX, centerY, WHITE);

		}
		else if (state == States::Zoomed)
		{
			auto isAngleInSlice = [](float angle, float centerAngle) {
				float diff = fmod(angle - centerAngle + 540, 360) - 180;
				return abs(diff) < 22.5;
			};

			// Calculate slice boundaries
			float startAngle = zoomAngle - 22.5f;
			float endAngle = zoomAngle + 22.5f;

			// Origin at the bottom center of the screen (can be set in state handling to increase Nexys performance)
			int centerX = SCREEN_WIDTH / 2;
			int centerY = SCREEN_HEIGHT;

			// Draw guidance circle to show what part of the circle the user is looking at
			drawCircleBorder(50, 50, 50, GREY_OUTLINE);
			drawCircleSliceBorder(50, 50, 49, startAngle, endAngle, RED);

			// Draw outlines
			drawCircleSliceBorder(centerX, centerY, SCREEN_HEIGHT, -22.5, 22.5, GREY_OUTLINE);

			for (uint16_t i = 0; i < 360; i++) {
				float distance = getLidarData(i);
				sf::Color color = getColorByDistance(distance);

				if (distance == 0 || distance > MAX_VISSIBLE_DISTANCE || !isAngleInSlice(i, zoomAngle))
					continue;

				// Normalize angle to 0-45 degree range within the slice
				float normalizedAngle = fmod(i - zoomAngle + 360 + 22.5, 360) - 22.5;

				// Scale distance to fill screen height
				float scaledDistance = (distance / MAX_VISSIBLE_DISTANCE) * SCREEN_HEIGHT;

				// Calculate position in the zoomed view
				float normalizedRadians = normalizedAngle * (M_PI / 180);
				int x = centerX + scaledDistance * sin(normalizedRadians);
				int y = centerY - scaledDistance * cos(normalizedRadians);

				// Draw the point
				drawPixel(x, y, color);
			}
		}

		window.display();
	}

	quit();
}

void App::initializeFakeLidarData()
{
	// Fill lidar bram with fake data
	// Set default values to out of range
	lidar_bram = std::vector<unsigned short>(360, 0);

	// Immitate a object blocking the view
	lidar_bram[36] = 4760;
	lidar_bram[37] = 4640;
	lidar_bram[38] = 4540;
	lidar_bram[39] = 4420;
	lidar_bram[40] = 4330;
	lidar_bram[41] = 4240;
	lidar_bram[42] = 4170;
	lidar_bram[43] = 4090;
	lidar_bram[44] = 4020;
	lidar_bram[45] = 3940;
	lidar_bram[46] = 3940;
	lidar_bram[47] = 3940;
	lidar_bram[48] = 3940;
	lidar_bram[49] = 3940;
	lidar_bram[50] = 3940;
	lidar_bram[51] = 3940;
	lidar_bram[52] = 3940;
	lidar_bram[53] = 3940;
	lidar_bram[54] = 3940;
	lidar_bram[55] = 3940;
	lidar_bram[56] = 3940;
	lidar_bram[57] = 3940;
	lidar_bram[58] = 4060;
	lidar_bram[59] = 4180;
	lidar_bram[60] = 4300;
	lidar_bram[61] = 4420;
	lidar_bram[62] = 4560;
	lidar_bram[63] = 4720;
	lidar_bram[64] = 4920;

	for (int i = 0; i < 34; i++)
		lidar_bram[93 + i] = 2200;

	lidar_bram[214] = 3080;
	lidar_bram[215] = 3000;
	lidar_bram[216] = 2950;
	lidar_bram[217] = 2880;
	lidar_bram[218] = 2800;
	lidar_bram[219] = 2750;
	lidar_bram[220] = 2700;
	lidar_bram[221] = 2640;
	lidar_bram[222] = 2590;
	lidar_bram[223] = 2540;
	lidar_bram[224] = 2490;
	lidar_bram[225] = 2450;
	lidar_bram[226] = 2490;
	lidar_bram[227] = 2540;
	lidar_bram[228] = 2590;
	lidar_bram[229] = 2640;
	lidar_bram[230] = 2700;
	lidar_bram[231] = 2750;
	lidar_bram[232] = 2800;
	lidar_bram[233] = 2880;
	lidar_bram[234] = 2950;
	lidar_bram[235] = 3000;
	lidar_bram[236] = 3080;

	for (int i = 0; i < 38; i++)
		lidar_bram[280 + i] = 950 + i * i;
}

void App::handleUserInput()
{
	// State managing based on key press (immitates switch functionality on Nexys board)
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			quit();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				quit();
				break;
			case sf::Keyboard::Space:
				switch (state)
				{
				case States::Idle:
					state = States::Normal;
					break;
				case States::Normal:
					state = States::Zoomed;
					break;
				case States::Zoomed:
					state = States::Idle;
					break;
				default:
					break;
				}
				break;
			case sf::Keyboard::Left:
				if (zoomAngle == 0)
					zoomAngle = 359;
				else
					zoomAngle--;
				break;
			case sf::Keyboard::Right:
				if (zoomAngle == 359)
					zoomAngle = 0;
				else
					zoomAngle++;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

sf::Color App::getColorByDistance(int distance)
{
	if (distance < 1000) return RED;
	if (distance < 2000) return YELLOW;
	if (distance < 3000) return GREEN;
	if (distance < 4000) return CYAN;
	return BLUE;
}

unsigned short App::getLidarData(int angle)
{
	return lidar_bram[angle];
}

void App::setLidarData(int angle, unsigned short distance)
{
	lidar_bram[angle] = distance;
}

void App::clearScreen(sf::Color color)
{
	window.clear(color);
}

void App::drawPixel(int x, int y, sf::Color color)
{
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return;

	sf::RectangleShape pixel;
	pixel.setPosition(x, y);
	pixel.setSize({ 1, 1 });
	pixel.setFillColor(color);

	window.draw(pixel);
}

void App::drawLine(int x1, int y1, int x2, int y2, sf::Color color)
{
	/*
	x, y are the pixel position
	dy, dy, dxAbs, dyAbs are the delta variables
	px, py accumulate the error, thus deciding the direction of the line
	xe, ye keep track of where the line ends, taking into account the direction
	*/
	uint16_t x = 0;
	uint16_t y = 0;
	int16_t dx = x2 - x1;
	int16_t dy = y2 - y1;
	uint16_t dxAbs = abs(dx);
	uint16_t dyAbs = abs(dy);
	int16_t px = 2 * dyAbs - dxAbs;
	int16_t py = 2 * dxAbs - dyAbs;
	uint16_t xe = 0;
	uint16_t ye = 0;

	// Check if the line is moving mostly horizontal, else its mostly vertical
	if (dyAbs <= dxAbs)
	{
		// Check if the line is moving right, else its moving left
		// Set the ends accordingly
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}

		// Draw the start of the line
		drawPixel(x, y, color);

		// Draw the rest of the line
		for (uint16_t i = 0; x < xe; i++)
		{
			x = x + 1;

			// Checking what ???
			if (px < 0)
			{
				px = px + 2 * dyAbs;
			}
			else
			{
				// Checking what ???
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}

				px = px + 2 * (dyAbs - dxAbs);
			}

			drawPixel(x, y, color);
		}
	}
	else
	{
		// Check if the line is moving down, else its moving down
		// Set the ends accordingly
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}

		// Draw the start of the line
		drawPixel(x, y, color);

		// Draw the rest of the line
		for (uint16_t i = 0; y < ye; i++)
		{
			y = y + 1;

			// Checking what ???
			if (py <= 0)
			{
				py = py + 2 * dxAbs;
			}
			else
			{
				// Checking what ???
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}

				py = py + 2 * (dxAbs - dyAbs);
			}

			drawPixel(x, y, color);
		}
	}
}

void App::drawCircle(int x, int y, int r, sf::Color color)
{
	// Circle is drawn within square of size 2r
	uint32_t size = 2 * r + 1;

	// Coordinates inside the square
	uint32_t xRect = 0;
	uint32_t yRect = 0;

	// Go through all the positions
	for (uint32_t i = 0; i < size; i++)
	{
		for (uint32_t j = 0; j < size; j++)
		{
			// Start from the top left corner
			xRect = i - r;
			yRect = j - r;

			// Draw the pixel if its inside the circle
			if (xRect * xRect + yRect * yRect <= r * r + 1)
			{
				drawPixel(x + xRect, y + yRect, color);
			}
		}
	}
}

void App::drawCircleBorder(int x, int y, int r, sf::Color color)
{
	int x0 = 0;
	int y0 = r;
	int d = 3 - 2 * r;

	while (y0 >= x0)
	{
		// Draw the eight octants
		drawPixel(x + x0, y - y0, color);
		drawPixel(x - x0, y - y0, color);
		drawPixel(x + x0, y + y0, color);
		drawPixel(x - x0, y + y0, color);
		drawPixel(x + y0, y - x0, color);
		drawPixel(x - y0, y - x0, color);
		drawPixel(x + y0, y + x0, color);
		drawPixel(x - y0, y + x0, color);

		if (d < 0)
		{
			d += 4 * x0 + 6;
		}
		else
		{
			d += 4 * (x0 - y0) + 10;
			y0--;
		}
		x0++;
	}
}

void App::drawCircleSliceBorder(int x, int y, int r, float startAngle, float endAngle, sf::Color color)
{
	// Draw the arch (360 - (opposite angle - 90)) to ensure correct positioning rotation
	float startRad = (360 - (endAngle - 90)) * M_PI / 180.0f;
	float endRad = (360 - (startAngle - 90)) * M_PI / 180.0f;

	if (endRad < startRad) endRad += 2 * M_PI;

	float step = 1.0f / r;
	for (float angle = startRad; angle <= endRad; angle += step)
	{
		int32_t i = round(r * cos(angle));
		int32_t j = round(r * sin(angle));
		drawPixel(x + i, y - j, color);
	}

	// Draw the side lines
	float startRadLines = startAngle * M_PI / 180.0f;
	float endRadLines = endAngle * M_PI / 180.0f;

	for (int32_t i = 0; i <= r; i++)
	{
		int32_t startX = round(i * sin(startRadLines));
		int32_t startY = round(i * cos(startRadLines));
		int32_t endX = round(i * sin(endRadLines));
		int32_t endY = round(i * cos(endRadLines));

		drawPixel(x + startX, y - startY, color);
		drawPixel(x + endX, y - endY, color);
	}
}
// Temp

void App::start()
{
	window.create(sf::VideoMode(SCREEN_WIDTH/*1920*/, SCREEN_HEIGHT/*1080*/), "", sf::Style::Fullscreen);
	window.setFramerateLimit(30);
	
	font.loadFromFile("resource\\arial.ttf");

	r = RoundedRectangle({ 0, 0, 50, 50 }, { .fillColor = sf::Color::Cyan, .outlineThickness = 1});

	r2 = RoundedRectangle(r);
	r2.setFillColor(sf::Color::Yellow);

	t = Text({ 0, 0 }, "Hello World!", 30, font, { .style = sf::Text::Italic | sf::Text::Underlined });

	b = Button({ 0, 0, 200, 100 }, "I'm a button", 30, font);

	cb = Checkbox({ 0, 0, 50, 50 }, "Check me!", 20, font);

	c = Container({ 0, 0, 200, 200 }, { .containerAttributes = { .outlineThickness = 1 } }, Text(t));

	l = LineLayout({ 100, 100, 1720, 880 }, { .spacing = 20, .frameAttributes = { .outlineThickness = 1 } }, { &r, &t, &b, &cb, &c, &r2 });

	//run();
	schoolProjectCode();
}

void App::run()
{
	while (window.isOpen())
	{
		handleEvents();
		update();
		draw();
	}

	quit();
}

void App::handleEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			quit();
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				quit();
				break;
			case sf::Keyboard::Space:
				l.setHorizontalContentAlignment(Left);
				l.setVerticalContentAlignment(Top);
				l.setAlignmentAxis((l.getAlignmentAxis() & Horizontal) ? Vertical : Horizontal);
				break;
			case sf::Keyboard::L:
				l.setHorizontalContentAlignment(Left);
				break;
			case sf::Keyboard::R:
				l.setHorizontalContentAlignment(Right);
				break;
			case sf::Keyboard::T:
				l.setVerticalContentAlignment(Top);
				break;
			case sf::Keyboard::B:
				l.setVerticalContentAlignment(Bottom);
				break;
			case sf::Keyboard::C:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
					l.setHorizontalContentAlignment(Center);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
					l.setVerticalContentAlignment(Center);
				break;
			case sf::Keyboard::S:
				if (l.getAlignmentAxis() & Horizontal)
					l.setHorizontalContentAlignment(Stretch);
				else if (l.getAlignmentAxis() & Vertical)
					l.setVerticalContentAlignment(Stretch);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void App::update()
{

}

void App::draw()
{
	window.clear(sf::Color::White);

	window.draw(l);

	sf::RectangleShape r1({ 1, 880 });
	r1.setPosition({ 960, 100 });
	r1.setFillColor(sf::Color::Red);
	window.draw(r1);

	sf::RectangleShape r2({ 1720, 1 });
	r2.setPosition({ 100, 540 });
	r2.setFillColor(sf::Color::Red);
	window.draw(r2);

	window.display();
}

void App::quit()
{
	window.close();
}