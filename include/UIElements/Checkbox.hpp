#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Text.hpp>
#include <UIElements/Alignment.hpp>

namespace uie
{
	class Checkbox : public UIElement
	{
	private:
		RoundedRectangle rectangle;
		Text text;

		bool selected = false;
		sf::Color selectedColor = sf::Color(0, 160, 255);
		sf::Color deselectedColor = sf::Color::Transparent;
		unsigned int textDistance = 20;
		Alignment alignment = Left;

		void checkAlignment();

	public:
		struct Attributes
		{
			bool selected = false;
			const sf::Color& selectedColor = sf::Color(0, 160, 255);
			const sf::Color& deselectedColor = sf::Color::Transparent;
			Alignment textAlignment = Left;
			unsigned int textDistance = 20;
			const RoundedRectangle::Attributes& rectangleAttributes{ .fillColor = deselectedColor, .outlineThickness = 1.0f };
			const Text::Attributes& textAttributes{};
		};

		/*------------------------------*/
		/*          Functional          */
		/*------------------------------*/

		Checkbox() = default;
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size);
		Checkbox(const sf::FloatRect& rect);
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		Checkbox(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		Checkbox(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		void setAttributes(const Attributes& attributes);
		RoundedRectangle& const getRectangle();
		void setRectangle(const RoundedRectangle& rect);
		Text& const getText();
		void setText(const Text& text);
		bool isSelected() const;
		void select();
		void deselect();
		void toggle();

		/*------------------------------*/
		/*   Interface implementations  */
		/*------------------------------*/

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;
		sf::Vector2f getPosition() const override;
		void setPosition(const sf::Vector2f& position) override;
		sf::Vector2f getSize() const override;
		void setSize(const sf::Vector2f& size) override;
		void move(const sf::Vector2f& offset) override;
		bool intersects(const sf::Vector2f& point) const override;
		bool intersects(const sf::FloatRect& rect) const override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/*------------------------------*/
		/*            Visual            */
		/*------------------------------*/

		void correctTextPosition();
		const sf::Color& getSelectedColor() const;
		void setSelectedColor(const sf::Color& color);
		const sf::Color& getDeselectedColor() const;
		void setDeselectedColor(const sf::Color& color);
		Alignment getTextAlignment() const;
		void setTextAlignment(Alignment alignment);
		unsigned int getTextDistance() const;
		void setTextDistance(unsigned int distance);
		void setString(const sf::String& text);
		void setCharacterSize(unsigned int size);
		void setLetterSpacing(float spacingFactor);
		void setLineSpacing(float spacingFactor);
	};
} // namespace uie