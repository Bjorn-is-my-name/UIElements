//#include <UIElements/Toggle.hpp>
//
//Toggle::Toggle(const Position& position, const Size& size, int numberOfOptions)
//	: UIElement(position, size)
//{
//	rectangle = RoundedRectangle(position, size);
//	rectangle.setFillColor(sf::Color(211, 211, 211));
//	rectangle.setOutlineThickness(1);
//	rectangle.setOutlineColor(sf::Color::Black);
//
//	float increment = size.width / numberOfOptions;
//
//	for (int i = 0; i < numberOfOptions; i++)
//	{
//		Button btn = Button({ (int)(position.x + i * increment), position.y }, { (int)increment, size.height });
//		// Other custom options
//		options.push_back(btn);
//	}
//}
//
//const Button& Toggle::getOption(int index) const
//{
//	if (index < 0 || index >= options.size())
//		throw std::out_of_range("Index out of range");
//
//	return options[index];
//}
//
//int Toggle::getOptionsCount() const
//{
//	return options.size();
//}
//
//void Toggle::addOptions(int numberOfOptions)
//{
//	numberOfOptions += options.size();
//	float increment = size.width / numberOfOptions;
//
//	for (int i = 0; i < options.size(); i++)
//		options[i].setSize({ (int)increment, size.height });
//
//	for (int i = options.size(); i < numberOfOptions; i++)
//	{
//		Button btn = Button({ (int)(position.x + i * increment), position.y }, { (int)increment, size.height });
//		// Copy other settings (same settings as other options)
//		options.push_back(btn);
//	}
//}
//
//void Toggle::removeOption(int index)
//{
//	if (index < 0 || index >= options.size())
//		throw std::out_of_range("Index out of range");
//	
//	options.erase(options.begin() + index);
//}
//
//void Toggle::setPosition(const Position& position)
//{
//	this->position = position;
//	rectangle.setPosition(position);
//
//	if (options.size() > 0)
//	{
//		float increment = options.at(0).getSize().width;
//
//		for (int i = 0; i < options.size(); i++)
//			options[i].setPosition({ (int)(position.x + i * increment), position.y });
//	}
//}
//
//void Toggle::setSize(const Size& size)
//{
//	this->size = size;
//	rectangle.setSize(size);
//	
//	float increment = size.width / options.size();
//
//	for (int i = 0; i < options.size(); i++)
//	{
//		options[i].setSize({ (int)increment, size.height });
//		options[i].setPosition({ (int)(position.x + i * increment), position.y });
//	}
//}
//
//void Toggle::move(const Position& offset)
//{
//	position += offset;
//	rectangle.move(offset);
//	
//	for (Button& btn : options)
//		btn.move(offset);
//}
//
//void Toggle::draw(sf::RenderWindow& window)
//{
//	rectangle.draw(window);
//	
//	for (Button& btn : options)
//		btn.draw(window);
//}
