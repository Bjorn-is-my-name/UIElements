#include <UIElements/Checkbox.hpp>
#include <UIElements/ExtraFunctions.hpp>
#include <stdexcept>
#include <format>

namespace uie
{
	Checkbox::Checkbox(const sf::Vector2f& position, const sf::Vector2f& size)
	{
		rectangle = RoundedRectangle(position, size);
		rectangle.setFillColor(deselectedColor);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Black);
	}

	Checkbox::Checkbox(const sf::FloatRect& rect)
		: Checkbox(rect.getPosition(), rect.getSize())
	{

	}

	Checkbox::Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& txt, unsigned int characterSize, const sf::Font& font)
		: Checkbox(position, size)
	{
		text = Text(position, txt, characterSize, font);
		correctTextPosition();
	}

	Checkbox::Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& txt, unsigned int characterSize, const sf::Font& font, const Attributes& attributes)
		: Checkbox(position, size)
	{
		text = Text(position, txt, characterSize, font);
		setAttributes(attributes);
		correctTextPosition();
	}

	Checkbox::Checkbox(const sf::FloatRect& rect, const sf::String& txt, unsigned int characterSize, const sf::Font& font)
		: Checkbox(rect.getPosition(), rect.getSize(), txt, characterSize, font)
	{

	}

	Checkbox::Checkbox(const sf::FloatRect& rect, const sf::String& txt, unsigned int characterSize, const sf::Font& font, const Attributes& attributes)
		: Checkbox(rect.getPosition(), rect.getSize(), txt, characterSize, font, attributes)
	{

	}

	void Checkbox::setAttributes(const Attributes& attributes)
	{
		attributes.selected ? select() : deselect();
		setSelectedColor(attributes.selectedColor);
		setDeselectedColor(attributes.deselectedColor);
		alignment = attributes.textAlignment;
		textDistance = attributes.textDistance;
		rectangle.setAttributes(attributes.rectangleAttributes);
		text.setAttributes(attributes.textAttributes);
	}

	void Checkbox::checkAlignment()
	{
		for (Alignment a : { Top, Bottom, Center, Absolute, Stretch })
			if (alignment & a)
				throw std::runtime_error(std::format("Checkbox does not support alignment '{}'", toString(a)));
	}

	RoundedRectangle& const Checkbox::getRectangle()
	{
		return rectangle;
	}

	void Checkbox::setRectangle(const RoundedRectangle& rect)
	{
		rectangle = rect;
		correctTextPosition();
	}

	Text& const Checkbox::getText()
	{
		return text;
	}

	void Checkbox::setText(const Text& txt)
	{
		text = txt;
		correctTextPosition();
	}

	bool Checkbox::isSelected() const
	{
		return selected;
	}

	void Checkbox::select()
	{
		selected = true;
		rectangle.setFillColor(selectedColor);
	}

	void Checkbox::deselect()
	{
		selected = false;
		rectangle.setFillColor(deselectedColor);
	}

	void Checkbox::toggle()
	{
		selected ? deselect() : select();
	}

	sf::FloatRect Checkbox::getLocalBounds() const
	{
		return getTotalRect<float>({ rectangle.getLocalBounds(), text.getLocalBounds() });
	}

	sf::FloatRect Checkbox::getGlobalBounds() const
	{
		return getTotalRect<float>({ rectangle.getGlobalBounds(), text.getGlobalBounds() });
	}

	sf::Vector2f Checkbox::getPosition() const
	{
		return rectangle.getPosition();
	}

	void Checkbox::setPosition(const sf::Vector2f& position)
	{
		rectangle.setPosition(position);
		correctTextPosition();
	}

	sf::Vector2f Checkbox::getSize() const
	{
		return rectangle.getSize();
	}

	void Checkbox::setSize(const sf::Vector2f& size)
	{
		rectangle.setSize(size);
		correctTextPosition();
	}

	void Checkbox::move(const sf::Vector2f& offset)
	{
		rectangle.move(offset);
		text.move(offset);
	}

	bool Checkbox::intersects(const sf::Vector2f& point) const
	{
		return rectangle.intersects(point);
	}

	bool Checkbox::intersects(const sf::FloatRect& rect) const
	{
		return rectangle.intersects(rect);
	}

	void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rectangle, states);
		target.draw(text, states);
	}

	void Checkbox::correctTextPosition()
	{
		checkAlignment();

		const sf::String txt = text.getString();

		if (txt.getSize() == 0)
			return;

		sf::Vector2f textSize = text.getSize();
		float textHeight = textSize.y;

		if (txt.find('\n') == sf::String::InvalidPos)
			textHeight = Text({ 0, 0 }, txt[0], text.getCharacterSize(), *text.getFont()).getSize().y;

		sf::FloatRect rectBounds = rectangle.getGlobalBounds();
		sf::Vector2f rectPosition = rectBounds.getPosition();
		sf::Vector2f rectSize = rectBounds.getSize();

		float y = rectPosition.y + (rectSize.y / 2.0f - textHeight / 2.0f);

		if (alignment & Left)
			text.setPosition({ rectPosition.x - textSize.x - textDistance, y });
		else if (alignment & Right)
			text.setPosition({ rectPosition.x + rectSize.x + textDistance, y });
	}

	const sf::Color& Checkbox::getSelectedColor() const
	{
		return selectedColor;
	}

	void Checkbox::setSelectedColor(const sf::Color& color)
	{
		selectedColor = color;

		if (selected)
			rectangle.setFillColor(selectedColor);
	}

	const sf::Color& Checkbox::getDeselectedColor() const
	{
		return deselectedColor;
	}

	void Checkbox::setDeselectedColor(const sf::Color& color)
	{
		deselectedColor = color;

		if (!selected)
			rectangle.setFillColor(deselectedColor);
	}

	Alignment Checkbox::getTextAlignment() const
	{
		return alignment;
	}

	void Checkbox::setTextAlignment(Alignment alignment)
	{
		this->alignment = alignment;
		correctTextPosition();
	}

	unsigned int Checkbox::getTextDistance() const
	{
		return textDistance;
	}

	void Checkbox::setTextDistance(unsigned int distance)
	{
		textDistance = distance;
		correctTextPosition();
	}

	void Checkbox::setString(const sf::String& string)
	{
		text.setString(string);
		correctTextPosition();
	}

	void Checkbox::setCharacterSize(unsigned int size)
	{
		text.setCharacterSize(size);
		correctTextPosition();
	}

	void Checkbox::setLetterSpacing(float spacingFactor)
	{
		text.setLetterSpacing(spacingFactor);
		correctTextPosition();
	}

	void Checkbox::setLineSpacing(float spacingFactor)
	{
		text.setLineSpacing(spacingFactor);
		correctTextPosition();
	}
} // namespace uie