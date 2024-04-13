#include <App.hpp>
#include <UIElements.hpp>

void App::start()
{
	window.create(sf::VideoMode(1920, 1080), "", sf::Style::Fullscreen);
	window.setFramerateLimit(30);

	font.loadFromFile("resource\\arial.ttf");

	/*
	r = RoundedRectangle({ 0, 0, 50, 50 });
	r.setFillColor(sf::Color::Cyan);
	r.setOutlineColor(sf::Color::Black);
	r.setOutlineThickness(1);

	r2 = RoundedRectangle(r);
	r2.setFillColor(sf::Color::Yellow);

	t = Text({ 0, 0 }, "Hello World!", 30, font);

	b = Button({ 0, 0, 200, 100 }, "I'm a button", 30, font);

	cb = Checkbox({ 0, 0, 50, 50 }, "Check me!", 20, font);

	c = Container({ 0, 0, 200, 200 }, Text(t));
	c.getContainer().setOutlineColor(sf::Color::Black);
	c.getContainer().setOutlineThickness(1);

	l = LineLayout({ 100, 100, 1720, 880 }, { &r, &t, &b, &cb, &c, &r2 });
	l.setElementSpacing(20);
	l.getFrame().setOutlineColor(sf::Color::Black);
	l.getFrame().setOutlineThickness(1);
	*/

	btn = Button({ 100, 100, 200, 100 }, "I'm a button", 30, font);

	run();
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
			
			/*
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
			*/

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

	/*
	window.draw(l);

	sf::RectangleShape r1({ 1, 880 });
	r1.setPosition({ 960, 100 });
	r1.setFillColor(sf::Color::Red);
	window.draw(r1);

	sf::RectangleShape r2({ 1720, 1 });
	r2.setPosition({ 100, 540 });
	r2.setFillColor(sf::Color::Red);
	window.draw(r2);
	*/

	window.draw(btn);

	window.display();
}

void App::quit()
{
	window.close();
}