/*****************************************************************//**
 * @file   Button.hpp
 * @brief  File containing the Button class
 * 
 * @author Bjorn Wakker
 * @date   15 April 2024
 *********************************************************************/
#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Text.hpp>
#include <functional>

namespace uie
{
	/**
	 * @brief Specialized ui-element representing a button
	 * 
	 * @details
	 * A button is made up of a rectangle and text, the text
	 * is centered by default
	 * 
	 * The button class only implements methods which differ from the methods
	 * in RoundedRectangle and Text. Any other desired changes must be made
	 * using the methods getRectangle and getText.
	 * 
	 * If a different position then the center is desired, getText has to be
	 * used to obtain the text. Changing the text independently will have to
	 * be done after the button has been set up, this becuase changing something
	 * in the button its visual settings may reset the text to the center.
	 * 
	 * @see UIElement, RoundedRectangle, Text
	 */
	class Button : public UIElement
	{
	private:
		RoundedRectangle rectangle;    // The rectangle
		Text text;                     // The text
		std::function<void()> onClick; // The function to be executed on click

	public:
		/**
		 * @brief Structure for additional attributes
		 *
		 * @see RoundedRectangle, Text
		 */
		struct Attributes
		{
			std::function<void()> onClick = [](){};
			RoundedRectangle::Attributes rectangleAttributes{ .outlineThickness = 1.0f };
			Text::Attributes textAttributes{};
		};

		/**
		 * @brief The default constructor
		 * 
		 * @see Button
		 */
		Button() = default;

		/**
		 * @brief Overloaded constructor
		 * 
		 * @details Create the button at the given position with the given size
		 * 
		 * @param[in] position The position of the button
		 * @param[in] size	   The size of the button
		 * 
		 * @see Button
		 */
		Button(const sf::Vector2f& position, const sf::Vector2f& size);

		/**
		 * @brief Overloaded constructor
		 * 
		 * @details Create the button at the given position with the given size
		 * 
		 * @param[in] rect The rectangle of which to create the rounded rectangle
		 * 
		 * @see Button
		 */
		Button(const sf::FloatRect& rect);

		/**
		 * @brief Overloaded constructor
		 * 
		 * @details
		 * Create the button at the given position with the given size
		 * Create the text inside the button and center it
		 * 
		 * @param[in] position      The position of the button
		 * @param[in] size          The size of the button
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * 
		 * @see Button
		 */
		Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the button at the given position with the given size
		 * Create the text inside the button and center it
		 * Set all the specified attributes
		 *
		 * @param[in] position      The position of the button
		 * @param[in] size          The size of the button
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * @param[in] attributes    The additional attributes to set
		 *
		 * @see Button, Attributes, setAttributes
		 */
		Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		
		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the button at the given position with the given size
		 * Create the text inside the button and center it
		 *
		 * @param[in] rect          The rectangle of which to create the rounded rectangle
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * 
		 * @see Button
		 */
		Button(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the button at the given position with the given size
		 * Create the text inside the button and center it
		 * Set all the specified attributes
		 *
		 * @param[in] rect          The rectangle of which to create the rounded rectangle
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * @param[in] attributes    The additional attributes to set
		 *
		 * @see Button, Attributes, setAttributes
		 */
		Button(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		
		/**
		 * @brief Set all the specified attributes
		 * 
		 * @param[in] attributes The attributes
		 * 
		 * @see Attributes, setOnclick
		 */
		void setAttributes(const Attributes& attributes);

		/**
		 * @brief Get the button rectangle
		 * 
		 * @return A reference to the rectangle
		 * 
		 * @see setRectange
		 */
		RoundedRectangle& const getRectangle();

		/**
		 * @brief Set the button rectangle
		 * 
		 * @param[in] rect The new rectangle for the button
		 * 
		 * @see getRectangle
		 */
		void setRectangle(const RoundedRectangle& rect);

		/**
		 * @brief Get the button text
		 * 
		 * @return A reference to the text
		 * 
		 * @see setText
		 */
		Text& const getText();

		/**
		 * @brief Set the button text
		 * 
		 * @param[in] text The new text for the button
		 * 
		 * @see getText
		 */
		void setText(const Text& text);
		
		/**
		 * @brief Get the onClick function
		 * 
		 * @details Get the function to be executed on click
		 * 
		 * @return A reference to the function
		 * 
		 * @see setOnClick
		 */
		const std::function<void()>& getOnClick() const;
		
		/**
		 * @brief Set the onClick function
		 * 
		 * @details Set the function to be executed on click
		 * 
		 * @param[in] functor A reference to the new onClick function
		 * 
		 * @see getOnClick
		 */
		void setOnClick(const std::function<void()>& functor);
		
		/**
		 * @brief Executes the onClick function
		 * 
		 * @details Executes the function which onClick holds a reference to
		 * 
		 * @see setOnClick
		 */
		void executeOnClick();

		/**
		 * @brief Get the local boundaries
		 *
		 * @details 
		 * Get the local boundaries of the button its rectangle
		 * The local boundaries are the boundaries of the button if it were to be at position (0, 0)
		 *
		 * @return The local boundaries
		 */
		sf::FloatRect getLocalBounds() const override;

		/**
		 * @brief Get the global boundaries
		 *
		 * @details 
		 * Get the global boundaries of the button its rectangle
		 * The global boundaries are the boundaries of the at its position (x, y)
		 *
		 * @return The global boundaries
		 */
		sf::FloatRect getGlobalBounds() const override;

		/**
		 * @brief Get the position
		 *
		 * @return The current position of the button its rectangle
		 *
		 * @see setPosition
		 */
		sf::Vector2f getPosition() const override;

		/**
		 * @brief Set the position
		 *
		 * @param[in] position The new position
		 *
		 * @see getPosition
		 */
		void setPosition(const sf::Vector2f& position) override;

		/**
		 * @brief Get the size
		 *
		 * @return The current size of the button its rectangle
		 *
		 * @see setSize
		 */
		sf::Vector2f getSize() const override;

		/**
		 * @brief Set the size
		 *
		 * @param[in] size The new size for the button its rectangle
		 *
		 * @see getSize
		 */
		void setSize(const sf::Vector2f& size) override;

		/**
		 * @brief Move the button by a certain offset
		 *
		 * @param[in] offset The distance to move
		 */
		void move(const sf::Vector2f& offset) override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the point intersects with the button its rectangle
		 *
		 * @param[in] point The point to check for
		 *
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::Vector2f& point) const override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the rectangle intersects with the button its rectangle
		 *
		 * @param[in] rect The rectangle to check for
		 *
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::FloatRect& rect) const override;

		/**
		 * @brief Draw the button to a rendertarget
		 *
		 * @param[in] target Render target to draw to
		 * @param[in] states Current render states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief Corrects the position of the text
		 * 
		 * @details Centers the text within the button
		 */
		void correctTextPosition();
		
		/**
		 * @brief Set the text's string
		 *
		 * @details
		 * A text's string is empty by default.
		 *
		 * The @a string argument is a sf::String, which can
		 * automatically be constructed from standard string types.
		 * So, the following calls are all valid:
		 *
		 * @code
		 * text.setString("hello");
		 * text.setString(L"hello");
		 * text.setString(std::string("hello"));
		 * text.setString(std::wstring(L"hello"));
		 * @endcode
		 *
		 * @param[in] string New string
		 *
		 * @see getString
		 */
		void setString(const sf::String& string);

		/**
		 * @brief Set the character size
		 *
		 * @details
		 * The default size is 30.
		 *
		 * Note that if the used font is a bitmap font, it is not
		 * scalable, thus not all requested sizes will be available
		 * to use. This needs to be taken into consideration when
		 * setting the character size. If you need to display text
		 * of a certain size, make sure the corresponding bitmap
		 * font that supports that size is used.
		 *
		 * @param[in] size New character size, in pixels
		 *
		 * @see getCharacterSize
		 */
		void setCharacterSize(unsigned int size);

		/**
		 * @brief Set the letter spacing factor
		 *
		 * @details
		 * The default spacing between letters is defined by the font.
		 * This factor doesn't directly apply to the existing
		 * spacing between each character, it rather adds a fixed
		 * space between them which is calculated from the font
		 * metrics and the character size.
		 * Note that factors below 1 (including negative numbers) bring
		 * characters closer to each other.
		 * By default the letter spacing factor is 1.
		 *
		 * @param[in] spacingFactor New letter spacing factor
		 *
		 * @see getLetterSpacing
		 */
		void setLetterSpacing(float spacingFactor);

		/**
		 * @brief Set the line spacing factor
		 *
		 * @details
		 * The default spacing between lines is defined by the font.
		 * This method enables you to set a factor for the spacing
		 * between lines. By default the line spacing factor is 1.
		 *
		 * @param[in] spacingFactor New line spacing factor
		 *
		 * @see getLineSpacing
		 */
		void setLineSpacing(float spacingFactor);
	};
} // namespace uie