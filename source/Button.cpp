#include <UIElements/Button.hpp>

namespace uie
{
	Button::Button(const sf::Vector2f& position, const sf::Vector2f& size)
	{
		rectangle = RoundedRectangle(position, size);
		rectangle.setFillColor(sf::Color::Color::White);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Black);
	}

	Button::Button(const sf::FloatRect& rect)
		: Button(rect.getPosition(), rect.getSize())
	{

	}

	Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& txt, unsigned int characterSize, const sf::Font& font)
		: Button(position, size)
	{
		text = Text(position, txt, characterSize, font);
		correctTextPosition();
	}

	Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& txt, unsigned int characterSize, const sf::Font& font, const Attributes& attributes)
		: Button(position, size)
	{
		text = Text(position, txt, characterSize, font);
		setAttributes(attributes);
		correctTextPosition();
	}

	Button::Button(const sf::FloatRect& rect, const sf::String& txt, unsigned int characterSize, const sf::Font& font)
		: Button(rect.getPosition(), rect.getSize(), txt, characterSize, font)
	{

	}

	Button::Button(const sf::FloatRect& rect, const sf::String& txt, unsigned int characterSize, const sf::Font& font, const Attributes& attributes)
		: Button(rect.getPosition(), rect.getSize(), txt, characterSize, font, attributes)
	{
		
	}

	void Button::setAttributes(const Attributes& attributes)
	{
		setOnClick(attributes.onClick);
		rectangle.setAttributes(attributes.rectangleAttributes);
		text.setAttributes(attributes.textAttributes);
	}

	RoundedRectangle& const Button::getRectangle()
	{
		return rectangle;
	}

	void Button::setRectangle(const RoundedRectangle& rect)
	{
		rectangle = rect;
		correctTextPosition();
	}

	Text& const Button::getText()
	{
		return text;
	}

	void Button::setText(const Text& txt)
	{
		text = txt;
		correctTextPosition();
	}

	const std::function<void()>& Button::getOnClick() const
	{
		return onClick;
	}

	void Button::setOnClick(const std::function<void()>& functor)
	{
		onClick = functor;
	}

	void Button::executeOnClick()
	{
		if (onClick)
			onClick();
	}

	sf::FloatRect Button::getLocalBounds() const
	{
		return rectangle.getLocalBounds();
	}

	sf::FloatRect Button::getGlobalBounds() const
	{
		return rectangle.getGlobalBounds();
	}

	sf::Vector2f Button::getPosition() const
	{
		return rectangle.getPosition();
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		rectangle.setPosition(position);
		correctTextPosition();
	}

	sf::Vector2f Button::getSize() const
	{
		return rectangle.getSize();
	}

	void Button::setSize(const sf::Vector2f& size)
	{
		rectangle.setSize(size);
		correctTextPosition();
	}

	void Button::move(const sf::Vector2f& offset)
	{
		rectangle.move(offset);
		text.move(offset);
	}

	bool Button::intersects(const sf::Vector2f& point) const
	{
		return rectangle.intersects(point);
	}

	bool Button::intersects(const sf::FloatRect& rect) const
	{
		return rectangle.intersects(rect);
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rectangle, states);
		target.draw(text, states);
	}

	void Button::correctTextPosition()
	{
		sf::FloatRect rectBounds = rectangle.getGlobalBounds();
		sf::FloatRect textBounds = text.getGlobalBounds();

		text.setPosition({
			(rectBounds.left + rectBounds.width / 2.0f) - textBounds.width / 2.0f,
			(rectBounds.top + rectBounds.height / 2.0f) - textBounds.height / 2.0f
		});
	}

	void Button::setString(const sf::String& string)
	{
		text.setString(string);
		correctTextPosition();
	}

	void Button::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
		correctTextPosition();
	}

	void Button::setLetterSpacing(float spacingFactor)
	{
		text.setLetterSpacing(spacingFactor);
		correctTextPosition();
	}

	void Button::setLineSpacing(float spacingFactor)
	{
		text.setLineSpacing(spacingFactor);
		correctTextPosition();
	}
} // namespace uie