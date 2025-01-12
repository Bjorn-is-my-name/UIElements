/*****************************************************************//**
 * @file   Checkbox.hpp
 * @brief  File containing the Checkbox class
 * 
 * @author Bjorn Wakker
 * @date   14 November 2024
 *********************************************************************/
#pragma once

#include <UIElements/UIElement.hpp>
#include <UIElements/RoundedRectangle.hpp>
#include <UIElements/Text.hpp>
#include <UIElements/Alignment.hpp>

namespace uie
{
	/**
	 * @brief Specialized ui-element representing a checkbox
	 * 
	 * @details
	 * A checkbox is made up of a rectangle and text, the text
	 * is centered on the left of the checkbox by default
	 * 
	 * The checkbox class only implements methods which differ from the methods
	 * in RoundedRectangle and Text. Any other desired changes must be made
	 * using the methods getRectangle and getText.
	 * 
	 * @see UIElement, RoundedRectangle, Text, Alignment
	 */
	class Checkbox : public UIElement
	{
	private:
		RoundedRectangle rectangle;							// The rectangle
		Text text;											// The text

		bool selected = false;								// The state of the checkbox
		sf::Color selectedColor = sf::Color(0, 160, 255);	// The color of the checkbox when it is selected
		sf::Color deselectedColor = sf::Color::Transparent;	// The color of the checkbox when it is not selected
		unsigned int textDistance = 20;						// The distance between the text and the rectangle
		Alignment alignment = Left;							// The positioning of the text relative to the rectangle

		/**
		 * @brief Checks if the allignment is possible for this ui-element
		 * 
		 * @details Not all alignment options are implemented for every ui-element
		 * 
		 * @see Alignment
		 */
		void checkAlignment();

	public:
		/**
		 * @brief Structure for additional attributes
		 * 
		 * @see RoundedRectangle, Text, Alignment
		 */
		struct Attributes
		{
			bool selected = false;
			sf::Color selectedColor = sf::Color(0, 160, 255);
			sf::Color deselectedColor = sf::Color::Transparent;
			Alignment textAlignment = Left;
			unsigned int textDistance = 20;
			RoundedRectangle::Attributes rectangleAttributes{ .fillColor = deselectedColor, .outlineThickness = 1.0f };
			Text::Attributes textAttributes{};
		};

		/**
		 * @brief The default constructor
		 * 
		 * @see Checkbox
		 */
		Checkbox() = default;

		/**
		 * @brief Overloaded constructor
		 * 
		 * @details Create the checkbox at the given position with the given size
		 * 
		 * @param[in] position The position of the checkbox
		 * @param[in] size     The size of the checkbox
		 * 
		 * @see Checkbox
		 */
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size);
		
		/**
		 * @brief Overloaded constructor
		 * 
		 * @details Create the checkbox at the given position with the given size
		 * 
		 * @param[in] rect The rectangle of which to create the checkbox
		 * 
		 * @see Checkbox
		 */
		Checkbox(const sf::FloatRect& rect);
		
		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the checkbox at the given position with the given size
		 * Create the text next to the rectangle and center it
		 *
		 * @param[in] position      The position of the checkbox
		 * @param[in] size          The size of the checkbox
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 *
		 * @see Checkbox
		 */
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		
		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the checkbox at the given position with the given size
		 * Create the text next to the rectangle and center it
		 * Set all the specified attributes
		 *
		 * @param[in] position      The position of the checkbox
		 * @param[in] size          The size of the checkbox
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * @param[in] attributes    The additional attributes to set
		 *
		 * @see Checkbox, Attributes, setAttributes
		 */
		Checkbox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		
		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the checkbox at the given position with the given size
		 * Create the text next to the rectangle and center it
		 *
		 * @param[in] rect          The rectangle of which to create the checkbox
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 *
		 * @see Checkbox
		 */
		Checkbox(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font);
		
		/**
		 * @brief Overloaded constructor
		 *
		 * @details
		 * Create the checkbox at the given position with the given size
		 * Create the text next to the rectangle and center it
		 * Set all the specified attributes
		 *
		 * @param[in] rect          The rectangle of which to create the checkbox
		 * @param[in] text          The string text to be displayed
		 * @param[in] characterSize The size of the characters
		 * @param[in] font          The font of the text
		 * @param[in] attributes    The additional attributes to set
		 *
		 * @see Checkbox, Attributes, setAttributes
		 */
		Checkbox(const sf::FloatRect& rect, const sf::String& text, unsigned int characterSize, const sf::Font& font, const Attributes& attributes);
		
		/**
		 * @brief Set all the specified attributes
		 *
		 * @param[in] attributes The attributes
		 *
		 * @see Attributes
		 */
		void setAttributes(const Attributes& attributes);
		
		/**
		 * @brief Get the checkbox rectangle
		 *
		 * @return A reference to the rectangle
		 *
		 * @see setRectange
		 */
		RoundedRectangle& const getRectangle();
		
		/**
		 * @brief Set the checkbox rectangle
		 *
		 * @param[in] rect The new rectangle for the checkbox
		 *
		 * @see getRectangle
		 */
		void setRectangle(const RoundedRectangle& rect);
		
		/**
		 * @brief Get the checkbox text
		 *
		 * @return A reference to the text
		 *
		 * @see setText
		 */
		Text& const getText();
		
		/**
		 * @brief Set the checkbox text
		 *
		 * @param[in] text The new text for the checkbox
		 *
		 * @see getText
		 */
		void setText(const Text& text);
		
		/**
		 * @brief Get the state of the checkbox
		 * 
		 * @return True if the checkbox is selected, else False
		 */
		bool isSelected() const;
		
		/**
		 * @brief Change the checkbox state to selected
		 */
		void select();
		
		/**
		 * @brief Change the checkbox state to deselected
		 */
		void deselect();
		
		/**
		 * @brief Flip the state of the checkbox
		 * 
		 * @see select, deselect
		 */
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