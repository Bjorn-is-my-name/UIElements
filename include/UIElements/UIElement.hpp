/*****************************************************************//**
 * @file   UIElement.hpp
 * @brief  File containing the main interface
 * 
 * @author Bjorn Wakker
 * @date   11 April 2024
 *********************************************************************/
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace uie
{
	/**
	 * @brief Specialized interface for all the ui-element classes
	 * 
	 * @see sf::Drawable
	 */
	class UIElement : public sf::Drawable
	{
	protected:
		/**
		 * @brief Protected constructor
		 *
		 * @details
		 * Only allow classes that implement the interface to create an object of it
		 * Necessary to allow declaration without initialization
		 */
		UIElement() = default;

	public:
		/**
		 * @brief Virtual destructor
		 */
		virtual ~UIElement() = default;

		/**
		 * @brief Get the local boundaries of the ui-element
		 *
		 * @details The local boundaries are the boundaries of the ui-element if it were to be at position (0, 0)
		 *
		 * @return The local boundaries
		 */
		virtual sf::FloatRect getLocalBounds() const = 0;

		/**
		 * @brief Get the global boundaries of the ui-element
		 *
		 * @details The global boundaries are the boundaries of the ui-element at its position (x, y)
		 *
		 * @return The global boundaries
		 */
		virtual sf::FloatRect getGlobalBounds() const = 0;

		/**
		 * @brief Get the position of the ui-element
		 *
		 * @return The current position
		 *
		 * @see setPosition
		 */
		virtual sf::Vector2f getPosition() const = 0;

		/**
		 * @brief Set the position of the ui-element
		 *
		 * @param[in] position The new position
		 *
		 * @see getPosition
		 */
		virtual void setPosition(const sf::Vector2f& position) = 0;

		/**
		 * @brief Get the size of the ui-element
		 *
		 * @return The current size
		 *
		 * @see setSize
		 */
		virtual sf::Vector2f getSize() const = 0;

		/**
		 * @brief Set the size of the ui-element
		 *
		 * @param[in] size The new size
		 *
		 * @see getSize
		 */
		virtual void setSize(const sf::Vector2f& size) = 0;

		/**
		 * @brief Move the ui-element by a certain offset
		 *
		 * @param[in] offset The distance to move
		 */
		virtual void move(const sf::Vector2f& offset) = 0;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the point intersects with the ui-element
		 *
		 * @param[in] point The point to check for
		 * 
		 * @return True on intersection, else false
		 */
		virtual bool intersects(const sf::Vector2f& point) const = 0;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the rectangle intersects with the ui-element
		 *
		 * @param[in] rect The rectangle to check for
		 * 
		 * @return True on intersection, else false
		 */
		virtual bool intersects(const sf::FloatRect& rect) const = 0;

		/**
		 * @brief Draw the ui-element to a rendertarget
		 *
		 * @details Draw function from the base class to be overridden by the ui-element
		 *
		 * @param[in] target Render target to draw to
		 * @param[in] states Current render states
		 * 
		 * @see sf::Drawable
		 */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};

	/**
	 * @brief Type declaration for a UIElement pointer
	 *
	 * @see UIElement
	 */
	typedef UIElement* Any;

	/**
	 * @brief Concept to check if a type is derived from the UIElement interface
	 *
	 * @tparam T The type to check if is derived from the interface, also allowing pointers to the type
	 *
	 * @see UIElement
	 */
	template <typename T>
	concept ImplementsUIElement = std::is_base_of_v<UIElement, std::remove_pointer_t<T>>;
} // namespace uie

/**
 * @class uie::UIElement
 * 
 * @details 
 * uie::UIElement is a simple interface which can be inherited from
 * to give a class the necessary methods to become a ui-element
 * 
 * All you have to do in your derived class is make an implementation
 * for each method signature
 * 
 * Note that inheriting from UIElement is mandatory if you want
 * your class to work with the other ui-elements
 * 
 * Usage Example:
 * @code
 * class MyUIElement : public UIElement
 * {
 * private:
 *     sf::RectangleShape frame;
 *     sf::Font font;
 *     sf::Text text;
 * 
 * public:
 *	 	MyUIElement(const sf::FloatRect& posAndSize)
 *		{
 *			frame.setPosition(posAndSize.getPosition());
 *			frame.setSize(posAndSize.getSize());
 *			frame.setFillColor(sf::Color::White);
 *			frame.setOutlineColor(sf::Color::Black);
 *			frame.setOutlineThickness(1);
 * 
 *			font.loadFromFile(R"(resource\arial.ttf)");
 *	
 *			text.setString("Look, it's a rectangle!");
 *			text.setCharacterSize(20);
 *			text.setFont(font);
 *			text.setFillColor(sf::Color::Black);
 *	
 *			text.setPosition({
 *				posAndSize.left + posAndSize.width / 2 - (text.getGlobalBounds().width - text.getLocalBounds().left) / 2,
 *				posAndSize.top - 30
 *			});
 *		}
 *
 *		sf::FloatRect getLocalBounds() const
 *		{
 *			return frame.getLocalBounds();
 *		}
 *
 *		sf::FloatRect getGlobalBounds() const
 *		{
 *			return frame.getGlobalBounds();
 *		}
 *
 *		sf::Vector2f getPosition() const
 *		{
 *			return frame.getPosition();
 *		}
 *
 *		void setPosition(const sf::Vector2f& position)
 *		{
 *			frame.setPosition(position);
 *          text.setPosition({
 *				position.x + getSize().x / 2 - (text.getGlobalBounds().width - text.getLocalBounds().left) / 2,
 *				position.y - 30
 *			});
 *		}
 *
 *		sf::Vector2f getSize() const
 *		{
 *			return frame.getSize();
 *		}
 *
 *		void setSize(const sf::Vector2f& size)
 *		{
 *			frame.setSize(size);
 *		}
 *
 *		void move(const sf::Vector2f& offset)
 *		{
 *			frame.move(offset);
 *			text.move(offset);
 *		}
 *
 *		bool intersects(const sf::Vector2f& point) const
 *		{
 *			return getGlobalBounds().intersects({ point, { 1, 1 } });
 *		}
 *
 *		bool intersects(const sf::FloatRect& rect) const
 *		{
 *			return getGlobalBounds().intersects(rect);
 *		}
 *
 *		void draw(sf::RenderTarget& target, sf::RenderStates states) const
 *		{
 *			target.draw(frame, states);
 *			target.draw(text, states);
 *		}
 * };
 * @endcode
 */
