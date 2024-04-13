#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Text.hpp>
#include <functional>

namespace uie
{
	class Button : public UIElement
	{
	private:
		RoundedRectangle rectangle;
		Text text;
		std::function<void()> onClick;

	public:

		/*------------------------------*/
		/*          Functional          */
		/*------------------------------*/

		Button() = default;
		Button(const sf::Vector2f& position, const sf::Vector2f& size);
		Button(const sf::FloatRect& rect);
		Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		Button(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		RoundedRectangle& const getRectangle();
		void setRectangle(const RoundedRectangle& rect);
		Text& const getText();
		void setText(const Text& text);
		const std::function<void()>& getOnClick() const;
		void setOnClick(const std::function<void()>& functor);
		void executeOnClick();

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
		void setString(const sf::String& text);
		void setCharacterSize(unsigned int size);
		void setLetterSpacing(float spacingFactor);
		void setLineSpacing(float spacingFactor);
	};
} // namespace uie