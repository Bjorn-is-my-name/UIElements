#include <UIElements/Text.hpp>

namespace uie
{
	Text::Text(const sf::Vector2f& position, const sf::String& text, unsigned int characterSize, const sf::Font& font)
	{
		label.setCharacterSize(characterSize);
		label.setString(text);
		label.setFont(font);
		label.setFillColor(sf::Color::Black);
		setPosition(position);
	}

	void Text::allowSnapping(bool allowed)
	{
		snap = allowed;
	}

	sf::FloatRect Text::getLocalBounds() const
	{
		return label.getLocalBounds();
	}

	sf::FloatRect Text::getGlobalBounds() const
	{
		return label.getGlobalBounds();
	}

	sf::Vector2f Text::getPosition() const
	{
		return getGlobalBounds().getPosition();
	}

	void Text::setPosition(const sf::Vector2f& position)
	{
		label.setPosition(position - getLocalBounds().getPosition());
	}

	sf::Vector2f Text::getSize() const
	{
		return getGlobalBounds().getSize();
	}

	void Text::setSize(const sf::Vector2f& size)
	{
		throw std::exception("setSize() is not implemented, use setCharacterSize() instead");
	}

	void Text::move(const sf::Vector2f& offset)
	{
		label.move(offset);
	}

	bool Text::intersects(const sf::Vector2f& point) const
	{
		return getGlobalBounds().intersects({ point, {1, 1} });
	}

	bool Text::intersects(const sf::FloatRect& rect) const
	{
		return getGlobalBounds().intersects(rect);
	}

	void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (snap)
		{
			sf::Text temp(label);
			sf::Vector2f position = getPosition();
			position = { (float)(int)(position.x + 0.5f), (float)(int)(position.y + 0.5f) };
			temp.setPosition(position - getLocalBounds().getPosition());
			target.draw(temp, states);
		}
		else
			target.draw(label, states);
	}

	const sf::String& Text::getString() const
	{
		return label.getString();
	}

	void Text::setString(const sf::String& string)
	{
		label.setString(string);
	}

	const sf::Font* Text::getFont() const
	{
		return label.getFont();
	}

	void Text::setFont(const sf::Font& font)
	{
		label.setFont(font);
	}

	unsigned int Text::getCharacterSize() const
	{
		return label.getCharacterSize();
	}

	void Text::setCharacterSize(unsigned int size)
	{
		label.setCharacterSize(size);
	}

	float Text::getLetterSpacing() const
	{
		return label.getLetterSpacing();
	}

	void Text::setLetterSpacing(float spacingFactor)
	{
		label.setLetterSpacing(spacingFactor);
	}

	float Text::getLineSpacing() const
	{
		return label.getLineSpacing();
	}

	void Text::setLineSpacing(float spacingFactor)
	{
		label.setLineSpacing(spacingFactor);
	}

	unsigned int Text::getStyle() const
	{
		return label.getStyle();
	}

	void Text::setStyle(unsigned int style)
	{
		label.setStyle(style);
	}

	const sf::Color& Text::getFillColor() const
	{
		return label.getFillColor();
	}

	void Text::setFillColor(const sf::Color& color)
	{
		label.setFillColor(color);
	}

	const sf::Color& Text::getOutlineColor() const
	{
		return label.getOutlineColor();
	}

	void Text::setOutlineColor(const sf::Color& color)
	{
		label.setOutlineColor(color);
	}

	float Text::getOutlineThickness() const
	{
		return label.getOutlineThickness();
	}

	void Text::setOutlineThickness(float thickness)
	{
		label.setOutlineThickness(thickness);
	}
} // namespace uie