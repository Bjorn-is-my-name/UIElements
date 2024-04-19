/*****************************************************************//**
 * @file   Text.hpp
 * @brief  File containing the Text class
 * 
 * @author Bjorn Wakker
 * @date   13 April 2024
 *********************************************************************/
#pragma once

#include <UIElements/UIElement.hpp>
#include <SFML/Graphics/Text.hpp>

namespace uie
{
	/**
	 * @brief Specialized ui-element representing text
	 *
	 * @details
	 * Text does not in inherit from sf::Text on purpose
	 * This is done to allow only specific methods to be implemented
	 * 
	 * @see UIElement
	 */
	class Text : public UIElement
	{
	private:
		sf::Text label;		// The text
		bool snap = true;	// If the position should round to an interger to prevent blurry text

	public:
		/**
		 * @brief Structure for additional attributes
		 */
		struct Attributes
		{
			float letterSpacing = 1.0f;
			float lineSpacing = 1.0f;
			unsigned int style = sf::Text::Regular;
			const sf::Color& fillColor = sf::Color::Black;
			const sf::Color& outlineColor = sf::Color::Black;
			float outlineThickness = 0.0f;
			bool snap = true;
		};

		/**
		 * @brief The default constructor
		 * 
		 * @see Text
		 */
		Text() = default;

		/**
		 * @brief Overloaded constructor
		 * 
		 * @details Create the text at the given position
		 * 
		 * @param[in] position      The position of the text
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * 
		 * @see Text
		 */
		Text(const sf::Vector2f& position, const sf::String& text, unsigned int characterSize, const sf::Font& font);

		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the text at the given position
		 * Set all the specified attributes
		 * 
		 * @param[in] position      The position of the text
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * @param[in] attributes    The additional attributes to set
		 *
		 * @see Text, Attributes, setAttributes
		 */
		Text(const sf::Vector2f& position, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		
		/**
		 * @brief Set all the specified attributes
		 * 
		 * @param[in] attributes The attributes
		 * 
		 * @see Attributes, setString, setFont, setCharacterSize, setLetterSpacing, setLineSpacing, 
		 * setStyle, setFillColor, setOutlineColor, setOutlineThickness, allowSnapping
		 */
		void setAttributes(const Attributes& attributes);

		/**
		 * @brief Allow snapping to pixels
		 * 
		 * @details 
		 * Allow the position to be rounded to the nearest integer to
		 * prevent getting blurry text on positions with non integral values
		 * 
		 * @param[in] allowed Is rounding the position allowed?
		 * 
		 * @see setPosition
		 */
		void allowSnapping(bool allowed);

		/**
		 * @brief Get the local boundaries
		 *
		 * @details The local boundaries are the boundaries of the text if it were to be at position (0, 0)
		 *
		 * @return The local boundaries
		 */
		sf::FloatRect getLocalBounds() const override;

		/**
		 * @brief Get the global boundaries
		 *
		 * @details The global boundaries are the boundaries of the text at its position (x, y)
		 *
		 * @return The global boundaries
		 */
		sf::FloatRect getGlobalBounds() const override;

		/**
		 * @brief Get the position
		 *
		 * @return The current position
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
		 * @return The current size
		 *
		 * @see setSize
		 */
		sf::Vector2f getSize() const override;

		/**
		 * @brief Set the size
		 *
		 * @param[in] size The new size
		 *
		 * @see getSize
		 */
		void setSize(const sf::Vector2f& size) override;

		/**
		 * @brief Move the text by a certain offset
		 *
		 * @param[in] offset The distance to move
		 */
		void move(const sf::Vector2f& offset) override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the point intersects with the text boundaries
		 *
		 * @param[in] point The point to check for
		 * 
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::Vector2f& point) const override;

		/**
		 * @brief Check for intersection
		 *
		 * @details Check if the rectangle intersects with the text boundaries
		 *
		 * @param[in] rect The rectangle to check for
		 * 
		 * @return True on intersection, else false
		 */
		bool intersects(const sf::FloatRect& rect) const override;

		/**
		 * @brief Draw the text to a rendertarget
		 *
		 * @param[in] target Render target to draw to
		 * @param[in] states Current render states
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief Get the text's string
		 *
		 * @details
		 * The returned string is a sf::String, which can automatically
		 * be converted to standard string types. So, the following
		 * lines of code are all valid:
		 * 
		 * @code
		 * sf::String   s1 = text.getString();
		 * std::string  s2 = text.getString();
		 * std::wstring s3 = text.getString();
		 * @endcode
		 *
		 * @return Text's string
		 *
		 * @see setString
		 */
		const sf::String& getString() const;

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
		 * @brief Get the text's font
		 *
		 * @details
		 * If the text has no font attached, a NULL pointer is returned.
		 * The returned pointer is const, which means that you
		 * cannot modify the font when you get it from this function.
		 *
		 * @return Pointer to the text's font
		 *
		 * @see setFont
		 */
		const sf::Font* getFont() const;
		
		/**
		 * @brief Set the text's font
		 *
		 * @details
		 * The @a font argument refers to a font that must
		 * exist as long as the text uses it. Indeed, the text
		 * doesn't store its own copy of the font, but rather keeps
		 * a pointer to the one that you passed to this function.
		 * If the font is destroyed and the text tries to
		 * use it, the behavior is undefined.
		 *
		 * @param[in] font New font
		 *
		 * @see getFont
		 */
		void setFont(const sf::Font& font);
		
		/**
		 * @brief Get the character size
		 *
		 * @return Size of the characters, in pixels
		 *
		 * @see setCharacterSize
		 */
		unsigned int getCharacterSize() const;
		
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
		 * @brief Get the size of the letter spacing factor
		 *
		 * @return Size of the letter spacing factor
		 *
		 * @see setLetterSpacing
		 */
		float getLetterSpacing() const;
		
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
		 * @brief Get the size of the line spacing factor
		 *
		 * @return Size of the line spacing factor
		 *
		 * @see setLineSpacing
		 */
		float getLineSpacing() const;
		
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
		
		/**
		 * @brief Get the text's style
		 *
		 * @return Text's style
		 *
		 * @see setStyle
		 */
		unsigned int getStyle() const;
		
		/**
		 * @brief Set the text's style
		 *
		 * @details
		 * You can pass a combination of one or more styles, for
		 * example sf::Text::Bold | sf::Text::Italic.
		 * The default style is sf::Text::Regular.
		 *
		 * @param[in] style New style
		 *
		 * @see getStyle
		 */
		void setStyle(unsigned int style);
		
		/**
		 * @brief Get the fill color of the text
		 *
		 * @return Fill color of the text
		 *
		 * @see setFillColor
		 */
		const sf::Color& getFillColor() const;
		
		/**
		 * @brief Set the fill color of the text
		 *
		 * @details
		 * By default, the text's fill color is opaque white.
		 * Setting the fill color to a transparent color with an outline
		 * will cause the outline to be displayed in the fill area of the text.
		 *
		 * @param[in] color New fill color of the text
		 *
		 * @see getFillColor
		 */
		void setFillColor(const sf::Color& color);
		
		/**
		 * @brief Get the outline color of the text
		 *
		 * @return Outline color of the text
		 *
		 * @see setOutlineColor
		 */
		const sf::Color& getOutlineColor() const;
		
		/**
		 * @brief Set the outline color of the text
		 *
		 * @details By default, the text's outline color is opaque black.
		 *
		 * @param[in] color New outline color of the text
		 *
		 * @see getOutlineColor
		 */
		void setOutlineColor(const sf::Color& color);
		
		/**
		 * @brief Get the outline thickness of the text
		 *
		 * @return Outline thickness of the text, in pixels
		 *
		 * @see setOutlineThickness
		 */
		float getOutlineThickness() const;
		
		/**
		 * @brief Set the thickness of the text's outline
		 *
		 * @details
		 * By default, the outline thickness is 0.
		 *
		 * Be aware that using a negative value for the outline
		 * thickness will cause distorted rendering.
		 *
		 * @param[in] thickness New outline thickness, in pixels
		 *
		 * @see getOutlineThickness
		 */
		void setOutlineThickness(float thickness);
	};
} // namespace uie

/**
 * @class uie::Text
 * 
 * Usage Example:
 * \code
 * sf::Font font;
 * ...
 * uie::Text txt(sf::Vector2f{ 100, 100 }, "Hello World!", 30, font);
 * txt.setFillColor(sf::Color::Black);
 * txt.setStyle(sf::Text::Italic);
 * txt.setLetterSpacing(0.5f);
 * ...
 * window.draw(txt);
 * \endcode
 * 
 * Usage Example with TAttr:
 * \code
 * sf::Font font;
 * ...
 * 	uie::Text txt(
 *		sf::Vector2f{ 100, 100 },
 *		"Hello World!",
 *		30,
 *		font,
 *		TAttr{
 *			.letterSpacing = 0.5f,
 *			.style = sf::Text::Italic,
 *			.fillColor = sf::Color::Black,
 *          ...
 *		}
 *	);
 * ...
 * window.draw(txt);
 * \endcode
 */
