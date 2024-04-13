#include <UIElements/RoundedRectangle.hpp>
#include <stdexcept>

namespace uie
{
	RoundedRectangle::RoundedRectangle(const sf::Vector2f& position, const sf::Vector2f& size)
	{
		rectangle.setPosition(position);
		rectangle.setSize(size);
		rectangle.setCornersRadius(5);
		rectangle.setCornerPointCount(20);
	}

	RoundedRectangle::RoundedRectangle(const sf::FloatRect& rect)
		: RoundedRectangle(rect.getPosition(), rect.getSize())
	{

	}

	sf::FloatRect RoundedRectangle::getLocalBounds() const
	{
		return rectangle.getLocalBounds();
	}

	sf::FloatRect RoundedRectangle::getGlobalBounds() const
	{
		return rectangle.getGlobalBounds();
	}

	sf::Vector2f RoundedRectangle::getPosition() const
	{
		return rectangle.getPosition();
	}

	void RoundedRectangle::setPosition(const sf::Vector2f& position)
	{
		rectangle.setPosition(position);
	}

	sf::Vector2f RoundedRectangle::getSize() const
	{
		return rectangle.getSize();
	}

	void RoundedRectangle::setSize(const sf::Vector2f& size)
	{
		rectangle.setSize(size);
	}

	void RoundedRectangle::move(const sf::Vector2f& offset)
	{
		rectangle.move(offset);
	}

	bool RoundedRectangle::intersects(const sf::Vector2f& point) const
	{
		return getGlobalBounds().intersects({ point, {1, 1} });
	}

	bool RoundedRectangle::intersects(const sf::FloatRect& rect) const
	{
		return getGlobalBounds().intersects(rect);
	}

	void RoundedRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rectangle, states);
	}

	float RoundedRectangle::getCornersRadius() const
	{
		return rectangle.getCornersRadius();
	}

	void RoundedRectangle::setCornersRadius(float radius)
	{
		rectangle.setCornersRadius(radius);
	}

	unsigned int RoundedRectangle::getCornerPointCount() const
	{
		return rectangle.getPointCount() / 4;
	}

	void RoundedRectangle::setCornerPointCount(unsigned int count)
	{
		if (count < 2)
			throw std::invalid_argument("Point count must be greater than 1");

		rectangle.setCornerPointCount(count);
	}

	const sf::Texture* RoundedRectangle::getTexture() const
	{
		return rectangle.getTexture();
	}

	void RoundedRectangle::setTexture(const sf::Texture* texture, bool resetRect)
	{
		rectangle.setTexture(texture, resetRect);
	}

	const sf::IntRect& RoundedRectangle::getTextureRect() const
	{
		return rectangle.getTextureRect();
	}

	void RoundedRectangle::setTextureRect(const sf::IntRect& rect)
	{
		rectangle.setTextureRect(rect);
	}

	const sf::Color& RoundedRectangle::getFillColor() const
	{
		return rectangle.getFillColor();
	}

	void RoundedRectangle::setFillColor(const sf::Color& color)
	{
		rectangle.setFillColor(color);
	}

	const sf::Color& RoundedRectangle::getOutlineColor() const
	{
		return rectangle.getOutlineColor();
	}

	void RoundedRectangle::setOutlineColor(const sf::Color& color)
	{
		rectangle.setOutlineColor(color);
	}

	float RoundedRectangle::getOutlineThickness() const
	{
		return rectangle.getOutlineThickness();
	}

	void RoundedRectangle::setOutlineThickness(float thickness)
	{
		rectangle.setOutlineThickness(thickness);
	}

	void RoundedRectangle::makeRectangle()
	{
		setCornerPointCount(2);
		setCornersRadius(0);

		float thickness = getOutlineThickness();

		if (thickness > 0)
			setOutlineThickness(-thickness);
	}
} // namespace uie